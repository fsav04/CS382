#include <stdio.h>
#include <string.h>

//int main()
// {
// 	char str[] = "strtok needs to be called several times to split a string";
// 	int init_size = strlen(str);
// 	char delim[] = " ";

// 	char *ptr = strtok(str, delim);

// 	while(ptr != NULL)
// 	{
// 		printf("'%s'\n", ptr);
// 		ptr = strtok(NULL, delim);
// 	}

// 	/* This loop will show that there are zeroes in the str after tokenizing */
// 	for (int i = 0; i < init_size; i++)
// 	{
// 		printf("%d ", str[i]); /* Convert the character to integer, in this case
// 							   the character's ASCII equivalent */
// 	}
// 	printf("\n");

// 	return 0;
int checkChar(char* str){
	int hasspace = 1;
	int count;
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == ' '){
			count++;
			if(count == 2){
				hasspace = 0;
				return hasspace;
			}
		}
}
	return hasspace;
}

int main()
{
char* str1 = " this has a space";
char* str2 = "1 space";
char* str3 = "none";
printf("%d\n",checkChar(str1));
printf("%d\n",checkChar(str2));
printf("%d\n",checkChar(str3));
	return 0;
}