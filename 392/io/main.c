#include "std392io.h"

int main(int argc, char* argv[]) {

int array[5] = {1,2,-9,12,-3};
char* string = "Hello!";

/* Print integers to stdout */
for (size_t i = 0; i < 5; i++) {
output("", 'd', &array[i]);
}
 /* Print string to stdout */
 output("", 's', string);

/* Error: unrecognized format */
output("", 'i', string);

/* Write integers to a text file */
 for (size_t i = 0; i < 5; i ++) {
 output("text", 'd', &array[i]);
 }

 /* Write string to a text file */
 output("text", 's', string);

 clean();

 char newstr[1024] = {0};
 int num;
 /* Receive a string from stdin */
 input("", 's', newstr);
 /* Print out the string to stdout */
 output("", 's', newstr);

 /* Receive an integer from stdin */
 input("", 'd', &num);
 /* Print out the integer to stdout */
 output("", 'd', &num);

 /* Read a file */

 while (!input("text", 's', newstr)) {
 output("", 's', "Line: ");
 output("", 's', newstr);
 }

 /* Close opened files */
 clean();

 return 0;
 }