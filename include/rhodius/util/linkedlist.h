#ifndef RHODIUS_LINKEDLIST_H
#define RHODIUS_LINKEDLIST_H

struct RhList;
struct RhListNode;

struct RhList {
    struct RhListNode* first;
    struct RhListNode* last;
};
struct RhListNode {
    struct RhListNode* previous;
    struct RhListNode* next;
    void* value;
};

void RhList_Create(struct RhList* out);
void RhList_Append(struct RhList* list, struct RhListNode* node);

#endif