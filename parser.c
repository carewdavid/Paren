#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "instruction.h"

static struct token *tokens;

static int at_end(){
  static struct token nil = {0};
  //Tokens should be null terminated.
  return memcmp(&nil, tokens, sizeof(struct token));
}

static struct token *peek(){
  if(!at_end()){
    return tokens;
  }else{
    return NULL;
  }
}


static struct token *next_token(){
  if(!at_end()){
    struct token *token = tokens;
    tokens++;
    return token;
  }else{
    return NULL;
  }
}

static int nesting(){
  int level = 0;
  int nesting = 1;
  struct token *current = next_token();
  while(nesting > 0){
    if(current->type == LPAREN){
    level++;
    nesting++;
    }
    if(current->type == RPAREN){
      nesting--;
    }
    current = next_token();
  }
  return level - 1;
}
  
instruction instr(){
  instruction instruction = malloc(sizeof(*instruction));
  instruction->start = *peek();
  instruction->opcode = nesting();
  while(peek()->type != RPAREN){
    //get arg
  }
  next_token();
  return instruction;
}


  
