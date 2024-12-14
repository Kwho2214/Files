#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int line_count = 0;
   int num = 0;
   FILE *in, *out;
   char line[MAX_LEN];

    // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
      if( in == NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }

    out = fopen(argv[2], "w");
    if( out == NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    //i googled this
    //from stack overflow
    //count number of lines in input file
    while(!feof(in)){
      char ch = fgetc(in);
      if (ch == '\n') {
        line_count += 1;
      }
    }

    char **arr = calloc(line_count, sizeof(char *));
    List L = newList();
    
    //copying strings into the array
    while (fgets(line, MAX_LEN, in) != NULL) {
      char *temp_arr = calloc(line_count, sizeof(char*) + 1);
      strcpy(temp_arr, line);
      int len = strlen(temp_arr);
      //To remove trailing newlines, if any
      if (temp_arr[len - 1] == '\n') {
        temp_arr[len - 1] = 0;
      }
      arr[num] = temp_arr;
      num += 1;
    }

    for (int i = 0; i < line_count; i++){
      char *temp = arr[i];
      moveFront(L);
      bool inserted = false;
      while(index(L) > 0 && inserted == false) {
        int curr_postition = get(L);
        char *curr = arr[curr_postition];
        if (temp <= curr) {
          arr[i - 1] = temp;
          inserted = true; 
        }
        moveNext(L);
      }
      if (inserted == false) {
        append(L, i);
      }
    }

    printList(out, L);
    freeList(&L);
    for (int i = 0; i < line_count; i++){
      free(arr[i]);
    }
    free(arr);
    fclose(in);
    fclose(out);
  return(0);
}