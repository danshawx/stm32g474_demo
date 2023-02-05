#include "main.h"


uint32_t comm_unpack_fun(void)
{
	//uint16_t unpack_cnt = 0;
	uint8_t u8_rxdata = 0;
	//static uint8_t unpack_phase = 0;

	while (!is_decirqueempty(p_usartrxque)) // || (unpack_cnt ++ < config_usart_rxque_maxlen))
	{
		if (1 == decirque_pop(p_usartrxque,&u8_rxdata, 1))
		{
			/*switch (unpack_phase)
			{
				case comm_usart_head_start:
				{
					if (comm_usart_procol_head_start == u8_rxdata)
					{
						unpack_phase = comm_usart_head_data;
					}
					break;
				}
				case comm_usart_head_data:
				{
					//decirque_pop(p_usartrxque, g_ausartrxbuf, )
					break;
				}

			}*/

		}
	}
	return 0;
}







