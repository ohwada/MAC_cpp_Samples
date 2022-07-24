/**
 * html_parser_url.cpp
 * 2022-06-01 K.OHWADA
 */


// parse while downloading
// reference : https://ykot.hateblo.jp/entry/20110106/1294280278

// g++  html_parser_url.cpp -o url `xml2-config --cflags` `xml2-config --libs` -lcurl

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include <curl/curl.h>
// #include <curl/types.h>
// #include <curl/easy.h>

#include <libxml/HTMLparser.h>

static char errorBuffer[CURL_ERROR_SIZE];
static std::string buffer;

static htmlParserCtxtPtr ctxt;


/**
 * writer
 */
static int writer(char *data, size_t size, size_t nmemb,
                  std::string *writerData)
{
    if (writerData == NULL)
        return 0;

    // for full text acquisition
    writerData->append(data, size*nmemb);

    // parse
    htmlParseChunk(ctxt, data, size*nmemb, 0);

    return size * nmemb;
}


/**
 * curl_init
 */
static bool curl_init(CURL *&conn, char *url)
{
    CURLcode code;
    conn = curl_easy_init();

    if (conn == NULL) {
        fprintf(stderr, "Failed to create CURL connection\n");
        exit(EXIT_FAILURE);
    }

    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to set error buffer [%d]\n", code);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_URL, url);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to set URL [%s]\n", errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to set redirect option [%s]\n", errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to set writer [%s]\n", errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to set write data [%s]\n", errorBuffer);
        return false;
    }

    return true;
}


// callback for html parser 
/**
 * isStandaloneDebug:
 * @ctxt:  An XML parser context
 *
 * Is this document tagged standalone ?
 *
 * Returns 1 if true
 */
int isStandaloneDebug(void *ctx)
{
    fprintf(stdout, "SAX.isStandalone()\n");
    return(0);
}


/**
 * hasInternalSubsetDebug:
 * @ctxt:  An XML parser context
 *
 * Does this document has an internal subset
 *
 * Returns 1 if true
 */
int hasInternalSubsetDebug(void *ctx)
{
    fprintf(stdout, "SAX.hasInternalSubset()\n");
    return(0);
}

/**
 * hasExternalSubsetDebug:
 * @ctxt:  An XML parser context
 *
 * Does this document has an external subset
 *
 * Returns 1 if true
 */
int hasExternalSubsetDebug(void *ctx)
{
    fprintf(stdout, "SAX.hasExternalSubset()\n");
    return(0);
}


/**
 * hasInternalSubsetDebug:
 * @ctxt:  An XML parser context
 *
 * Does this document has an internal subset
 */
void
internalSubsetDebug(void *ctx, const xmlChar *name,
           const xmlChar *ExternalID, const xmlChar *SystemID)
{
    fprintf(stdout, "SAX.internalSubset(%s,", name);
    if (ExternalID == NULL)
    fprintf(stdout, " ,");
    else
    fprintf(stdout, " %s,", ExternalID);
    if (SystemID == NULL)
    fprintf(stdout, " )\n");
    else
    fprintf(stdout, " %s)\n", SystemID);
}


/**
 * resolveEntityDebug:
 * @ctxt:  An XML parser context
 * @publicId: The public ID of the entity
 * @systemId: The system ID of the entity
 *
 * Special entity resolver, better left to the parser, it has
 * more context than the application layer.
 * The default behaviour is to NOT resolve the entities, in that case
 * the ENTITY_REF nodes are built in the structure (and the parameter
 * values).
 *
 * Returns the xmlParserInputPtr if inlined or NULL for DOM behaviour.
 */
xmlParserInputPtr
resolveEntityDebug(void *ctx, const xmlChar *publicId, const xmlChar *systemId)
{
    /* xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx; */


    fprintf(stdout, "SAX.resolveEntity(");
    if (publicId != NULL)
    fprintf(stdout, "%s", (char *)publicId);
    else
    fprintf(stdout, " ");
    if (systemId != NULL)
    fprintf(stdout, ", %s)\n", (char *)systemId);
    else
    fprintf(stdout, ", )\n");

    return(NULL);
}


