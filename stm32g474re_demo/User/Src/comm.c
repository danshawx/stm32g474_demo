#include "comm.h"
#include "main.h"

comm_test_send_t g_tcomm_test_send = {0};

static void comm_recv_process(void)
{
	if (SUCCESS == comm_unpack_fun())
	{

	}
}

static void comm_tra_procecss(void)
{
	//uint8_t i = 0;
	//uint16_t tx_crc16 = 0;
	comm_test_send_t *p_tcomm_test_send = (comm_test_send_t *)g_ausarttxbuf;

	p_tcomm_test_send->g_theadtestsend.head_start = 0xff;
	p_tcomm_test_send->g_theadtestsend.head_traid = 0x01;
	p_tcomm_test_send->g_theadtestsend.head_recid = 0x02;
	p_tcomm_test_send->g_theadtestsend.head_protoltype = 0xe1;
	p_tcomm_test_send->g_theadtestsend.frame_cnt = 0x01;
	p_tcomm_test_send->g_theadtestsend.head_crc = crc_8(p_tcomm_test_send, CONFIG_COMMUSART_HEAD_LEN-1);

	p_tcomm_test_send->g_tframetestsend.frame_start = 0xfe;
	p_tcomm_test_send->g_tframetestsend.frame_len   = 6;
	p_tcomm_test_send->g_tframetestsend.frame_func  = 0xd9;
	p_tcomm_test_send->g_tframetestsend.frame_dates[0] = 10;
	p_tcomm_test_send->g_tframetestsend.frame_dates[1] = 11;

	//crc to do
	p_tcomm_test_send->g_tframetestsend.fram_crc = crc_16(&p_tcomm_test_send->g_tframetestsend, CONFIG_COMMUSART_DATA_LEN-1);

	hal_comm_tx((uint8_t *)p_tcomm_test_send, sizeof(g_tcomm_test_send));
}

void comm_task(void)
{
	comm_recv_process();
	comm_tra_procecss();
}
