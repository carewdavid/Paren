#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "util/vector.h"

struct Vector *lex(char *program){
  size_t program_length = strlen(program) + 1;
  struct Vector *tokens = vec_create(sizeof(struct token), program_length);
  int line = 0;
  int col = 0;
  for(size_t i = 0; i < program_length; i++){
    char c = program[i];
    struct token tok;
    if(c == '('){
      tok.line = line;
      tok.column = col;
      tok.type = LPAREN;
      col++;
      vec_push(tokens, &tok);
    }else if(c == ')'){
      tok.line = line;
      tok.column = col;
      tok.type = RPAREN;
      col++;
      vec_push(tokens, &tok);
    }else if(c == '\n'){
      line++;
      col = 0;
    }else{
      col++;
    }
  }
  return tokens;
      
} 
