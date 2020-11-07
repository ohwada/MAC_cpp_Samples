/**
 * zlib sample
 * 2020-07-01 K.OHWADA
 */


// compress and decompress file

// gcc comp_decomp_file.c `pkg-config --cflags --libs zlib` 

// original : http://www.zlib.net/zlib_how.html

/* example of proper use of zlib's inflate() and deflate()
   Not copyrighted -- provided to the public domain
   Version 1.4  11 December 2005  Mark Adler */

/* Version history:
   1.0  30 Oct 2004  First version
   1.1   8 Nov 2004  Add void casting for unused return values
                     Use switch statement for inflate() return values
   1.2   9 Nov 2004  Add assertions to document zlib guarantees
   1.3   6 Apr 2005  Remove incorrect assertion in inf()
   1.4  11 Dec 2005  Add hack to avoid MSDOS end-of-line conversions
                     Avoid some compiler warnings for input and output buffers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384


// prototype
bool compFile(char *input, char *output);
bool decompFile(char *input, char *output);
int compFileStream(FILE *source, FILE *dest, int level);
int decompFileStream(FILE *source, FILE *dest);
void zerr(int ret);


/**
 * compFile
 */
bool compFile(char *input, char *output)
{

    FILE *fin;
    FILE *fout;
    bool is_error = false;

    fin = fopen(input, "rb");
    if (!fin) {
        fprintf(stderr, "Can't open %s \n", input);
        return false;
    }

    fout = fopen(output, "wb");
    if (!fout) {
        fprintf(stderr, "Can't open %s \n", output);
        return false;
    }

    int ret = compFileStream(fin, fout, Z_DEFAULT_COMPRESSION);
    if (ret != Z_OK) {
            zerr(ret);
            is_error = true;
    }

    fclose(fin);

    fflush(fout);
    fclose(fout);

    return !is_error;
}


/**
 * decompFile
 */
bool decompFile(char *input, char *output)
{

    FILE *fin;
    FILE *fout;
    bool is_error = false;

    fin = fopen(input, "rb");
    if (!fin) {
        fprintf(stderr, "Can't open %s \n", input);
        return false;
    }

    fout = fopen(output, "wb");
    if (!fout) {
        fprintf(stderr, "Can't open %s \n", output);
        return false;
    }

    int ret = decompFileStream(fin, fout);
    if (ret != Z_OK) {
            zerr(ret);
            is_error = true;
    }

    fclose(fin);

    fflush(fout);
    fclose(fout);

    return !is_error;
}


/* Compress from file source to file dest until EOF on source.
   def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_STREAM_ERROR if an invalid compion
   level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
   version of the library linked do not match, or Z_ERRNO if there is
   an error reading or writing the files. 
*/
int compFileStream(FILE *source, FILE *dest, int level)
{
    int ret, flush;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate deflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;

    /* comp until end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)deflateEnd(&strm);
            return Z_ERRNO;
        }
        flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compion if all of source has been read in */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)deflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);
    return Z_OK;
}

/* Decomp from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. 
*/
int decompFileStream(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;

    /* decomp until deflate stream ends or end of file */
    do {
        strm.avail_in = fread(in, 1, CHUNK, source);
        if (ferror(source)) {
            (void)inflateEnd(&strm);
            return Z_ERRNO;
        }
        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
                ret = Z_DATA_ERROR;     /* and fall through */
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return ret;
            }
            have = CHUNK - strm.avail_out;
            if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
                (void)inflateEnd(&strm);
                return Z_ERRNO;
            }
        } while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);

    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}


/**
* report a zlib or i/o error 
*/
void zerr(int ret)
{
    fputs("zpipe: ", stderr);
    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            fputs("error reading stdin\n", stderr);
        if (ferror(stdout))
            fputs("error writing stdout\n", stderr);
        break;
    case Z_STREAM_ERROR:
        fputs("invalid compion level\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("zlib version mismatch!\n", stderr);
    }
}


/**
 * main
 */
int main(int argc, char **argv)
{

    char *flie_in = "data/sample.txt";
    char *file_out = "sample_out.txt";
    char *file_tmp = "temp.zlib";

    if(argc ==3){
        flie_in = argv[1];
        file_out = argv[2];
    } else {
        printf("Usage: %s [inputFile] [outputFile]  \n", argv[0] );
    }


    bool ret1 = compFile(flie_in, file_tmp);
    if(ret1){
        printf("saved to: %s \n", file_tmp);
    } else {
        return EXIT_FAILURE;
    }


    bool ret2 = decompFile(file_tmp, file_out);
    if(ret2){
        printf("saved to: %s \n", file_out);
    } else {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}


// saved to: temp.zlib 
// saved to: sample_out.txt 

