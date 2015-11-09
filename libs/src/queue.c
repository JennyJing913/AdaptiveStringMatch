#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

/*void test_queue(Queue_t *q)
  {
  char op;
  int value;

  for (;;) {
  printf("������ָ��: ");
  scanf(" %c", &op);
  while (getchar() != '\n')
  ;

  switch(op) {
  case 'i':  
  printf("������ֵ: ");
  scanf("%d", &value);
  in_queue(q, value);
  break;
  case 'd': out_queue(q);break;
  case 'f': 
  if ((value = get_q_first(q)) != EMPTY)
  printf("��һ��Ԫ��Ϊ: %d", value);
  else
  puts("���п�!");
  break;
  case 'l': if ((value = get_q_last(q)) != EMPTY)
  printf("���һ��Ԫ��Ϊ: %d", value);
  else
  puts("���п�!");
  break;
  case 'p': print_queue(q);break;
  case 'q': return;break;
  default: puts("���Ϸ�ָ��!");
  }
  printf("\n");
  }

  des_queue(q);
  }*/

Queue_t *make_queue(void)
{
     return CALLOC(1, Queue_t);
}

void free_queue(Queue_t *q)
{
     clean_queue(q);
     free(q);
}

void clean_queue(Queue_t *q) /*��ն������������������нṹ*/
{
     Q_Node_t *free_node;

     while (q->head) {
          free_node = q->head;
          q->head = q->head->next;
          free(free_node);
     }
	
     q->tail = NULL;
     q->count = 0;
}

int queue_is_empty(Queue_t *q)
{
     return q->count == 0;
}

void in_queue(Queue_t *q, Q_Value_t value) /*����һ��Ԫ��*/
{
     Q_Node_t *new_node =  MALLOC(1, Q_Node_t);

     new_node->value = value;
     new_node->next = NULL;

     if (queue_is_empty(q)) {/*�����һ���ڵ�*/
          q->head = new_node;
          q->tail = new_node;
     } else {	
          q->tail->next = new_node;
          q->tail = new_node;
     }

     q->count++;
}

Q_Value_t out_queue(Queue_t *q) /*ɾ��һ��Ԫ��*/
{
     Q_Node_t* free_node;
     Q_Value_t value;

     if (queue_is_empty(q)) {
          puts("The queue is empty!");
          return EMPTY;
     }

     value = q->head->value;
     free_node = q->head;
     q->head = q->head->next;
     free(free_node);
     q->count--;

     if (queue_is_empty(q)) /*ɾ�������һ���ڵ�*/
          q->tail = NULL;

     return value;
}

Q_Value_t get_q_first(Queue_t *q) /*���ض��е�һ��Ԫ��ֵ������ɾ��*/
{
     if (queue_is_empty(q))
          return EMPTY;
     else
          return q->head->value;
}

Q_Value_t get_q_last(Queue_t *q)/*���ض������һ��Ԫ��ֵ������ɾ��*/
{
     if (queue_is_empty(q))
          return EMPTY;
     else	
          return q->tail->value;
}

#ifdef DEBUG
void print_queue(Queue_t *q)
{
     Q_Node_t *index;
     FILE *fp_result;

     fp_result = fopen("./queue_content", "w");
     
     if (queue_is_empty(q)) {
          printf("�ն���!\n");
          fputs("�ն���!\n", fp_result);
          return;
     }

     printf("�����й��� %ld Ԫ��:\n ", q->count);
     fprintf(fp_result, "�����й��� %ld Ԫ��:\n ", q->count);
     for (index = q->head; index; index = index->next) {
          printf("%ld ", index->value);
          fprintf(fp_result, "%ld ", index->value);
     }

     fclose(fp_result);
}
#endif