/**
 * getEntityDebug:
 * @ctxt:  An XML parser context
 * @name: The entity name
 *
 * Get an entity by name
 *
 * Returns the xmlParserInputPtr if inlined or NULL for DOM behaviour.
 */
xmlEntityPtr
getEntityDebug(void *ctx, const xmlChar *name)
{
    fprintf(stdout, "SAX.getEntity(%s)\n", name);
    return(NULL);
}


/**
 * getParameterEntityDebug:
 * @ctxt:  An XML parser context
 * @name: The entity name
 *
 * Get a parameter entity by name
 *
 * Returns the xmlParserInputPtr
 */
xmlEntityPtr
getParameterEntityDebug(void *ctx, const xmlChar *name)
{
    fprintf(stdout, "SAX.getParameterEntity(%s)\n", name);
    return(NULL);
}


/**
 * entityDeclDebug:
 * @ctxt:  An XML parser context
 * @name:  the entity name
 * @type:  the entity type
 * @publicId: The public ID of the entity
 * @systemId: The system ID of the entity
 * @content: the entity value (without processing).
 *
 * An entity definition has been parsed
 */
void
entityDeclDebug(void *ctx, const xmlChar *name, int type,
          const xmlChar *publicId, const xmlChar *systemId, xmlChar *content)
{
    fprintf(stdout, "SAX.entityDecl(%s, %d, %s, %s, %s)\n",
            name, type, publicId, systemId, content);
}

/**
 * attributeDeclDebug:
 * @ctxt:  An XML parser context
 * @name:  the attribute name
 * @type:  the attribute type
 *
 * An attribute definition has been parsed
 */
void
attributeDeclDebug(void *ctx, const xmlChar *elem, const xmlChar *name,
              int type, int def, const xmlChar *defaultValue,
          xmlEnumerationPtr tree)
{
    fprintf(stdout, "SAX.attributeDecl(%s, %s, %d, %d, %s, ...)\n",
            elem, name, type, def, defaultValue);
}


/**
 * elementDeclDebug:
 * @ctxt:  An XML parser context
 * @name:  the element name
 * @type:  the element type
 * @content: the element value (without processing).
 *
 * An element definition has been parsed
 */
void
elementDeclDebug(void *ctx, const xmlChar *name, int type,
        xmlElementContentPtr content)
{
    fprintf(stdout, "SAX.elementDecl(%s, %d, ...)\n",
            name, type);
}


/**
 * notationDeclDebug:
 * @ctxt:  An XML parser context
 * @name: The name of the notation
 * @publicId: The public ID of the entity
 * @systemId: The system ID of the entity
 *
 * What to do when a notation declaration has been parsed.
 */
void
notationDeclDebug(void *ctx, const xmlChar *name,
         const xmlChar *publicId, const xmlChar *systemId)
{
    fprintf(stdout, "SAX.notationDecl(%s, %s, %s)\n",
            (char *) name, (char *) publicId, (char *) systemId);
}


/**
 * unparsedEntityDeclDebug:
 * @ctxt:  An XML parser context
 * @name: The name of the entity
 * @publicId: The public ID of the entity
 * @systemId: The system ID of the entity
 * @notationName: the name of the notation
 *
 * What to do when an unparsed entity declaration is parsed
 */
void
unparsedEntityDeclDebug(void *ctx, const xmlChar *name,
           const xmlChar *publicId, const xmlChar *systemId,
           const xmlChar *notationName)
{
    fprintf(stdout, "SAX.unparsedEntityDecl(%s, %s, %s, %s)\n",
            (char *) name, (char *) publicId, (char *) systemId,
        (char *) notationName);
}


/**
 * setDocumentLocatorDebug:
 * @ctxt:  An XML parser context
 * @loc: A SAX Locator
 *
 * Receive the document locator at startup, actually xmlDefaultSAXLocator
 * Everything is available on the context, so this is useless in our case.
 */
