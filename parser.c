#include <stdlib.h>
#include "token.h"
#include "instruction.h"

static struct token *tokens;

static struct token *peek(){
  if(tokens){
    return tokens;
  }else{
    return NULL;
}


static struct token *next_token(){
  if(tokens){
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
  
instruction instruction(){
  instruction instruction = malloc(sizeof(*instruction));
  instruction->start = *peek();
  instruction->opcode = nesting();
  while(peek()->type != RPAREN){
    //get arg
  }
  next_token();
  return instruction;
}


  
