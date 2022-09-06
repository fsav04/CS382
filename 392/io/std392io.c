#include "std392io.h"
#define EOF -1

//Frank Savattere
//I pledge my honor that I have abided by the Stevens honor system

void __toString(int data, char* string){
int isneg = 0; //var to check for neg value first
int index = 0;
int sloppy = data;
int datacopy = data;
if (datacopy < 0){ //if negative number add a space for the negative sign
        isneg = 1;
    }
    do {
    datacopy /= 10;
    isneg++;
    } 
    while (datacopy != 0);
    
    if (data < 0){  
        data *= -1; //make n positive
    }          
     do {      
        string[index] = data % 10 + '0';  
        data /= 10;
        index++;
     } 
     while (data > 0); 

    if (sloppy < 0){
        string[index++] = '-';
     }
     string[index] = '\0';


    char ctr;
    for (int i = 0; i < strlen(string) - 1; i++){
        for(int j = i + 1; j < strlen(string); j++){

         ctr = string[i];
         string[i] = string[j];
         string[j] = ctr;
     }
 }
}

int output(char* filename, char format, void* data){
if (&data == NULL){
    errno = EIO;
    return -1;
}
if (format == 'd'){ //if the format is an int
    int dataInt = *(int *)data; //dereference
    int nbyte = 0; //
    if (dataInt > 0){ //allocate size for write
        do{
            dataInt /= 10;
            nbyte += 1;
        }
        while (dataInt != 0);
    }
    else{ //allocate extra byte for write if the data is negative to allow for the - sign 
        nbyte = 1;
        do{
            dataInt /= 10;
            nbyte += 1;
        }
        while (dataInt != 0);
    }
    dataInt = *(int *)data;
    
    char outString[nbyte];
    if (strcmp(filename, "") == 0){ //if the filename is blank
        __toString(dataInt,outString);
        write(1, outString, nbyte);
        write(1, "\n", 1);
    }
    else {
        if(access(filename, F_OK) != 0){ //file doesnt exist
            int file = open(filename, O_WRONLY | O_APPEND | O_CREAT);
            __toString(dataInt,outString);
            write(file, outString, nbyte);
            write(file, "\n", 1);
        }
        
        else{ //File does exist
        int file = open(filename, O_WRONLY | O_APPEND);
        __toString(dataInt,outString);
        write(file, outString, nbyte);
        write(file, "\n", 1);
        }
        }

    }

else if (format == 's'){
    char* dataString = (char *)data;
    size_t nbyte = sizeof(dataString);
    if (strcmp(filename, "") == 0){
        write(1, dataString, nbyte);
        write(1, "\n", 1);
    }
    else {
        if(access(filename, F_OK) != 0){ //if file does not exist
            int file = open(filename, O_WRONLY | O_APPEND | O_CREAT); //we need to create the file 
            write(file, dataString, nbyte);
            write(file, "\n", 1);
        }
        
        else{ 
            int file = open(filename, O_WRONLY | O_APPEND);
            write(file, dataString, nbyte);
            write(file, "\n", 1);
        }
    }
    }

    else {
    //puts("unrec format"); //test
    errno = EIO;
    return -1;
}
return 0;
}




int input(char* filename, char format, void* data){
    if(filename == ""){
        *(char *) filename = 1;
    }
int fd = open(filename, O_RDONLY);
char tmp;
if(format == 's'){
char* datacopy = (char *) data;
datacopy = malloc(128);
int index = 0;
int curr_size = 128;
  while(read(fd, &tmp, 1) != 0){
    if(index == curr_size){
      char* newarr = malloc(curr_size+128);
      for(size_t j = 0; j < curr_size; j++){
        newarr[j] = datacopy[j];
      }
      free(datacopy);
      datacopy = newarr;
      curr_size += 128;
    }
    datacopy[index] = tmp;
    index++;
  }
  if(access(filename, F_OK) == 0){
      if(open(filename, O_RDONLY) != -1){
      while(1){
          ssize_t check = read(fd, data, 1);
          if(check != sizeof(datacopy)){
            break; 
          }
      }
      }
}
}
else if(format == 'd'){
    int datacopy = *(int *) data;
}
  else{
      errno = ENOENT;
      return -1;
  }

    return 0;
}


int clean(){
    struct dirent* drp;
    DIR* dp = opendir("/proc");
    struct stat info;
    while((drp = readdir(dp)) != NULL){
    if(drp -> d_name != "." || drp -> d_name != ".."){
        close(atoi(drp -> d_name));
    }
    }
	return 0;
}

