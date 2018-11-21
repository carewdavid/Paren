#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "instruction.h"

static struct token *tokens;
static struct token nil = {0};

static int at_end(){
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
  
void instr(struct instruction *instruction){
  instruction->start = *peek();
  instruction->opcode = nesting();
  int i = 0;
  while(peek()->type != RPAREN){
    instruction->args[i] = nesting();
    i++;
  }
  next_token();
}

static size_t prog_len(struct token *program){
  size_t len = 0;
  while(memcmp(&nil, program, sizeof(struct token))){
    len++;
    program++;
  }
  return len;
}

struct instruction *parse(struct token *program){
  size_t program_length = prog_len(program) / 2;
  struct instruction *instrs = malloc(sizeof(struct instruction) * program_length);
  memset(instrs, 0, program_length);
  size_t i = 0;
  while(!at_end()){
    instr(instrs + i);
  }
  return instrs;
}

