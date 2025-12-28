#define STATUS_REG_MASK 0b11111000

/******************Receiver Mode Status Codes**********************/
#define R_SLA_ACK 0x60U
#define R_ARB_LOST_SLA_ACK 0x68U
#define R_GCALL_ACK 0x70U
#define R_ARB_LOST_GCALL_ACK 0x78U
#define R_DATA_ACK 0x80U
#define R_DATA_NACK 0x88U
#define R_GCALL_DATA_ACK 0x90U
#define R_GCALL_DATA_NACK 0x98U
#define R_STOP 0xA0U


/******************Transmitter Mode Status Codes**********************/
#define T_SLA_ACK 0xA8U
#define T_ARB_LOST_SLA_ACK 0xB0U
#define T_DATA_ACK 0xB8U
#define T_DATA_NACK 0xC0U
#define T_DONE_ACK 0xC8U