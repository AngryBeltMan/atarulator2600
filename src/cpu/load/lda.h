// all of the LDA opcodes
#define LDA_CASES() \
    case 0xA9: \
        opcode.mode = Immediate; \
        opcode.opcode = LDA; \
        break; \
    case 0xAD: \
        opcode.mode = Absolute; \
        opcode.opcode = LDA; \
        break; \
    case 0xA5: \
        opcode.mode = ZeroPage; \
        opcode.opcode = LDA; \
        break; \
    case 0xBD: \
        opcode.mode = XIndexedAbsolute; \
        opcode.opcode = LDA; \
        break; \
    case 0xB9: \
        opcode.mode = YIndexedAbsolute; \
        opcode.opcode = LDA; \
        break; \
    case 0xB5: \
        opcode.mode = XIndexedZeroPage; \
        opcode.opcode = LDA; \
        break; \
    case 0xA1: \
        opcode.mode = XIndexZeroPageIndirect; \
        opcode.opcode = LDA; \
        break; \
    case 0xB1: \
        opcode.mode = YIndexZeroPageIndirect; \
        opcode.opcode = LDA; \
        break;
