enum opcodes{
      PUSH = 0x00,
      ADD = 0x01,
      SUB = 0x02,
      MUL = 0x03,
      DIV = 0x04,
      CMP = 0x05,
      LD = 0x06,
      STO = 0x07,
      IO = 0x08,
      DUP = 0x09,
      SWP = 0x0A,
      DRP = 0x0B,
      JMP = 0x0C,
      CALL = 0x0D,
      RET = 0x0E,
      EXIT = 0x0F,
};
struct instruction{
  struct token start;
  enum opcodes opcode;
  int args[3];
};

