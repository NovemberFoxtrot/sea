#ifndef dlist_h
#define dlist_h

#include <stdlib.h>

struct DListNode;

typedef struct DListNode {
	struct DListNode *next;
	struct DListNode *prev;
	void *value;	
} DListNode;

typedef struct DList {
	int count;
	DListNode *first;
	DListNode *last;
} DList;

DList *DList_create(void);
void DList_destroy(DList *dlist);
void DList_clear(DList *dlist);
void DList_clear_destroy(DList *dlist);

#define DList_count(A) ((A)->count)
#define DList_first(A) ((A)->first != NULL ? (A)->first->value : NULL )
#define DList_last(A) ((A)->last != NULL ? (A)->last->value : NULL )

void DList_push(DList *dlist, void *value);
void *DList_pop(DList *dlist);

void DList_unshift(DList *dlist, void *value);
void *DList_shift(DList *dlist);

void *DList_remove(DList *dlist, DListNode *node);

#define DLIST_FOREACH(L, S, M, V) DListNode *_node = NULL;\
	DListNode *V = NULL;\
	for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
