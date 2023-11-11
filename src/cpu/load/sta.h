// all of the STA opcodes and its variations
#define STA_CASES() \
    case 0x8D: \
        opcode.mode = Absolute; \
        opcode.opcode = STA; \
        break; \
    case 0x9D: \
        opcode.mode = XIndexedAbsolute; \
        opcode.opcode = STA; \
        break; \
    case 0x99: \
        opcode.mode = YIndexedAbsolute; \
        opcode.opcode = STA; \
        break; \
    case 0x85: \
        opcode.mode = ZeroPage; \
        opcode.opcode = STA; \
        break; \
    case 0x95: \
        opcode.mode = XIndexedZeroPage; \
        opcode.opcode = STA; \
        break; \
    case 0x81: \
        opcode.mode = XIndexZeroPageIndirect; \
        opcode.opcode = STA; \
        break; \
    case 0x91: \
        opcode.mode = YIndexZeroPageIndirect;\
        opcode.opcode = STA;\
        break;

