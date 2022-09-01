/**
 * zip_util.h
 * 2022-06-01 K.OHWADA
 */


#include <stdbool.h>
#include <string.h>

// prototype
void get_parent_list(char *fullpath, int *listsize, int num, int bufsize, char list[num][bufsize] );
bool is_zip_dir(char *name);


/**
 * get_parent_list
 */
void get_parent_list(char *fullpath, int *listsize, int num, int bufsize, char list[num][bufsize] ) 
{
    const char SLASH = '/';
	const char NUL = '\0';

    int len = strlen(fullpath);
char buf[len+1];
strcpy(buf, fullpath);

int cnt = 0;
while(1)
{
    char *p = strrchr(buf, SLASH);
    if(!p) {
        break;
    }

     *p = NUL;
	// printf("%s \n", buf);
	cnt++;
}

int listnum = cnt;

strcpy(buf, fullpath);
for(int i=0; i<listnum; i++)
{
    char *p = strrchr(buf, SLASH);
    if(!p) {
        break;
    }

     *p = NUL;
	strcpy(list[listnum- i-1], buf);
}

    *listsize = listnum;
    return;
}

/**
 *  is_zip_dir
 */
// https://stackoverflow.com/questions/56480947/does-libzip-provides-a-way-to-check-if-zip-file-is-a-directory
bool is_zip_dir(char *name)
{
 	const char SLASH = '/';
	char last = name[strlen(name)-1];
	bool ret = (last == SLASH)? true: false;
 	return ret;
}


