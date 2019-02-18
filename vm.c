#Include <stdlib.h>
#include <stdio.h>
#include "instruction.h"

#define DEFAULT_STACK_SIZE 1000
#define DEFAULT_MEMORY_SIZE 1000

typedef struct {
  size_t top;
  int *data;
} Stack;

static Stack stack;

static int memory[DEFAULT_MEMORY_SIZE];

static void push(int data){
  stack.data[stack.top] = data;
  stack.top++;
}

static int pop(){
  int ret = stack.data[stack.top];
  stack.top--;
  return ret;
}

static void init_stack(){
  stack.top = 0;
  stack.data = malloc(sizeof(int) * DEFAULT_STACK_SIZE);
}

  
int run(int *program){
  size_t pc = 0;
  init_stack();

#define BINOP(op) do { \
    int left = pop(); \
    int right = pop(); \
    push(left op right); \
  } while(0);

  while(program[pc] != -1){
    struct instruction inst = program[pc];
    switch(inst.opcode){
    case PUSH: {
      push(inst.args[0]);
      break;
    }
    case OP_ADD: {
      BINOP(+);
      break;
    }
    case OP_SUB: {
      BINOP(-);
      break;
    }
    case OP_MUL: {
      BINOP(*);
      break;
    }
    case OP_DIV: {
      BINOP(/);
      break;
    }
    case OP_CMP: {
      int op = pop();
      switch(op){
      case 0:
	BINOP(==);
	break;
      case 1:
	BINOP(!=);
	break;
      case 2:
	BINOP(<);
	break;
      case 3:
	BINOP(<=);
	break;
      case 4:
	BINOP(>);
	break;
      case 5:
	BINOP(>=);
	break;
      default:
	error("Invalid comparison");
      }
    }
	  
    case OP_LOAD: {
      int addr = pop();
      push(memory[addr]);
      break;
    }
    case OP_STORE: {
      int addr = pop();
      int val = pop();
      memory[addr] = val;
      break;
    }
    case OP_READ: {
      if(inst.args[0] == 1){
	int chr = getchar();
      }
      break;
    }
    case OP_WRITE:{}

    case OP_DUP: {
      int temp = pop();
      push(temp);
      push(temp);
      break;
    }
    case OP_SWAP: {
      int temp = pop();
      int temp2 = pop();
      push(temp);
      push(temp2);
      break;
    }
    case OP_DROP: {
      pop();
      break;
    }
    case OP_GOTO: {
      int cond = pop();
      if(cond){
	switch(args[1]){
	case 0:
	  pc = args[0];
	  break;
	case 1: 
	  pc += args[0];
	  break;
	case 2:
	  pc -= args[0];
	  break;
	default:
	  //error
	}
      }
      break;
    }
    case _OPC_CALL: {
      push(pc);
      pc = inst.args[0];
      pc--;
      break;
    }
    case RET: {
      pc = pop();
      pc--;
      break;
    }
    case OP_EXIT: {
      goto exit;
    }
    default: {
      fprintf(stderr, "Unknown opcode %x.\n", inst.opcode);
      return 1;
    }
      pc++;
    }
  }
 exit:
  return 0;
}
