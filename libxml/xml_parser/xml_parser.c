/**
 * xml_parser.cpp
 * 2022-06-01 K.OHWADA
 */

// XML Parser
// extract the element name and value from XML file
// modify reader2.c
// original : http://www.xmlsoft.org/examples/

#include <stdio.h>
#include <libxml/xmlreader.h>

 xmlChar* ele_name;


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
 *
 * Dump information about the current node
 */
static void
processNode(xmlTextReaderPtr reader) {
    const xmlChar *name, *value;

    name = xmlTextReaderConstName(reader);
    if (name == NULL) {
	    // name = BAD_CAST "--";
    }

    value = xmlTextReaderConstValue(reader);

    int type = xmlTextReaderNodeType(reader);
    if(type == XML_READER_TYPE_ELEMENT) {
        if (name) {
            ele_name = (xmlChar *)name;
        }
   } else if (type == XML_READER_TYPE_TEXT) {
        if ( ele_name && name ) {
            printf("\n %s : %s \n", ele_name, value);
        }
    }

    // print_info(reader);
}


/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse, validate and print information about an XML file.
 */
static void
streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;


    /*
     * Pass some special parsing options to activate DTD attribute defaulting,
     * entities substitution and DTD validation
     */
    reader = xmlReaderForFile(filename, NULL,
                 XML_PARSE_DTDATTR |  /* default DTD attributes */
		 XML_PARSE_NOENT ); /* substitute entities */
		 // XML_PARSE_DTDVALID); /* validate with the DTD */

    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
	/*
	 * Once the document has been fully parsed check the validation results
	 */
	if (xmlTextReaderIsValid(reader) != 1) {
	        // fprintf(stderr, "Document %s does not validate\n", filename);
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
    char* file = (char *)"examples.xml";

    if (argc == 2) {
        file = argv[1];
    } else {
       printf("Usage: %s <xmlFile> \n", argv[0] );
    }

    printf("file: %s \n", file );

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    streamFile(file);

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return 0;
}

