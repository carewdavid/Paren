#include <stdlib.h>
#include <string.h>

#include "error.h"

char *source_code;

static char peek(){
  return *source_code;
}
static char advance(){
  char next = *source_code;
  source_code++;
  return next;
}

static char atEnd(){
  return *source_code == '\0';
}

static void skip(void){
  while(!atEnd() && peek() != '('){
    advance();
  }
}

static int instruction(){
  skip();
  advance();
  int depth = 0;
  int max = 0;

  if(atEnd()){
    return -1;
  }

  while(peek() != ')' || depth != 0){
    char c = advance();
    if(c == '('){
      depth++;
      max = depth > max ? depth : max;
    }else if(c == ')'){
      depth--;
    }else if(atEnd()){ //i.e. c == '\0'
      error("Reached end of file without matching ')'.");
      return -1;
    }
  }
  return max;
}
  
int *parse(char *source){
  source_code = source;
  size_t len = strlen(source);
  if(len == 0){
    return NULL;
  }
  size_t code_len = len / 2 + 1;
  int *code = malloc(code_len * sizeof(int));
  for(size_t i = 0; i < code_len; i++){
    int instr = instruction();
    code[i] = instr;
    if(instr < 0) break;
  }
  return code;
}

  

