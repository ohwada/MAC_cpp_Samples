// ex_bulk
// Using the bulk interface, secondary indexes, and subdatabases 
// This demonstrates how to fetch and modify many records within a single call of DB->get(), DB->put(), and DB->del(). 
// It also shows how to:
// a) define a custom btree key comparison function, so that records are ordered as natural integers,
// b) store two databases in a single Berkeley DB file, and
// c) construct a secondary “index” database for quick record access via a component of the data field.

 // gcc ex_bulk.c  `pkg-config --cflags --libs libdb`


// https://github.com/berkeleydb/libdb/blob/master/examples/c/ex_bulk.c

/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2001, 2012 Oracle and/or its affiliates.  All rights reserved. 
 *
 * $Id$
 */

/*
 * ex_bulk - Demonstrate usage of all bulk APIs available in Berkeley DB.
 * NOTE: Though this example code generates timing information, it's important
 * to note that it is written as code to demonstrate functionality, and is not
 * optimized as a benchmark. 
 */
#include <sys/types.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define	DATABASE	"ex_bulk.db"                      /* Database name */
#define	DATALEN		20                           /* The length of data */
#define	NS_PER_MS	1000000            /* Nanoseconds in a millisecond */
#define	NS_PER_US	1000               /* Nanoseconds in a microsecond */
#define	PUTS_PER_TXN	10
#define	STRLEN		DATALEN - sizeof(int)      /* The length of string */
#define	UPDATES_PER_BULK_PUT	100

#ifdef _WIN32
#include <sys/timeb.h>
extern int getopt(int, char * const *, const char *);
/* Implement a basic high res timer with a POSIX interface for Windows. */
struct timeval {
	time_t tv_sec;
	long tv_usec;
};
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	struct _timeb now;
	_ftime(&now);
	tv->tv_sec = now.time;
	tv->tv_usec = now.millitm * NS_PER_US;
	return (0);
}
#define CLEANUP_CMD "rmdir EX_BULK /q/s"
#else
#include <sys/time.h>
#include <unistd.h>
#define CLEANUP_CMD "rm -rf EX_BULK"
#endif

#include <db.h>

int	bulk_delete(DB_ENV *, DB *, int, int, int *, int *, int);
int	bulk_delete_sec(DB_ENV *, DB *, int, int, int *, int *, int);
int	bulk_fill(DB_ENV *, DB *, int, int, int *, int *, int);
int	bulk_get(DB_ENV *, DB *, int, int, int, int *, int);
int	compare_int(DB *, const DBT *, const DBT *);
DB_ENV	*db_init(char *, char *, u_int);
int	get_first_str(DB *, const DBT *, const DBT *, DBT *);
int	get_string(const char *, char *, int);
int	main(int, char *[]);
void	usage(void);

const char	*progname = "ex_bulk";                      /* Program name */
const char	tstring[STRLEN] = "0123456789abcde";        /* Const string */

struct data {
	int	id;
	char	str[STRLEN];
};

