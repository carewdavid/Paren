#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "parser.h"

void test_parser_empty(){
  assert(parse("") == NULL);
}

void test_parser_nest_single_zero(){
  int *prog  = parse("()");
  int expected[] = {0, -1};
  assert(memcmp(prog, expected, 2 * sizeof(int)) == 0);
}

void test_parser_nest_single_one(){
  int  *prog = parse("(())");
  int expected[] = {1, -1};
  assert(memcmp(prog, expected, 2 * sizeof(int)) == 0);
}
void test_parser_nest_multiple(){
  int *prog = parse("(())(((())))");
  int expected[] = {1, 3, -1};
  assert(memcmp(prog, expected, 3 * sizeof(int)) == 0);
}

void test_parser_unbalanced(){
  int *prog = parse("((())");
  int expected[] = {-1};
  assert(memcmp(prog, expected, 1 * sizeof(int)) == 0);
}

void test_parser(){
  test_parser_empty();
  test_parser_nest_single_zero();
  test_parser_nest_single_one();
  test_parser_nest_multiple();
  test_parser_unbalanced();
}

int main(){
  test_parser();
  return 0;
}
  
  
