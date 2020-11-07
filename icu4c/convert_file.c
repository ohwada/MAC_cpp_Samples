/**
 * icu4c sample
 * 2020-07-01 K.OHWADA
 */


// read file convert charset write file
//reference : https://www.nslabs.jp/icu-conversion.rhtml



#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <unicode/ucnv.h> 


/**
 * read_convert_write
 */
void read_convert_write(FILE* input, FILE* output, char *input_charset, char *output_charset) 
{ 
  assert(input); 
  assert(output); 
   
  char source_buf[10];  // longer than the longest multibyte character 

  const int ELEM_SIZE = 30; // must be large enough for source_buf
  UChar pivot[ELEM_SIZE];  // intermediate charset (UTF-16)

  char target_buf[100]; 

  UErrorCode err = U_ZERO_ERROR; 
 
  UConverter* sourceCnv = ucnv_open( (char *)input_charset, &err); 
  assert(sourceCnv); 

  UConverter* targetCnv = ucnv_open( (char *)output_charset, &err); 
  assert(targetCnv); 
 
  int remaining = 0; 
   
  while (true) { 

    // read input file
    // Not necessarily at the beginning of the buffer.
    int len_read = fread(source_buf + remaining, 1, sizeof(source_buf) - remaining, 
                  input); 

    bool flush = feof(input) || ferror(input); 
    if ( flush && (remaining + len_read == 0) ) {
        // no unconverted.
         break;
    }


// convert to intermediate charset (UTF-16)
    UChar* pivot_p = pivot; 
    const char* source_p = source_buf; 
    ucnv_toUnicode(sourceCnv, &pivot_p, pivot + ELEM_SIZE, 
                   &source_p,  // source 
                   source_buf + remaining + len_read, // sourceLimit 
                   NULL, flush, &err); 
    assert(U_SUCCESS(err)); 
 
    // print_uchars(pivot, pivot_p); 
     

// convert to target charset (UTF-8)
    char* target_p = target_buf; 
    const UChar* pivot_out = pivot; 
    ucnv_fromUnicode(targetCnv, &target_p, target_buf + sizeof(target_buf), 
                     &pivot_out, pivot_p, NULL, flush, &err); 
    assert(U_SUCCESS(err)); 
    assert(pivot_out == pivot_p); 
     
    size_t write_size = target_p - target_buf;

    // output display
    printf("%zu : ", write_size);
    fwrite(target_buf, 1, write_size, stdout); 
    printf("\n");

    // write output file
    fwrite(target_buf, 1, write_size, output); 
     
    if (flush) {
      break; 
    }

    // fill the source buffer
    memmove(source_buf, source_p, (remaining + len_read) - (source_p - source_buf)); 
    remaining = (remaining + len_read) - (source_p - source_buf); 

  } // while
 
  ucnv_close(sourceCnv); 
  ucnv_close(targetCnv); 
}



/**
 * main
 */
int main(int argc, char* argv[])
{

    char *file_input = "data/sjis.txt";
    char *file_output ="utf8.txt";

    char *charset_input = "MS932"; // sjis
    char *charset_output = "UTF-8";

    if(argc == 3) {
            file_input = argv[1];
            charset_input = argv[2];
    } else {
            printf( "Usage:  %s [file] [charset] \n",  argv[0] );
    }

  FILE* input = fopen(file_input, "r"); 

  if (!input) { 
        fprintf(stderr, "fopen failed: %s\n", file_input); 
        return EXIT_FAILURE;
  } 

  FILE* output = fopen(file_output, "w"); 

  if (!output) { 
        fprintf(stderr, "fopen failed: %s \n", file_output); 
        return EXIT_FAILURE;
  } 
 
    read_convert_write(input, output, charset_input, charset_output); 
 
    printf("saved to: %s \n", file_output);

    fclose(input); 
    fclose(output); 
   
    return EXIT_SUCCESS;
}

