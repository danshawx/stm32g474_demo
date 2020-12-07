#include "comm_task.h"
#include "main.h"

T_Comm_Test_Send g_tComm_Test_Send = {0};

static void Comm_Recv_Process(void)
{
	if (SUCCESS == Comm_Unpack_Fun())
	{

	}
}

static void Comm_Tra_Procecss(void)
{
	//uint8_t i = 0;
	//uint16_t tx_crc16 = 0;
	T_Comm_Test_Send *p_tComm_Test_Send = (T_Comm_Test_Send *)g_aUsartTxBuf;

	p_tComm_Test_Send->g_tHeadTestSend.head_start = 0xFF;
	p_tComm_Test_Send->g_tHeadTestSend.head_traid = 0x01;
	p_tComm_Test_Send->g_tHeadTestSend.head_recid = 0x02;
	p_tComm_Test_Send->g_tHeadTestSend.head_protoltype = 0xE1;
	p_tComm_Test_Send->g_tHeadTestSend.frame_cnt = 0x01;
	p_tComm_Test_Send->g_tHeadTestSend.head_crc = crc_8(p_tComm_Test_Send, CONFIG_COMMUSART_HEAD_LEN-1);

	p_tComm_Test_Send->g_tFrameTestSend.frame_start = 0xFE;
	p_tComm_Test_Send->g_tFrameTestSend.frame_len   = 6;
	p_tComm_Test_Send->g_tFrameTestSend.frame_func  = 0xd9;
	p_tComm_Test_Send->g_tFrameTestSend.frame_dates[0] = 10;
	p_tComm_Test_Send->g_tFrameTestSend.frame_dates[1] = 11;

	//crc to do
	p_tComm_Test_Send->g_tFrameTestSend.fram_crc = crc_16(&p_tComm_Test_Send->g_tFrameTestSend, CONFIG_COMMUSART_DATA_LEN-1);

	Comm_Tx_Hal((uint8_t *)p_tComm_Test_Send, sizeof(g_tComm_Test_Send));
}

void Comm_Task(void)
{
	Comm_Recv_Process();
	Comm_Tra_Procecss();
}