void
setDocumentLocatorDebug(void *ctx, xmlSAXLocatorPtr loc)
{
    fprintf(stdout, "SAX.setDocumentLocator()\n");
}


/**
 * startDocumentDebug:
 * @ctxt:  An XML parser context
 *
 * called when the document start being processed.
 */
void
startDocumentDebug(void *ctx)
{
    fprintf(stdout, "SAX.startDocument()\n");
}


/**
 * endDocumentDebug:
 * @ctxt:  An XML parser context
 *
 * called when the document end has been detected.
 */
void
endDocumentDebug(void *ctx)
{
    fprintf(stdout, "SAX.endDocument()\n");
}


/**
 * startElementDebug:
 * @ctxt:  An XML parser context
 * @name:  The element name
 *
 * called when an opening tag has been processed.
 */
void
startElementDebug(void *ctx, const xmlChar *name, const xmlChar **atts)
{
    int i;

    fprintf(stdout, "SAX.startElement(%s", (char *) name);
    if (atts != NULL) {
        for (i = 0;(atts[i] != NULL);i++) {
            fprintf(stdout, ", %s", atts[i++]);
            if (atts[i] != NULL) {
                unsigned char output[40];
                const unsigned char *att = atts[i];
                int outlen, attlen;
                fprintf(stdout, "='");
                while ((attlen = strlen((char*)att)) > 0) {
                    outlen = sizeof output - 1;
                    htmlEncodeEntities(output, &outlen, att, &attlen, '\'');
                    fprintf(stdout, "%.*s", outlen, output);
                    att += attlen;
                }
                fprintf(stdout, "'");
            }
        }
    }
    fprintf(stdout, ")\n");
}


/**
 * endElementDebug:
 * @ctxt:  An XML parser context
 * @name:  The element name
 *
 * called when the end of an element has been detected.
 */
void
endElementDebug(void *ctx, const xmlChar *name)
{
    fprintf(stdout, "SAX.endElement(%s)\n", (char *) name);
}


/**
 * charactersDebug:
 * @ctxt:  An XML parser context
 * @ch:  a xmlChar string
 * @len: the number of xmlChar
 *
 * receiving some chars from the parser.
 * Question: how much at a time ???
 */
void
charactersDebug(void *ctx, const xmlChar *ch, int len)
{
    unsigned char output[40];
    int inlen = len, outlen = 30;

    htmlEncodeEntities(output, &outlen, ch, &inlen, 0);
    output[outlen] = 0;

    fprintf(stdout, "SAX.characters(%s, %d)\n", output, len);
}


/**
 * cdataDebug:
 * @ctxt:  An XML parser context
 * @ch:  a xmlChar string
 * @len: the number of xmlChar
 *
 * receiving some cdata chars from the parser.
 * Question: how much at a time ???
 */
void
cdataDebug(void *ctx, const xmlChar *ch, int len)
{
    unsigned char output[40];
    int inlen = len, outlen = 30;

    htmlEncodeEntities(output, &outlen, ch, &inlen, 0);
    output[outlen] = 0;

    fprintf(stdout, "SAX.cdata(%s, %d)\n", output, len);
}


/**
 * referenceDebug:
 * @ctxt:  An XML parser context
 * @name:  The entity name
 *
 * called when an entity reference is detected.
 */
void
referenceDebug(void *ctx, const xmlChar *name)
{
    fprintf(stdout, "SAX.reference(%s)\n", name);
}


/**
 * ignorableWhitespaceDebug:
 * @ctxt:  An XML parser context
 * @ch:  a xmlChar string
 * @start: the first char in the string
 * @len: the number of xmlChar
 *
 * receiving some ignorable whitespaces from the parser.
 * Question: how much at a time ???
 */
void
ignorableWhitespaceDebug(void *ctx, const xmlChar *ch, int len)
{
    char output[40];
    int i;

    for (i = 0;(i<len) && (i < 30);i++)
    output[i] = ch[i];
    output[i] = 0;

    fprintf(stdout, "SAX.ignorableWhitespace(%s, %d)\n", output, len);
}


