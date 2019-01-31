#Include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "instruction.h"

#define DEFAULT_STACK_SIZE 1000
#define DEFAULT_MEMORY_SIZE 1000

static struct Stack {
  size_t top;
  int *data;
} stack;

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

int math(enum opcodes op, int args[3]){
  int left;
  int right;
  if(args[0] == 0){
    right = pop();
    left = pop();
  }else if(args[1] == 0){
    left = pop();
    right = args[0];
  }else{
    left = args[0];
    right = args[1];
  }

  if(op == ADD){
    return left + right;
  }else if(op == SUB){
    return left - right;
  }else if(op == MUL){
    return left * right;
  }else{
    return left / right;
  }
}

int compare(int args[3]){
  int left;
  int right;

  if(args[1] == 0){
    right = pop();
    left = pop();
  }else if(args[2] == 0){
    left = pop();
    right = args[1];
  }else{
    left = args[1];
    right = args[2];
  }

  switch(args[0]){
  case 1:
    return left == right;
  case 2:
    return left != right;
  case 3:
    return left < right;
  case 4:
    return left <= right;
  case 5:
    return left > right;
  case 6:
    return left >= right;
  default:
    fprintf(stderr, "Unknown comparison code %d.\n", args[0]);
    exit(1);
  }
}

int run(struct instruction *program){
  size_t pc = 0;
  init_stack();

  while(1){
    struct instruction inst = program[pc];
    switch(inst.opcode){
    case PUSH: {
      push(inst.args[0]);
      break;
    }
    case ADD: 
    case SUB:
    case MUL:
    case DIV: {
      push(math(inst.opcode, inst.args));
      break;
    }
    case CMP:
      push(compare(inst.args));
	   break;
    case LD: {
      int addr = 0;
      if(inst.args[0] == 0){
	addr = pop();
      }else{
	addr = inst.args[0];
      }
      push(memory[addr]);
      break;
    }
    case STO: {
      int addr = 0;
      int val = 0;
      if(inst.args[0] == 0){
	addr = pop();
      }else{
	addr = inst.args[0];
      }
      if(inst.args[1] == 0){
	val = pop();
      }else{
	val = inst.args[1];
      }
      memory[addr] = val;
      break;
    }
    case IO: {
      if(inst.args[0] == 1){
	int chr = getchar();
	
      
    case DUP: {
      int temp = pop();
      push(temp);
      push(temp);
      break;
    }
    case SWP: {
      int temp = pop();
      int temp2 = pop();
      push(temp);
      push(temp2);
      break;
    }
    case DRP: {
      pop();
      break;
    }
    case JMP: {
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
    case CALL: {
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
    case EXIT: {
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
