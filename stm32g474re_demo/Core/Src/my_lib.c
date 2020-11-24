
#include "stdlib.h"
#include "stdio.h"
#include "my_lib.h"

//*********************** circular queue ****************//
int32_t is_DeCirqueempty(T_DeCirqueDate *p_quehead)
{
    if (NULL == p_quehead)
        return 0;
    
    if (p_quehead->size <= 0)
    {
        return 1;
    }

    return 0;
}

int32_t DeCirque_pop(T_DeCirqueDate *p_quehead, uint8_t *p_buf, uint8_t buf_len)
{
	uint8_t i = 0;

    if (NULL == p_quehead)
        return -1;
    if ((buf_len > p_quehead->size) || (buf_len <= 0))
    	return -1;

    for (i = 0; i < buf_len; i ++)
    {
    	p_buf[i] = p_quehead->p_queuebuf[p_quehead->front];
		p_quehead->front = (p_quehead->front + 1) % (p_quehead->cap);
		p_quehead->size -= 1;
    }
    return 1;
}

int32_t DeCirque_push(T_DeCirqueDate *p_quehead, uint8_t *p_buf, uint8_t buf_len)
{
	uint8_t i = 0;

    if (NULL == p_quehead)
        return -1;
    if (NULL == p_quehead->p_queuebuf)
        return -1;
    if (buf_len <= 0)
    	return -1;

    for (i = 0; i < buf_len; i ++)
    {
    	p_quehead->p_queuebuf[p_quehead->rear] = p_buf[i];
		p_quehead->rear = (p_quehead->rear + 1) % (p_quehead->cap);
		if (p_quehead->size < p_quehead->cap)
			p_quehead->size += 1;
		else
		{
			p_quehead->front = p_quehead->rear;
		}
    }
    
    return 1;
};

T_DeCirqueDate *DeCirque_init(int32_t buf_len)
{
    if (buf_len > 0)
    {
        T_DeCirqueDate *p_queue = (T_DeCirqueDate *)malloc(sizeof(T_DeCirqueDate));
        uint8_t *p_buf = (uint8_t *)malloc(buf_len * sizeof(uint8_t));

        if ((NULL == p_queue) || (NULL == p_buf))
        {
            free(p_queue);
            free(p_buf);
            return NULL;
        }
        p_queue->cap = buf_len;
        p_queue->rear = 0;
        p_queue->front = 0;
        p_queue->size = 0;
        p_queue->p_queuebuf = p_buf;

        return p_queue;
    }
    return NULL;
}


//*********************** non-circular queue ****************//
int32_t is_Dequeempty(T_DequeDate *p_quehead)
{
    if (NULL == p_quehead)
        return 0;
    
    if (p_quehead->front >= p_quehead->rear)
    {
        return 1;
    }

    return 0;
}

int32_t Deque_pop(T_DequeDate *p_quehead, uint8_t *p_val)
{
    if (NULL == p_quehead)
        return -1;

    if (!is_Dequeempty(p_quehead))
    {
        *p_val = p_quehead->p_queuebuf[p_quehead->front];
        p_quehead->front = (p_quehead->front + 1) % (p_quehead->cap);
        return 1;
    }
    return -2;
}

int32_t Deque_push(T_DequeDate *p_quehead, int8_t value)
{
    if (NULL == p_quehead)
        return -1;

    if (NULL == p_quehead->p_queuebuf)
        return -1;
    
    p_quehead->p_queuebuf[p_quehead->rear] = value;
    p_quehead->rear = (p_quehead->rear + 1) % (p_quehead->cap);

    return 1;
};

T_DequeDate *Deque_init(int32_t buf_len)
{
    if (buf_len > 0)
    {
        T_DequeDate *p_queue = (T_DequeDate *)malloc(sizeof(T_DequeDate));
        uint8_t *p_buf = (uint8_t *)malloc(buf_len * sizeof(uint8_t));

        if ((NULL == p_queue) || (NULL == p_buf))
        {
            free(p_queue);
            free(p_buf);
            return NULL;
        }
        p_queue->cap = buf_len;
        p_queue->rear = 0;
        p_queue->front = 0;
        p_queue->p_queuebuf = p_buf;

        return p_queue;
    }
    return NULL;
}

//*********************** linked_list ****************//
T_node linked_head = {0};

