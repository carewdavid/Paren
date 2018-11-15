#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "instruction.h"
#include "util/vector.h"

static struct Vector *program_tokens;

static bool at_end(){
  return program_tokens->len == 0;
}
  


static struct token *peek(){
  if(!at_end()){
    return vec_get(program_tokens, 0);
  }else{
    return NULL;
  }
}


static struct token *next_token(){
  if(!at_end()){
    struct token *token = vec_remove(program_tokens, 0);
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
  int i = 0;
  while(peek()->type != RPAREN){
    instruction->args[i] = nesting();
    i++;
  }
  //Fill unused slots in the arguments array with -1 to mark that they are empty, since there is no way to directly express negative numbers
  for(; i < 3; i++){
    instruction->args[i] = -1;
  }
  next_token();
  return instruction;
}


struct Vector *parse(struct token *tokens){
  program_tokens = tokens;
  struct Vector *program = vec_create(10, sizeof(instruction));
  while(

  
 }
