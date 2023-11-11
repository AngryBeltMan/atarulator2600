#define STX_CASES() \
    case 0x8E: \
        opcode.mode = Absolute; \
        opcode.opcode = STX;\
        break;\
    case 0x86:\
        opcode.mode = ZeroPage; \
        opcode.opcode = STX;\
        break; \
    case 0x96: \
        opcode.mode = YIndexedZeroPage; \
        opcode.opcode = STX; \
        break;