/**
 * processingInstructionDebug:
 * @ctxt:  An XML parser context
 * @target:  the target name
 * @data: the PI data's
 * @len: the number of xmlChar
 *
 * A processing instruction has been parsed.
 */
void
processingInstructionDebug(void *ctx, const xmlChar *target,
                      const xmlChar *data)
{
    fprintf(stdout, "SAX.processingInstruction(%s, %s)\n",
            (char *) target, (char *) data);
}


/**
 * commentDebug:
 * @ctxt:  An XML parser context
 * @value:  the comment content
 *
 * A comment has been parsed.
 */
void
commentDebug(void *ctx, const xmlChar *value)
{
    fprintf(stdout, "SAX.comment(%s)\n", value);
}


/**
 * warningDebug:
 * @ctxt:  An XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format a warning messages, gives file, line, position and
 * extra parameters.
 */
void
warningDebug(void *ctx, const char *msg, ...)
{
    va_list args;

    va_start(args, msg);
    fprintf(stdout, "SAX.warning: ");
    vfprintf(stdout, msg, args);
    va_end(args);
}


/**
 * errorDebug:
 * @ctxt:  An XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format a error messages, gives file, line, position and
 * extra parameters.
 */
void
errorDebug(void *ctx, const char *msg, ...)
{
    va_list args;

    va_start(args, msg);
    fprintf(stdout, "SAX.error: ");
    vfprintf(stdout, msg, args);
    va_end(args);
}


/**
 * fatalErrorDebug:
 * @ctxt:  An XML parser context
 * @msg:  the message to display/transmit
 * @...:  extra parameters for the message display
 *
 * Display and format a fatalError messages, gives file, line, position and
 * extra parameters.
 */
void
fatalErrorDebug(void *ctx, const char *msg, ...)
{
    va_list args;

    va_start(args, msg);
    fprintf(stdout, "SAX.fatalError: ");
    vfprintf(stdout, msg, args);
    va_end(args);
}

// SAX Handler:  callback function definition
static xmlSAXHandler saxHandler = {
    internalSubsetDebug,
    isStandaloneDebug,
    hasInternalSubsetDebug,
    hasExternalSubsetDebug,
    resolveEntityDebug,
    getEntityDebug,
    entityDeclDebug,
    notationDeclDebug,
    attributeDeclDebug,
    elementDeclDebug,
    unparsedEntityDeclDebug,
    setDocumentLocatorDebug,
    startDocumentDebug,
    endDocumentDebug,
    startElementDebug,
    endElementDebug,
    referenceDebug,
    charactersDebug,
    ignorableWhitespaceDebug,
    processingInstructionDebug,
    commentDebug,
    warningDebug,
    errorDebug,
    fatalErrorDebug,
    getParameterEntityDebug,
    cdataDebug,
    NULL,
    1,
    NULL,
    NULL,
    NULL,
    NULL
};


/**
 * main
 */
int main(int argc, char *argv[])
{
    CURL *conn = NULL;
    CURLcode code;

    char* url = (char *)"https://example.com/";

    if (argc == 2) {
        url = argv[1];
   } else  {
        printf("Usage: %s <url>\n", argv[0]);
    }

    printf("url: %s \n", url);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (!curl_init(conn, url)) {
        fprintf(stderr, "Connection initializion failed: %s \n", url);
        return EXIT_FAILURE;
    }

    // Push MODE Parse definition
    ctxt = htmlCreatePushParserCtxt(&saxHandler, NULL, "", 0, "",
                                    XML_CHAR_ENCODING_NONE);

    // curl
    code = curl_easy_perform(conn);
    curl_easy_cleanup(conn);
    if (code != CURLE_OK) {
        fprintf(stderr, "Failed to get '%s' [%s]\n", url, errorBuffer);
        return EXIT_FAILURE;
    }

    // End of Chunk
    htmlParseChunk(ctxt, "", 0, 1);
    htmlFreeParserCtxt(ctxt);

    // Full HTML for parsing
    printf("\n === HTML === \n");
    printf("%s \n", buffer.c_str());

    return EXIT_SUCCESS;
}


