/**
 * decimal_to_binary.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://webkaru.net/clang/decimal-to-binary/

// prototype
void decimal_to_binary(int *binary, int size, int decimal,  int digits);
void binary_to_string(char *buf, int size, int *binary, int digits);
void print_binary(int *binary, int digits);
void clear_binary(int *binary, int size);
void clear_binary_string(char *buf, int size);

const char NUL = '\0';
const char ZERO = '0';
const char ONE = '1';

/**
 * decimal_to_binary
 */
void decimal_to_binary(int *binary, int size, int decimal, int  digits)
{
     clear_binary(binary, digits);

    for(int i=0; decimal>0; i++)
    {
        if(i<size) {
            binary[i] =  decimal % 2;
        }
         decimal =  decimal / 2;
    } // for
}


/**
 * binary_to_string
 */
void binary_to_string(char *buf, int size, int *binary, int digits)
{

clear_binary_string(buf, size);

for(int i=0; i<=digits; i++)
{
    int j = digits-i;
    if(j>=0){
        int bin = binary[j];
        char ch = (bin==1)? ONE : ZERO;
        if(i<size){     
         buf[i] = ch;
        }
    }
} // for

}


/**
 * print_binary
 */
void print_binary(int *binary, int digits)
{
for(int i=0; i<=digits; i++)
{
    int j = digits-i;
    if(j>=0){
        printf("%d", binary[j]);
    }
} // for
    printf(" ");
}


/**
 * clear_binary
 */
void clear_binary(int *binary, int  digits)
{
    for(int i=0; i<= digits; i++)
    {
        binary[i] = 0;
    } // for
}


/**
 * clear_binary_string
 */
void clear_binary_string(char *buf, int size)
{
    for(int i=0; i<size; i++)
    {
        buf[i] = NUL;
    } // for
}