T_node *linked_list_inverse(T_node *p_head)
{
    T_node *p_pre = NULL;
    T_node *p_cur = NULL;
    T_node *p_next = NULL;

    if (NULL == p_head)
        return NULL;

    p_cur = p_head;
    while (NULL != p_cur)
    {
        p_next = p_cur->p_next;
        p_cur->p_next = p_pre;

        p_pre = p_cur;
        p_cur = p_next;
    }
    return p_pre;
}

T_node *linked_list_tail(T_node *p_head)
{
    T_node *p_temp = NULL;

    if (NULL == p_head)
        return NULL;

    p_temp = p_head;
    while (NULL != p_temp->p_next)
    {
        p_temp = p_temp->p_next;
    }

    return p_temp;
}

int32_t linked_list_del(T_node *p_head, T_node *p_item)
{
    T_node *p_temp = NULL;
    T_node *p_pre  = NULL;

    if ((NULL == p_item) || (NULL == p_head) || (p_head == p_item))
        return -1;

    p_temp = p_head->p_next;
    p_pre  = p_head;
    while (NULL != p_temp)
    {
        if (p_item == p_temp)
        {
            p_pre->p_next = p_temp->p_next;
            p_temp->p_next = NULL;
            free(p_temp);
            return 1;
        }
        p_pre = p_temp;
        p_temp = p_temp->p_next;
    }
    return -2;
}

int32_t linked_list_insert(T_node *p_pre, T_node *p_item)
{
    T_node *p_temp = NULL;

    if ((NULL == p_pre) || (NULL == p_item))
        return -1;
    
    p_temp = p_pre->p_next;
    p_pre->p_next = p_item;
    p_item->p_next = p_temp;

    return 1;
}

T_node *linked_list_creat(void)
{
    T_node *p_list = (T_node *)malloc(sizeof(T_node));

    if (NULL == p_list)
        return NULL;

    p_list->value = 0;
    p_list->p_next = NULL;

    return p_list;
}

#if 0
int main()
{
    printf("%s", "Hello World!\n");

/*
    T_node *p_list1 = NULL;
    T_node *p_list2 = NULL;
    T_node *p_list3 = NULL;
    T_node *p_tail  = NULL;

    p_list1 = linked_list_creat();
    p_tail  = linked_list_tail(&linked_head);
    linked_list_insert(p_tail, p_list1);
    p_list2 = linked_list_creat();
    p_tail  = linked_list_tail(&linked_head);
    linked_list_insert(p_tail, p_list2);
    p_list3 = linked_list_creat();
    p_tail  = linked_list_tail(&linked_head);
    linked_list_insert(p_tail, p_list3);

    linked_list_inverse(&linked_head);

    //linked_list_del(&linked_head, p_list2);
    //linked_list_del(&linked_head, p_list1);

    printf("linked-list test end");
*/
    uint8_t read_data = 0;
    int32_t code = 0;
   /* T_DequeDate *p_quehead = Deque_init(5);

    Deque_push(p_quehead, 10);
    Deque_push(p_quehead, 11);
    Deque_push(p_quehead, 12);
    Deque_push(p_quehead, 13);
    Deque_push(p_quehead, 14);
    Deque_push(p_quehead, 15);

    code = Deque_pop(p_quehead, &read_data);
    code = Deque_pop(p_quehead, &read_data);
    code = Deque_pop(p_quehead, &read_data);
    code = Deque_pop(p_quehead, &read_data);
    code = Deque_pop(p_quehead, &read_data);
    code = Deque_pop(p_quehead, &read_data);*/

    T_DeCirqueDate *p_quehead  = DeCirque_init(5);
    DeCirque_push(p_quehead, 10);
    DeCirque_push(p_quehead, 11);
    DeCirque_push(p_quehead, 12);
    DeCirque_push(p_quehead, 13);
    DeCirque_push(p_quehead, 14);
    DeCirque_push(p_quehead, 15);

    code = DeCirque_pop(p_quehead, &read_data);
    code = DeCirque_pop(p_quehead, &read_data);
    code = DeCirque_pop(p_quehead, &read_data);
    code = DeCirque_pop(p_quehead, &read_data);
    code = DeCirque_pop(p_quehead, &read_data);
    code = DeCirque_pop(p_quehead, &read_data);

    printf("cirqueue test end");

}
#endif

