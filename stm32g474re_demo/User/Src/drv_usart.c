#include "main.h"


uint8_t g_atxdmabuf[CONFIG_USARTDMA_TX_MAXLEN] = {0};
uint8_t g_arxdmabuf[CONFIG_USARTDMA_RX_MAXLEN] = {0};

uint8_t g_ausarttxbuf[CONFIG_USART_TX_MAXLEN] = {0};
uint8_t g_ausartrxbuf[CONFIG_USART_RX_MAXLEN] = {0};

decirquedate_t *p_usarttxque = NULL;
decirquedate_t *p_usartrxque = NULL;

void hal_comm_bufinit(void)
{
    p_usarttxque = decirque_init(CONFIG_USART_TXQUE_MAXLEN);
    p_usartrxque = decirque_init(CONFIG_USART_RXQUE_MAXLEN);
}

void hal_comm_dmauconf(void)
{
    /* (3) Configure the DMA functional parameters for transmission */
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2,
                           (uint32_t)g_atxdmabuf,
                           LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT),
                           LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, CONFIG_USARTDMA_TX_MAXLEN);

    /* (4) Configure the DMA functional parameters for reception */

    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
                           LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_RECEIVE),
                           (uint32_t)g_arxdmabuf,
                           LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, CONFIG_USARTDMA_RX_MAXLEN);

    /* (5) Enable DMA transfer complete/error interrupts  */
    //LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
    //LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_3);

    LL_USART_EnableDMAReq_RX(USART1);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    LL_USART_EnableIT_IDLE(USART1);

}

void hal_comm_tx(uint8_t *p_txbuf, uint8_t tx_len)
{
    uint8_t tx_dmalen = 0;

    decirque_push(p_usarttxque, p_txbuf, tx_len);
    if (!LL_DMA_IsEnabledChannel(DMA1, LL_DMA_CHANNEL_2))
    {
        tx_dmalen = (p_usarttxque->size < CONFIG_USARTDMA_TX_MAXLEN) ? p_usarttxque->size : CONFIG_USARTDMA_TX_MAXLEN;
        if (1 == decirque_pop(p_usarttxque, g_atxdmabuf, tx_dmalen))
        {
        	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, tx_dmalen);
        	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
            LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
            LL_USART_EnableDMAReq_TX(USART1);
        }
    }
}


//******************** handler ***********************
static void dma1_receivecomplete_callback(void)
{
	uint8_t rx_dmalen = 0;

	//LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_3);
	//LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);

	rx_dmalen = CONFIG_USARTDMA_RX_MAXLEN - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_3);
	decirque_push(p_usartrxque, g_arxdmabuf, rx_dmalen);

	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, CONFIG_USARTDMA_RX_MAXLEN);

	//LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
}

void comm_dma_chan2_handler(void)
{
    if(LL_DMA_IsActiveFlag_TC2(DMA1))
    {
        LL_DMA_ClearFlag_GI2(DMA1);
        /* Call function Transmission complete Callback */
        //DMA1_TransmitComplete_Callback();
        LL_USART_EnableIT_TC(USART1);
    }
    else if(LL_DMA_IsActiveFlag_TE2(DMA1))
    {
        /* Call Error function */
        //USART_TransferError_Callback();
    	LL_DMA_ClearFlag_TE2(DMA1);
    }
//    if(LL_DMA_IsActiveFlag_TC3(DMA1))
//    {
//        LL_DMA_ClearFlag_GI3(DMA1);
//        /* Call function Reception complete Callback */
//        //DMA1_ReceiveComplete_Callback();
//    }
//    else if(LL_DMA_IsActiveFlag_TE3(DMA1))
//    {
//    	LL_DMA_ClearFlag_TE3(DMA1);
//        /* Call Error function */
//        //USART_TransferError_Callback();
//    }
}

void comm_dma_chan3_handler(void)
{
//    if(LL_DMA_IsActiveFlag_TC2(DMA1))
//    {
//        LL_DMA_ClearFlag_GI2(DMA1);
//        /* Call function Transmission complete Callback */
//        //DMA1_TransmitComplete_Callback();
//        LL_USART_EnableIT_TC(USART1);
//    }
//    else if(LL_DMA_IsActiveFlag_TE2(DMA1))
//    {
//        /* Call Error function */
//        //USART_TransferError_Callback();
//    	LL_DMA_ClearFlag_TE2(DMA1);
//    }
    if(LL_DMA_IsActiveFlag_TC3(DMA1))
    {
        LL_DMA_ClearFlag_GI3(DMA1);
        /* Call function Reception complete Callback */
        //DMA1_ReceiveComplete_Callback();
    }
    else if(LL_DMA_IsActiveFlag_TE3(DMA1))
    {
    	LL_DMA_ClearFlag_TE3(DMA1);
        /* Call Error function */
        //USART_TransferError_Callback();
    }
}

void comm_usart1_tx_handler(void)
{
	 uint8_t tx_dmalen = 0;

	if (is_decirqueempty(p_usarttxque))
	{
		LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
	}
	else
	{
		tx_dmalen = (p_usarttxque->size < CONFIG_USARTDMA_TX_MAXLEN) ? p_usarttxque->size : CONFIG_USARTDMA_TX_MAXLEN;
		if (1 == decirque_pop(p_usarttxque, g_atxdmabuf, tx_dmalen))
		{
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, tx_dmalen);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
			//LL_USART_EnableDMAReq_TX(USART1);
		}
	}
}

void comm_usart1_handler(void)
{
	if (LL_USART_IsActiveFlag_TC(USART1))
	{
		LL_USART_ClearFlag_TC(USART1);
		LL_USART_DisableIT_TC(USART1);
		comm_usart1_tx_handler();
	}
	if (LL_USART_IsActiveFlag_IDLE(USART1))
	{
		LL_USART_ClearFlag_IDLE(USART1);
		LL_USART_DisableIT_IDLE(USART1);
		dma1_receivecomplete_callback();
		LL_USART_EnableIT_IDLE(USART1);
	}
}


