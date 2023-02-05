#ifndef HAL_USART_H
#define HAL_USART_H


#define CONFIG_USARTDMA_TX_MAXLEN    (10)
#define CONFIG_USARTDMA_RX_MAXLEN    (20)

#define CONFIG_USART_TX_MAXLEN       (30)
#define CONFIG_USART_RX_MAXLEN       (30)

#define CONFIG_USART_TXQUE_MAXLEN     (CONFIG_USART_TX_MAXLEN * 3)
#define CONFIG_USART_RXQUE_MAXLEN     (CONFIG_USART_RX_MAXLEN * 2)

extern uint8_t g_atxdmabuf[CONFIG_USARTDMA_TX_MAXLEN];
extern uint8_t g_arxdmabuf[CONFIG_USARTDMA_RX_MAXLEN];

extern uint8_t g_ausarttxbuf[CONFIG_USART_TX_MAXLEN];
extern uint8_t g_ausartrxbuf[CONFIG_USART_RX_MAXLEN];

extern decirquedate_t *p_usarttxque;
extern decirquedate_t *p_usartrxque;


void hal_comm_dmauconf(void);
void hal_comm_bufinit(void);
void hal_comm_tx(uint8_t *p_txbuf, uint8_t tx_len);
//void comm_dma_usart_handler(void);
void comm_dma_chan2_handler(void);
void comm_dma_chan3_handler(void);
void comm_usart1_handler(void);

#endif
