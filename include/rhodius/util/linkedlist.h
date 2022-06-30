#ifndef RHODIUS_LINKEDLIST_H
#define RHODIUS_LINKEDLIST_H

struct RhLinkedList;
struct RhLinkedListNode;

struct RhLinkedList {
    struct RhLinkedListNode* first;
    struct RhLinkedListNode* last;
};
struct RhLinkedListNode {
    struct RhLinkedListNode* previous;
    struct RhLinkedListNode* next;
    void* value;
};

void RhList_Create(struct RhLinkedList* out);
void RhList_Append(struct RhLinkedList* list, struct RhLinkedListNode* node);

#endif