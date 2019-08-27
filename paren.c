#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "vm.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Usage: $paren prog\n");
    return 1;
  }

  FILE *program = fopen(argv[1], "r");
  fseek(program,0, SEEK_END);
  long size = ftell(program);

  char *source = malloc(sizeof(char) * size);
  fseek(program, 0, SEEK_SET);

  for(long i; i < size; i++){
    source[i] = (char)fgetc(program);
  }

  int *code = parse(source);
  return run(code);
}
