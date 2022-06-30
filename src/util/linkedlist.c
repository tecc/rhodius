#include <rhodius/util/linkedlist.h>
#include <stddef.h>

void RhList_Create(struct RhLinkedList* out) {
    out->first = NULL;
    out->last = NULL;
}
void RhList_Append(struct RhLinkedList* list, struct RhLinkedListNode* node) {
    if (list->first == NULL) { // If first is null, then last is probably null too
        list->first = node;    // Because they are, we can just set both first and last to the node and say it's done
        list->last = node;
        return;
    }

    node->previous = list->last;
    node->next = NULL;
    list->last = node;
}
