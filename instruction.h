struct {
  struct token start;
  int opcode;
  int args[3];
} instruction_;

typedef struct instruction_ *instruction
