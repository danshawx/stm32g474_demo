#ifndef COMM_PROTOCOL_H
#define COMM_PROTOCOL_H

#include "my_lib.h"

#define COMM_USART_PROCOL_HEAD_START    (0xFF)
#define COMM_USART_PROCOL_FRAME_START   (0xFE)
// head_start head_traid  head_traid head_crc;
// frame_head frame_len(frame_func+frame_dates+frame_crc) frame_func frame_dates frame_crc

enum
{
	COMM_USART_HEAD_START,
	COMM_USART_HEAD_DATA,
	COMM_USART_FRAME_START,
	COMM_USART_FRAME_DATA,
}COMM_USART_UNPACK_STATE;

#pragma pack(push)
#pragma pack(1)

typedef struct
{
    uint8_t head_start;
	uint8_t head_traid;
	uint8_t head_recid;
	uint8_t head_protoltype;
	uint8_t frame_cnt;
	uint8_t head_crc;
}T_Comm_Mess_Head;

typedef struct
{
	uint8_t frame_start;
	uint8_t frame_len;
	uint8_t frame_func;
	uint8_t frame_dates[2];
	uint16_t fram_crc;
}T_Comm_Test_Frame;

typedef struct
{
	T_Comm_Mess_Head g_tHeadTestSend;
	T_Comm_Test_Frame g_tFrameTestSend;
}T_Comm_Test_Send;

#pragma pack(pop)


#define CONFIG_COMMUSART_HEAD_LEN       (sizeof(T_Comm_Mess_Head))
#define CONFIG_COMMUSART_DATA_LEN       (sizeof(T_Comm_Test_Frame))

uint32_t Comm_Unpack_Fun(void);

#endif
