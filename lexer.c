#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

struct token *lex(char *program){
  size_t program_length = strlen(program) + 1;
  struct token *tokens = malloc(sizeof(struct token) * program_length);
  memset(tokens, 0, program_length);
  int line = 0;
  int col = 0;
  for(size_t i = 0; i < program_length; i++){
    char c = program[i];
    if(c == '('){
      tokens[i].line = line;
      tokens[i].column = col;
      tokens[i].type = LPAREN;
      col++;
    }else if(c == ')'){
      tokens[i].line = line;
      tokens[i].column = col;
      tokens[i].type = RPAREN;
      col++;
    }else if(c == '\n'){
      line++;
      col = 0;
    }else{
      col++;
    }
  }
  return tokens;
      
} 
