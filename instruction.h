enum opcodes{
      exit = 0x00,
      push = 0x01,
      add = 0x02,
      sub = 0x03,
      mul = 0x04,
      div = 0x05,
      cmp = 0x06,
      ld = 0x07,
      sto = 0x08,
      io = 0x09,
      dup = 0x0A,
      swp = 0x0B,
      drp = 0x0C,
      jmp = 0x0D,
      call = 0x0E,
      ret = 0x0F
};
struct instruction_{
  struct token start;

  int args[3];
};

typedef struct instruction_ *instruction;
