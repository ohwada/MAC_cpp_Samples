/**
 *  http_upload_server.c
 * 2022-06-01 K.OHWADA
 */

// Streaming upload example. Demonstrates how to use chunked encoding
// original : https://github.com/cesanta/mongoose/blob/master/examples/file-upload-single-post/main.c

// See detailed tutorial at https://mongoose.ws/tutorials/file-uploads/

// to send large payload in smaller chunks. To test, use curl utility:
//
// curl http://localhost:8000/upload?name=a.txt --data-binary @large_file.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h"
#include "request_parser.h"
#include "file_util.h"


const char* DIR_ROOT = "www";

// global
FILE *fp = NULL;


/**
 *  get_filepath
 */
void get_filepath( struct mg_str str_query,  char* fname, char* fpath)
{
    const size_t BUFSIZE = 128;
    char query[BUFSIZE];

    strncpy( (char*)query, str_query.ptr, (int)str_query.len);
    printf("query: %s \n", query);

    parse_query( (char*)query, fname );
    printf("name: %s \n", fname);

//  It is better to separate document root and the upload destination directory
// in this version set the same directoy to simplify the program
    make_path( (char *)DIR_ROOT,   fname, (char *)fpath);
    printf("path: %s \n", fpath);
}


// HTTP request handler function. It implements the following endpoints:
//   /upload - Saves the next file chunk
//   all other URI - serves www/ directory
void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) 
{
    const size_t BUFSIZE = 256;
    char filename[BUFSIZE];
    char filepath[BUFSIZE];
    char response[BUFSIZE];

const char FORMAT[] = 
"<h2>uploaded</h2><font size='+2'><a href='%s'>%s</a></font>";

    char* headers = 
"Content-Type: text/html; chrset=utf-8\r\n";

  struct mg_http_message *hm = (struct mg_http_message *) ev_data;
  if (ev == MG_EV_HTTP_CHUNK && mg_http_match_uri(hm, "/upload")) {
if(!fp){
    get_filepath(hm->query, (char *)filename, (char *)filepath);
// remove previously uploaded file
    remove( (char *)filepath);
// additional writing
    fp = fopen( (char *)filepath, "wb+");
    if(!fp){
        fprintf(stderr, "cannot open: %s : %s \n", 
        filepath, strerror( errno) );
    }
}
// HTTP chunk (partial msg)
    MG_INFO(("Got chunk len %lu", (unsigned long) hm->chunk.len));
    MG_INFO(("Query string: [%.*s]", (int) hm->query.len, hm->query.ptr));
    // MG_INFO(("Chunk data:\n%.*s", (int) hm->chunk.len, hm->chunk.ptr));
if(fp){
    size_t write_size = fwrite( (char *)hm->chunk.ptr, sizeof(char), hm->chunk.len, fp);
    printf("write %zu bytes \n", write_size);
}
    mg_http_delete_chunk(c, hm);
    if (hm->chunk.len == 0) {
       MG_INFO(("Last chunk received, sending response"));
// send response
        if(fp){
            fclose(fp);
            fp = NULL;
            printf("save to: %s \n", filepath);
// send response
            snprintf( (char *)response, BUFSIZE, (char *)FORMAT, (char *)filename, (char *)filename);
            printf("response: %s \n", response);
            mg_http_reply(c, 200, headers, (char *)response);
        } else {
// send response
            mg_http_reply(c, 200, "", "ok (chunked)\n");
        }
    }
  } else if (ev == MG_EV_HTTP_MSG && mg_http_match_uri(hm, "/upload")) {
// request info
    MG_INFO(("Got all %lu bytes!", (unsigned long) hm->body.len));
    MG_INFO(("Query string: [%.*s]", (int) hm->query.len, hm->query.ptr));
    // MG_INFO(("Body:\n%.*s", (int) hm->body.len, hm->body.ptr));
// send response
    //mg_http_reply(c, 200, "", "ok (%lu)\n", (unsigned long) hm->body.len);
  } else if (ev == MG_EV_HTTP_MSG) {
// request
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        print_mg_str("method",  hm->method);
        print_mg_str("uri",  hm->uri);
// send response
    struct mg_http_serve_opts opts = {.root_dir = DIR_ROOT};
    mg_http_serve_dir(c, hm, &opts);
  }
}


/**
 *  main
 */
int main(void) 
{

    unsigned short port = 8000;

    run_server(port);


  return 0;
}
