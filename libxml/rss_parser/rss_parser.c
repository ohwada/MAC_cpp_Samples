/**
 * rss_parser.cpp
 * 2022-06-01 K.OHWADA
 */

// RSS Parser
// extract the Title and pubDate from RSS Feeds 
// modify reader2.c 
// reference : http://www.xmlsoft.org/examples/

#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>

const xmlChar* IMAGE = BAD_CAST"image";
const xmlChar* ITEM = BAD_CAST"item";
const xmlChar* TITLE = BAD_CAST"title";
const xmlChar* PUBDATE = BAD_CAST"pubDate";
bool is_image_start = false;
bool is_item_start = false;
bool is_title_start = false;
bool is_pubDate_start = false;


/**
 * print_info
 */
void print_info(xmlTextReaderPtr reader)
{
    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);
    value = xmlTextReaderConstValue(reader);

    int depth = xmlTextReaderDepth(reader);
    int type = xmlTextReaderNodeType(reader);
    int is_empty = xmlTextReaderIsEmptyElement(reader);
    int has_value = xmlTextReaderHasValue(reader);

    printf("%d %d %s %d %d", 
	    depth,
	    type,
	    name,
	    is_empty,
	    has_value);
        if (value == NULL){
	        printf("\n");
        }else {
            if (xmlStrlen(value) > 40){
                printf(" %.40s...\n", value);
            } else {
	            printf(" %s\n", value);
            }
        }
}


/**
 * processNode:
 * @reader: the xmlReader
 * Dump information about the current node
 */
static void
processNode(xmlTextReaderPtr reader) 
{
    const xmlChar *name, *value;
    bool is_image = false;
    bool is_item = false;
    bool is_title = false;
bool is_pubDate = false;

    name = xmlTextReaderConstName(reader);
    int ret1 = xmlStrEqual(name, IMAGE);
    if( ret1 == 1){
        is_image = true;
    }
    int ret2 = xmlStrEqual(name, ITEM);
    if( ret2 == 1){
        is_item = true;
    }
    int ret3 = xmlStrEqual(name, TITLE);
    if( ret3 == 1){
        is_title = true;
    }
    int ret4 = xmlStrEqual(name, PUBDATE);
    if( ret4 == 1){
        is_pubDate = true;
    }

    value = xmlTextReaderConstValue(reader);

    int type = xmlTextReaderNodeType(reader);
    if(type == XML_READER_TYPE_ELEMENT){
        if(is_image) {
            is_image_start = true;
        } else if(is_item) {
            is_item_start = true;
            printf("\n");
        } else if(is_title) {
            is_title_start = true;
        } else if(is_pubDate) {
            is_pubDate_start = true;
        }

    } else if (type == XML_READER_TYPE_TEXT){
        if(is_title_start) {
            if(is_item_start) {
                printf("title: %s \n", value);
            } else if( is_image_start ) {
                printf("image title: %s \n", value);
            } else {
                printf("site title: %s \n", value);
            }
            is_title_start = false;
        } else if(is_pubDate_start) {
            printf("pubDate: %s \n", value);
            is_pubDate_start = false;
        }  else {
            // is_title_start = false;
            // is_pubDate_start = false;
        }
    }

    // print_info(reader);
}


/**
 * streamFile:
 * @filename: the file name to parse
 * Parse, validate and print information about an XML file.
 */
static void
streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(filename, NULL,
            XML_PARSE_DTDATTR |  /* default DTD attributes */
	        XML_PARSE_NOENT );   /* substitute entities */

    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }

        xmlFreeTextReader(reader);
        if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}


/**
 * main
 */
int main(int argc, char **argv) 
{
    char* file = (char *)"sample.xml";

    if (argc == 2) {
        file = argv[1];
    } else {
       printf("Usage: %s <rssFile> \n", argv[0] );
    }

    printf("file: %s \n", file );

    streamFile(file);
    xmlCleanupParser();
    xmlMemoryDump();

    return 0;
}


