#include "dlist.h"
#include "dbg.h"

DList *DList_create() {
	return calloc(1, sizeof(DList));
}

void DList_destroy(DList *dlist) {
	DLIST_FOREACH(dlist, first, next, cur) {
		if (cur->prev) {
			free(cur->prev);
		}
	}

	free(dlist->last);
	free(dlist);
}

void DList_clear(DList *dlist) {
	DLIST_FOREACH(dlist, first, next, cur) {
		free(cur->value);
	}
}

void DList_clear_destroy(DList *dlist) {
	DList_clear(dlist);
	DList_destroy(dlist);
}

void DList_push(DList *dlist, void *value) {
	DListNode *dnode = calloc(1, sizeof(DListNode));
	check_mem(dnode);

	dnode->value = value;

	if(dlist->last == NULL) {
		dlist->first = dnode;
		dlist->last = dnode;
	} else {
		dlist->last->next = dnode;
		dnode->prev = dlist->last;
		dlist->last = dnode;
	}

	dlist->count++;

error:
	return ;
}

void *DList_pop(DList *dlist) {
	DListNode *dnode = dlist->last;
	return dnode != NULL ? DList_remove(dlist, dnode) : NULL;
}

void DList_unshift(DList *dlist, void *value) {
	DListNode *dnode = calloc(1, sizeof(DListNode));
	check_mem(dnode);

	dnode->value = value;

	if (dlist->first == NULL) {
		dlist->first = dnode;
		dlist->last = dnode;
	} else {
		dnode->next = dlist->first;
		dlist->first->prev = dnode;
		dlist->first = dnode;
	}

	dlist->count++;

error:
	return;
}

void *DList_shift(DList *dlist) {
	DListNode *dnode = dlist->first;
	return dnode != NULL ? List_remove(dlist, dnode) : NULL;
}

void *DList_remove(DList *dlist, DListNode *dnode) {
	void *result = NULL;
	
	check(dlist->first && dlist->last, "List is empty");
	check(dnode, "dnode can't be NULL");

	if (dnode == dlist->first && dnode == dlist->last) {
		dlist->first = NULL;
		dlist->last = NULL;
	} else if (dnode == dlist->first) {
		dlist->first = dnode->next;
		check(dlist->first != NULL, "Invalid list, somehow got a first that is NULL.");
		dlist->first->prev = NULL;
	} else if (dnode == dlist->last) {
		dlist->last = dnode->prev;
		check(dlist->last != NULL, "Invalid list, somehow got a next that is NULL.");
		dlist->last->next = NULL;
	} else {
		DListNode *after = dnode->next;
		DListNode *before = dnode->prev;
		after->prev = before;
		before->next = after;
	}

	dlist->count--;
	result = dnode->value;
	free(dnode);

error:
	return;
}
