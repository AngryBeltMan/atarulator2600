#define STY_CASES() \
    case 0x8C: \
        opcode.mode = Absolute; \
        opcode.opcode = STY; \
        break; \
    case 0x84: \
        opcode.mode = ZeroPage; \
        opcode.opcode = STY; \
        break; \
    case 0x94:\
        opcode.mode = XIndexedZeroPage;\
        opcode.opcode = STY;\
        break;
