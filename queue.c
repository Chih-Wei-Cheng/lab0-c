#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head)
        return NULL;
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, l, list) {
        q_release_element(entry);
    }
    free(l);
}
/* q_insert */
static inline bool q_insert(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *entry = malloc(sizeof(element_t));
    if (entry == NULL)
        return false;
    entry->value = strdup(s);
    if (entry->value == NULL) {
        free(entry);
        return false;
    }
    list_add(&entry->list, head);

    return true;
}
/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    return q_insert(head, s);
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    return q_insert(head->prev, s);
}
static inline element_t *q_remove(struct list_head *node,
                                  char *sp,
                                  size_t bufsize)
{
    if (!node || list_empty(node))
        return NULL;
    element_t *entry = container_of(node, element_t, list);
    if (sp) {
        strncpy(sp, entry->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_del(node);
    return entry;
}
/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    return q_remove(head->next, sp, bufsize);
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    return q_remove(head->prev, sp, bufsize);
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    int cnt = 0;
    if (head == NULL || list_empty(head))
        return 0;
    struct list_head *node;
    list_for_each (node, head) {
        cnt++;
    }
    return cnt;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (head == NULL || list_empty(head))
        return false;
    struct list_head *from_head = head->next, *from_tail = head->prev;
    while ((from_head != from_tail) && (from_head->next != from_tail)) {
        from_head = from_head->next;
        from_tail = from_tail->prev;
    }
    list_del(from_tail);
    element_t *entry = container_of(from_tail, element_t, list);
    q_release_element(entry);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (head == NULL)
        return false;
    if (list_empty(head))
        return true;

    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
