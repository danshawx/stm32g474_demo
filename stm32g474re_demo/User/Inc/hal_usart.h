#ifndef HAL_USART_H
#define HAL_USART_H


#define CONFIG_USARTDMA_TX_MAXLEN    (10)
#define CONFIG_USARTDMA_RX_MAXLEN    (20)

#define CONFIG_USART_TX_MAXLEN       (30)
#define CONFIG_USART_RX_MAXLEN       (30)

#define CONFIG_USART_TXQUE_MAXLEN     (CONFIG_USART_TX_MAXLEN * 3)
#define CONFIG_USART_RXQUE_MAXLEN     (CONFIG_USART_RX_MAXLEN * 2)

extern uint8_t g_aTXDMABuf[CONFIG_USARTDMA_TX_MAXLEN];
extern uint8_t g_aRXDMABuf[CONFIG_USARTDMA_RX_MAXLEN];

extern uint8_t g_aUsartTxBuf[CONFIG_USART_TX_MAXLEN];
extern uint8_t g_aUsartRxBuf[CONFIG_USART_RX_MAXLEN];

extern T_DeCirqueDate *p_usarttxque;
extern T_DeCirqueDate *p_usartrxque;


void Comm_DMAUconf_Hal(void);
void Comm_BufInit_Hal(void);
void Comm_Tx_Hal(uint8_t *p_txbuf, uint8_t tx_len);
//void Comm_DMA_USART_Handler(void);
void Comm_DMA_CHAN2_Handler(void);
void Comm_DMA_CHAN3_Handler(void);
void Comm_USART1_Handler(void);

#endif