int
main(argc, argv)
	int argc;
	char *argv[];
{
	extern char *optarg;
	extern int optind;
	DB *dbp, *sdbp;
	DB_ENV *dbenv;
	DB_TXN *txnp;
	struct timeval start_time, end_time;
	double secs;
	u_int cache, pagesize;
	int biter, ch, count, dups, init, iter, num;
	int ret, rflag, sflag, bulk, delete, pair, verbose;

	dbp = sdbp = NULL;
	dbenv = NULL;
	txnp = NULL;
	iter = num = 1000000;
	dups = init = rflag = sflag = bulk = delete = verbose = 0;

	pagesize = 65536;
	cache = 1000 * pagesize;

	while ((ch = getopt(argc, argv, "c:d:i:n:p:vDIRSU")) != EOF)
		switch (ch) {
		case 'c':
			cache = (u_int)atoi(optarg);
			break;
		case 'd':
			dups = atoi(optarg);
			break;
		case 'i':
			iter = atoi(optarg);
			break;
		case 'n':
			num = atoi(optarg);
			break;
		case 'p':
			pagesize = (u_int)atoi(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		case 'D':
			delete = 1;
			break;
		case 'I':
			init = 1;
			break;
		case 'R':
			rflag = 1;
			break;
		case 'S':
			sflag = 1;
			break;
		case 'U':
			bulk = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	/* Remove the previous environment and database(s). */
	if (!rflag) {
		system(CLEANUP_CMD);
		system("mkdir EX_BULK");
	}

	if ((dbenv = db_init("EX_BULK", "ex_bulk", cache)) == NULL)
		return (-1);
	if (init)
		exit(0);

	/* Create and initialize database object, open the database. */
	if ((ret = db_create(&dbp, dbenv, 0)) != 0) {
		fprintf(stderr,
		    "%s: db_create: %s\n", progname, db_strerror(ret));
		exit(EXIT_FAILURE);
	}
	dbp->set_errfile(dbp, stderr);
	dbp->set_errpfx(dbp, progname);
	if ((ret = dbp->set_bt_compare(dbp, compare_int)) != 0) {
		dbp->err(dbp, ret, "set_bt_compare");
		goto err;
	}
	if ((ret = dbp->set_pagesize(dbp, pagesize)) != 0) {
		dbp->err(dbp, ret, "set_pagesize");
		goto err;
	}
	if (dups && (ret = dbp->set_flags(dbp, DB_DUP)) != 0) {
		dbp->err(dbp, ret, "set_flags");
		goto err;
	}

	if ((ret = dbenv->txn_begin(dbenv, NULL, &txnp, 0)) != 0)
		goto err;

	if ((ret = dbp->open(dbp, txnp, DATABASE, "primary", DB_BTREE,
	    DB_CREATE , 0664)) != 0) {
		dbp->err(dbp, ret, "%s: open", DATABASE);
		if (txnp != NULL)
			(void)txnp->abort(txnp);
		goto err;
	}

	if (sflag) {
		/* 
		 * Open secondary database. The keys in secondary database 
		 * are the first charactor in str of struct data in data
		 * field of primary database.
		 */
		if ((ret = db_create(&sdbp, dbenv, 0)) != 0) {
			fprintf(stderr, "%s: db_create: %s\n",
			    progname, db_strerror(ret));
			exit(EXIT_FAILURE);
		}
		if ((ret = sdbp->set_flags(sdbp, DB_DUPSORT)) != 0) {
			sdbp->err(sdbp, ret, "set_flags");
			goto err;
		}
		if ((ret = sdbp->open(sdbp, txnp, DATABASE, "secondary",
		    DB_BTREE, DB_CREATE, 0664)) != 0) {
			sdbp->err(sdbp, ret, "%s: secondary open", DATABASE);
			if (txnp != NULL)
				(void)txnp->abort(txnp);
			goto err;
		}
		if ((ret =  dbp->associate(dbp, txnp, sdbp, get_first_str,
		     0)) != 0) {
			dbp->err(dbp, ret, "%s: associate", DATABASE);
			if (txnp != NULL)
				(void)txnp->abort(txnp);
			goto err;
		}
	}

	if ((ret = txnp->commit(txnp, 0)) != 0)
		goto err;
	txnp = NULL;

	if (rflag) {
		/* Time the get loop. */
		(void)gettimeofday(&start_time, NULL);
		if ((ret = bulk_get(
		    dbenv, dbp, num, dups, iter, &count, verbose)) != 0)
			goto err;
		(void)gettimeofday(&end_time, NULL);
		secs =
		    (((double)end_time.tv_sec * 1000000 + 
		    end_time.tv_usec) -
		    ((double)start_time.tv_sec * 1000000 + 
		    start_time.tv_usec)) / 1000000;
		printf("[STAT] Read %d records read using %d batches",
		    count, iter);
		printf(" in %.2f seconds: ", secs);
		printf("%.0f records/second\n", (double)count / secs);
	} else {
		/* Time the fill loop. */
		(void)gettimeofday(&start_time, NULL);
		if ((ret = bulk_fill(dbenv, dbp, num, dups, &count,
		    &biter, verbose)) != 0)
			goto err;
		(void)gettimeofday(&end_time, NULL);
		secs = (((double)end_time.tv_sec * 1000000 + 
		    end_time.tv_usec) -
		    ((double)start_time.tv_sec * 1000000 +
		    start_time.tv_usec)) / 1000000;
		printf("[STAT] Insert %d records using %d batches",
		    count, biter);
		printf(" in %.2f seconds: ", secs);
		printf("%.0f records/second\n", (double)count / secs);

		if (delete) {
			if (sflag) {
				pair = rand() % 2;
				/* Time the delete loop in secondary db */
				(void)gettimeofday(&start_time, NULL);
				if ((ret = bulk_delete_sec(dbenv, sdbp, num,
				    pair, &count, &iter, verbose)) != 0)
					goto err;
				(void)gettimeofday(&end_time, NULL);
				secs = (((double)end_time.tv_sec * 1000000 + 
				    end_time.tv_usec) -
				    ((double)start_time.tv_sec * 1000000 + 
				    start_time.tv_usec)) / 1000000;
				printf("[STAT] Delete %d %s using %d batches",
				    count, (pair) ? "records" : "keys", iter);
				printf(" in %.2f seconds: ", secs);
				printf("%.0f records/second\n", 
				    (double)count / secs);
			} else {
				/* Time the delete loop in primary db */
				(void)gettimeofday(&start_time, NULL);
				if ((ret = bulk_delete(dbenv, dbp, num, dups, 
				    &count, &iter, verbose)) != 0)
					goto err;
				(void)gettimeofday(&end_time, NULL);
				secs = (((double)end_time.tv_sec * 1000000 + 
				    end_time.tv_usec) -
				    ((double)start_time.tv_sec * 1000000 + 
				    start_time.tv_usec)) / 1000000;
				printf(
"[STAT] Delete %d records using %d batches",
				    count, iter);
				printf(" in %.2f seconds: ",  secs);
				printf("%.0f records/second\n",  
				    (double)count / secs);
			}
		} 
	}

	/* Close everything down. */
	if (sflag) 
		if ((ret = sdbp->close(sdbp, rflag ? DB_NOSYNC : 0)) != 0) {
			fprintf(stderr, "%s: DB->close: %s\n",
			    progname, db_strerror(ret));
			return (1);
		}

	if ((ret = dbp->close(dbp, rflag ? DB_NOSYNC : 0)) != 0) {
		fprintf(stderr,
		    "%s: DB->close: %s\n", progname, db_strerror(ret));
		return (1);
	}
	return (ret);

err:
	if (sflag)
		(void)sdbp->close(sdbp, 0);
	(void)dbp->close(dbp, 0);
	return (1);
}

/*
 * bulk_delete - bulk_delete from a db
 *	Since we open/created the db with transactions, we need to delete
 * from it with transactions.  We'll bundle the deletes UPDATES_PER_BULK_PUT
 * to a transaction.
 */
int
bulk_delete(dbenv, dbp, num, dups, countp, iterp, verbose)
	DB_ENV *dbenv;
	DB *dbp;
	int num, dups, verbose;
	int *countp, *iterp;
{
	DBT key;
	DB_TXN *txnp;
	struct data *data_val;
	u_int32_t flag;
	int count, i, j, iter, ret;
	void *ptrk;

	txnp = NULL;
	count = flag = iter = ret = 0;
	memset(&key, 0, sizeof(DBT));

	j = rand() % num;

	/*
	 * Need to account for proper buffer size, the buffer must be at 
	 * least as large as the page size of the underlying database, 
	 * aligned for unsigned integer access, and be a multiple of 1024
	 * bytes in size.
	 */
	key.ulen = (u_int32_t)UPDATES_PER_BULK_PUT *
	    (sizeof(u_int32_t) + DATALEN) * 1024;
	key.flags = DB_DBT_USERMEM | DB_DBT_BULK;
	key.data = malloc(key.ulen);
	memset(key.data, 0, key.ulen);
	data_val = malloc(DATALEN);
	memset(data_val, 0, DATALEN);

	/*
	 * If DB_MULTIPLE, delete all records with a specified set of keys
	 * in a DBT. The DBT is constructed by DB_MULTIPLE_WRITE_NEXT. If 
	 * DB_MULTIPLE_KEY, delete a specific set of key/data pairs in the
	 * DBT constructed by DB_MULTIPLE_KEY_WRITE_NEXT. Here, delete 
	 * keys before the random key, if there are duplicate records, 
	 * delete duplicate pairs with DB_MULTIPLE_KEY, unless, delete keys
	 * with DB_MULTIPLE.
	 */
	flag |= (dups) ? DB_MULTIPLE : DB_MULTIPLE_KEY;
	DB_MULTIPLE_WRITE_INIT(ptrk, &key);
	for (i = 0; i < j; i++) {
		if (i % UPDATES_PER_BULK_PUT == 0) {
			if (txnp != NULL) {
				if ((ret = txnp->commit(txnp, 0)) != 0)
					goto err;
				txnp = NULL;
			}
			if ((ret =
				dbenv->txn_begin(dbenv, NULL, &txnp, 0)) != 0)
				goto err;
		}
		
		if (dups) {
			DB_MULTIPLE_WRITE_NEXT(ptrk, &key, &i, sizeof(i));
			assert(ptrk != NULL);
			count++;
			if (verbose)
				printf("Delete key: %d\n", i);
		} else {
			data_val->id = 0;
			do {
				get_string(tstring, data_val->str, i);
				DB_MULTIPLE_KEY_WRITE_NEXT(ptrk, &key, &i,
				    sizeof(i), data_val, DATALEN);
				assert(ptrk != NULL);
				count++;
				if (verbose)
					printf(
"Delete key: %d, \tdata: (id %d, str %s)\n", 
					    i, data_val->id, data_val->str);
			} while (++data_val->id < dups);
		}

		if ((i + 1) % UPDATES_PER_BULK_PUT == 0) {
			switch (ret = dbp->del(dbp, txnp, &key, flag)) {
			case 0:
				iter++;
				DB_MULTIPLE_WRITE_INIT(ptrk, &key);
				break;
			default:
				dbp->err(dbp, ret, "Bulk DB->del");
				goto err;
			}
		}
	}
	if ((j % UPDATES_PER_BULK_PUT) != 0) {
		switch (ret = dbp->del(dbp, txnp, &key, flag)) {
		case 0:
			iter++;
			break;
		default:
			dbp->err(dbp, ret, "Bulk DB->del");
			goto err;
		}
	}

	if (txnp != NULL) {
		ret = txnp->commit(txnp, 0);
		txnp = NULL;
	}

	*countp = count;
	*iterp = iter;

err:	if (txnp != NULL)
		(void)txnp->abort(txnp);
	free(data_val);
	free(key.data);
	return (ret);
}

/*
 * bulk_delete_sec - bulk_delete_sec from a secondary db
 */
int
bulk_delete_sec(dbenv, dbp, num, pair, countp, iterp, verbose)
	DB_ENV *dbenv;
	DB *dbp;
	int num, verbose, pair;
	int *countp, *iterp;
{
	DBT key;
	DB_TXN *txnp;
	u_int32_t flag;
	int count, i, iter, j, k, rc, ret;
	void *ptrk;
	char ch;

	txnp = NULL;
	count = flag = iter = ret = 0;
	memset(&key, 0, sizeof(DBT));
	rc = rand() % (STRLEN - 1);

	/*
	 * Need to account for proper buffer size, the buffer must be at
	 * least as large as the page size of the underlying database, 
	 * aligned for unsigned integer access, and be a multiple of 
	 * 1024 bytes in size.
	 */
	key.ulen = (u_int32_t)UPDATES_PER_BULK_PUT *
	    (sizeof(u_int32_t) + DATALEN) * 1024;
	key.flags = DB_DBT_USERMEM | DB_DBT_BULK;
	key.data = malloc(key.ulen);
	memset(key.data, 0, key.ulen);

	/*
	 * Bulk delete records from a random key, which is one of charaters
	 * in tstring. If DB_MULTIPLE, delete all characters before the random
	 * key in the tstring. If DB_MULTIPLE_KEY, get duplicate data to the
	 * specified keys and delete key/data pairs.
	 */
	flag |= (pair) ? DB_MULTIPLE_KEY : DB_MULTIPLE;
	DB_MULTIPLE_WRITE_INIT(ptrk, &key);
	for (i = 0; i <= rc; i++) {
		if (i % UPDATES_PER_BULK_PUT == 0) {
			if (txnp != NULL) {
				if ((ret = txnp->commit(txnp, 0)) != 0)
					goto err;
				txnp = NULL;
			}
			if ((ret = dbenv->txn_begin(
			    dbenv, NULL, &txnp, 0)) != 0)
				goto err;
		}

		ch = tstring[i];
		if (!pair) {
			DB_MULTIPLE_WRITE_NEXT(ptrk, &key, &ch, sizeof(ch));
			assert(ptrk != NULL);
			count++;
			if (verbose)
				printf("Delete key: %c\n", ch);
		} else {
			j = 0;
			do {
				k = j * (STRLEN - 1) + i;
				DB_MULTIPLE_KEY_WRITE_NEXT(ptrk, &key, &ch,
				    sizeof(ch), &k, sizeof(k));
				assert(ptrk != NULL);
				count++;
				if (verbose)
					printf(
"Delete secondary key: %c, \tdata: %d\n", 
					    ch, k);
			} while (++j < (int)(num / (STRLEN - 1)));
		}

		if ((i + 1) % UPDATES_PER_BULK_PUT == 0) {
			switch (ret = dbp->del(dbp, txnp, &key, flag)) {
			case 0:
				iter++;
				DB_MULTIPLE_WRITE_INIT(ptrk, &key);
				break;
			default:
				dbp->err(dbp, ret, "Bulk DB->del");
				goto err;
			}
		}
	}
	if ((rc % UPDATES_PER_BULK_PUT) != 0) {
		switch (ret = dbp->del(dbp, txnp, &key, flag)) {
		case 0:
			iter++;
			break;
		default:
			dbp->err(dbp, ret, "Bulk DB->del");
			goto err;
		}
	}

	if (txnp != NULL) {
		ret = txnp->commit(txnp, 0);
		txnp = NULL;
	}

	*countp = count;
	*iterp = iter;	

err:	if (txnp != NULL)
		(void)txnp->abort(txnp);
	free(key.data);
	return (ret);
}

/*
 * bulk_fill - bulk_fill a db
 *	Since we open/created the db with transactions, we need to populate
 * it with transactions. We'll bundle the puts UPDATES_PER_BULK_PUT to a 
 * transaction.
 */
int
bulk_fill(dbenv, dbp, num, dups, countp, iterp, verbose)
	DB_ENV *dbenv;
	DB *dbp;
	int num, dups, verbose;
	int *countp, *iterp;
{
	DBT key, data;
	u_int32_t flag;
	DB_TXN *txnp;
	struct data *data_val;
	int count, i, iter, ret;
	void *ptrk, *ptrd;

	txnp = NULL;
	count = flag = iter = ret = 0;
	ptrk = ptrd = NULL;
	data_val = malloc(DATALEN);
	memset(data_val, 0, DATALEN);
	memset(&key, 0, sizeof(DBT));
	memset(&data, 0, sizeof(DBT));

	/* 
	 * Need to account for proper buffer size,
	 * The buffer must be at least as large as the page size of
	 * the underlying database, aligned for unsigned integer
	 * access, and be a multiple of 1024 bytes in size.
	 */
	key.ulen = (u_int32_t) UPDATES_PER_BULK_PUT * 
	    (sizeof(u_int32_t) + DATALEN) * 1024;
	key.flags = DB_DBT_USERMEM | DB_DBT_BULK;
	key.data = malloc(key.ulen);
	memset(key.data, 0, key.ulen);

	data.ulen = (u_int32_t)UPDATES_PER_BULK_PUT * 
	    (u_int32_t)DATALEN * 1024;
	data.flags = DB_DBT_USERMEM | DB_DBT_BULK;
	data.data = malloc(data.ulen);
	memset(data.data, 0, data.ulen);

	/*
	 * We could bulk insert with either DB_MULTIPLE in two buffers or 
	 * DB_MULTIPLE_KEY in one buffer. With DB_MULTIPLE, all keys are 
	 * constructed in key DBT, all data is constructed in data DBT. 
	 * With DB_MULTIPLE_KEY, all key/data pairs are constructed in 
	 * the key DBT. Here, we use DB_MULTIPLE mode when there are 
	 * duplicate records.
	 */
	flag |= (dups) ? DB_MULTIPLE : DB_MULTIPLE_KEY;
	DB_MULTIPLE_WRITE_INIT(ptrk, &key);
	if (dups)
		DB_MULTIPLE_WRITE_INIT(ptrd, &data);
	for (i = 0; i < num; i++) {
		if (i % UPDATES_PER_BULK_PUT == 0) {
			if (txnp != NULL) {
				if ((ret = txnp->commit(txnp, 0)) != 0)
					goto err;
				txnp = NULL;
			}
			if ((ret = 
			    dbenv->txn_begin(dbenv, NULL, &txnp, 0)) != 0)
				goto err;
		}
		data_val->id = 0;
		do {
			get_string(tstring, data_val->str, i);
			if (dups) {
				DB_MULTIPLE_WRITE_NEXT(ptrk, &key, 
				    &i, sizeof(i));
				assert(ptrk != NULL);
				DB_MULTIPLE_WRITE_NEXT(ptrd, &data, 
				    data_val, DATALEN);
				assert(ptrd != NULL);
			} else {
				DB_MULTIPLE_KEY_WRITE_NEXT(ptrk, 
				    &key, &i, sizeof(i), data_val, DATALEN);
				assert(ptrk != NULL);
			}
			if (verbose)
				printf(
"Insert key: %d, \t data: (id %d, str %s)\n", 
				    i, data_val->id, data_val->str);
			count++;
		} while (++data_val->id < dups);
		if ((i + 1) % UPDATES_PER_BULK_PUT == 0) {
			switch (ret = dbp->put(dbp, txnp, &key, &data, flag)) {
			case 0:
				iter++;
				DB_MULTIPLE_WRITE_INIT(ptrk, &key);
				if (dups)
					DB_MULTIPLE_WRITE_INIT(ptrd, &data);
				break;
			default:
				dbp->err(dbp, ret, "Bulk DB->put");
				goto err;
			} 
		}
	} 
	if ((num % UPDATES_PER_BULK_PUT) != 0) {
		switch (ret = dbp->put(dbp, txnp, &key, &data, flag)) {
			case 0:
				iter++;
				break;
			default:
				dbp->err(dbp, ret, "Bulk DB->put");
				goto err;
		}
	}

	if (txnp != NULL) {
		ret = txnp->commit(txnp, 0);
		txnp = NULL;
	}

	*countp = count;
	*iterp = iter;

err:
	if (txnp != NULL)
		(void)txnp->abort(txnp);
	free(key.data);
	free(data.data);
	free(data_val);
	return (ret);
}

/*
 * bulk_get -- loop getting batches of records.
 */
int
bulk_get(dbenv, dbp, num, dups, iter, countp, verbose)
	DB_ENV *dbenv;
	DB *dbp;
	int num, dups, iter, *countp, verbose;
{
	DBC *dbcp;
	DBT key, data;
	DB_TXN *txnp;
	u_int32_t flags, len, klen;
	int count, i, j, ret;
	void *pointer, *dp, *kp;

	klen = count = ret = 0;
	dbcp = NULL;
	dp = kp = pointer = NULL;
	txnp = NULL;

	/* Initialize key DBT and data DBT, malloc bulk buffer. */
	memset(&key, 0, sizeof(key));
	memset(&data, 0, sizeof(data));
	key.data = &j;
	key.size = sizeof(j);
	data.flags = DB_DBT_USERMEM;
	data.data = malloc(DATALEN * 16 * 1024);
	memset(data.data, 0, DATALEN * 16 * 1024);
	data.ulen = data.size = DATALEN * 16 * 1024;

	flags = DB_SET;
	flags |= (dups) ? DB_MULTIPLE: DB_MULTIPLE_KEY;
	for (i = 0; i < iter; i++) {
		if ((ret =
		    dbenv->txn_begin(dbenv, NULL, &txnp, 0)) != 0)
			goto err;
		if ((ret = dbp->cursor(dbp, txnp, &dbcp, 0)) != 0)
			goto err;

		/*
		 * Bulk retrieve from a random key. Use DB_MULTIPLE_INIT to 
		 * initialize variables for bulk retrieval. If there are 
		 * duplicate records, use DB_MULTIPLE_NEXT to iterate them
		 * in the buffer. Unless, use DB_MULTIPLE_KEY_NEXT to iterate
		 * records after the random key.
		 */
		j = rand() % num;
		if ((ret = dbcp->get(dbcp, &key, &data, flags)) != 0)
			goto err;
		DB_MULTIPLE_INIT(pointer, &data);
		if (dups)
			while (pointer) {
				DB_MULTIPLE_NEXT(pointer, &data, dp, len);
				if (dp) {
					count++;
					if (verbose)
						printf(
"Retrieve key: %d, \tdata: (id %d, str %s)\n",
					j, ((struct data *)(dp))->id, 
					(char *)((struct data *)(dp))->str);
				}
			}
		else
			while (pointer) {
				DB_MULTIPLE_KEY_NEXT(pointer,
				    &data, kp, klen, dp, len);
				if (kp) {
					count++;
					if (verbose)
						printf(
"Retrieve key: %d, \tdata: (id %d, str %s)\n",
					*((int *)kp), ((struct data *)(dp))->id, 
					(char *)((struct data *)(dp))->str);
				}
			}

		if ((ret = dbcp->close(dbcp)) != 0)
			goto err;
		if ((ret = txnp->commit(txnp, 0)) != 0)
			goto err;
	}

	*countp = count;

err:	
	if (ret != 0)
		dbp->err(dbp, ret, "get");
	free(data.data);
	return (ret);
}

int
compare_int(dbp, a, b)
	DB *dbp;
	const DBT *a, *b;
{
	int ai, bi;

	dbp = NULL;

	/*
	 * Returns:
	 *	< 0 if a < b
	 *	= 0 if a = b
	 *	> 0 if a > b
	 */
	memcpy(&ai, a->data, sizeof(int));
	memcpy(&bi, b->data, sizeof(int));
	return (ai - bi);
}

/*
 * db_init --
 *	Initialize the environment.
 */
DB_ENV *
db_init(home, prefix, cachesize)
	char *home, *prefix;
	u_int cachesize;
{
	DB_ENV *dbenv;
	int ret;

	if ((ret = db_env_create(&dbenv, 0)) != 0) {
		dbenv->err(dbenv, ret, "db_env_create");
		return (NULL);
	}
	dbenv->set_errfile(dbenv, stderr);
	dbenv->set_errpfx(dbenv, prefix);
	(void)dbenv->set_cachesize(dbenv, 0,
	    cachesize == 0 ? 50 * 1024 * 1024 : (u_int32_t)cachesize, 0);

	if ((ret = dbenv->open(dbenv, home, DB_CREATE | DB_INIT_MPOOL |
	    DB_INIT_TXN | DB_INIT_LOCK, 0)) != 0) {
		dbenv->err(dbenv, ret, "DB_ENV->open: %s", home);
		(void)dbenv->close(dbenv, 0);
		return (NULL);
	}
	return (dbenv);
}

int
get_first_str(sdbp, key, data, skey)
	DB *sdbp;
	const DBT *key;
	const DBT *data;
	DBT *skey;
{
	sdbp = NULL;
	key = NULL;

	memset(skey, 0, sizeof(DBT));
	skey->data = ((struct data *)(data->data))->str;
	skey->size = sizeof(char);
	return (0);
}

int
get_string(src, des, off)
	const char *src;
	char *des;
	int off;
{
	int i;

	for (i = 0; i < (int)(STRLEN - 1); i++) 
		des[i] = src[(off + i) % (STRLEN - 1)];
	des[STRLEN - 1] = '\0';
	return (0);
}

void
usage()
{
	(void)fprintf(stderr, 
"Usage: %s \n\
    -c	cachesize [1000 * pagesize] \n\
    -d	number of duplicates [none] \n\
    -i	number of read iterations [1000000] \n\
    -n	number of keys [1000000] \n\
    -p	pagesize [65536] \n\
    -v	verbose output \n\
    -D  perform bulk delete \n\
    -I	just initialize the environment \n\
    -R	perform bulk read \n\
    -S	perform bulk read in secondary database \n\
    -U  perform bulk update \n",
	    progname);
	exit(EXIT_FAILURE);
}


// created  ex_bulk.db  in "EX_BULK" directory 

