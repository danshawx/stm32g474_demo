#include "main.h"


uint32_t Comm_Unpack_Fun(void)
{
	//uint16_t unpack_cnt = 0;
	uint8_t u8_rxdata = 0;
	//static uint8_t unpack_phase = 0;

	while (!is_DeCirqueempty(p_usartrxque)) // || (unpack_cnt ++ < CONFIG_USART_RXQUE_MAXLEN))
	{
		if (1 == DeCirque_pop(p_usartrxque,&u8_rxdata, 1))
		{
			/*switch (unpack_phase)
			{
				case COMM_USART_HEAD_START:
				{
					if (COMM_USART_PROCOL_HEAD_START == u8_rxdata)
					{
						unpack_phase = COMM_USART_HEAD_DATA;
					}
					break;
				}
				case COMM_USART_HEAD_DATA:
				{
					//DeCirque_pop(p_usartrxque, g_aUsartRxBuf, )
					break;
				}

			}*/

		}
	}
}





