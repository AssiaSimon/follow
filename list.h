#ifndef _LIST_H_
#define _LIST_H_

struct _list_node{
    void *data; 
    struct _list_node * next; 
}; 

typedef struct _list_node s_node; 

s_node * list_create(void);
void * list_get_data(s_node *node);
void list_set_data (s_node *node,void *data);
s_node *list_next(s_node *node);
s_node *list_insert(s_node *head,void *data);
void displaylist(s_node *head, void (*display)(s_node*));
s_node * list_orderedAppend(s_node **head, int (*compare)(s_node*,void*), 
                            void * param); 
s_node * list_append(s_node * head, void * data);
s_node * list_remove (s_node * head, void * data );
s_node * list_headRemove(s_node *head); 
void listdestroy(s_node *head) ;

#endif