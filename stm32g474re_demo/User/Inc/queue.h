#ifndef MY_LIB_H
#define MY_LIB_H

/*
typedef unsigned char   uint8_t;     
typedef signed   char   int8_t;      
typedef unsigned int    uint16_t;    
typedef signed   int    int16_t;     
typedef unsigned long   uint32_t;    
typedef signed   long   int32_t;     
typedef float           float32;     
typedef double          float64;  
*/

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define SUCCESS      (int32_t)(1)
#define FAILED       (int32_t)(0)
#define PARAM_ILLEGA (int32_t)(-1)



typedef struct 
{
    int cap;
    int rear;
    int front;
    int size;
    uint8_t *p_queuebuf;
}decirquedate_t;


typedef struct 
{
    int cap;
    int rear;
    int front;
    uint8_t *p_queuebuf;
}dequedate_t;


typedef struct my_node
{
    int32_t value;
    struct my_node *p_next;
}node_t;

int32_t is_decirqueempty(decirquedate_t *p_quehead);
int32_t decirque_pop(decirquedate_t *p_quehead, uint8_t *p_buf, uint8_t buf_len);
int32_t decirque_push(decirquedate_t *p_quehead, uint8_t *p_buf, uint8_t buf_len);
decirquedate_t *decirque_init(int32_t buf_len);

#endif
