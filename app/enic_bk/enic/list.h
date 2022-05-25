#ifndef __LIST_H
#define __LIST_H

typedef struct list_head
{
    struct list_head *next, *prev;
} LIST_HeadTypeDef;

#define OFFSETOF(TYPE, MEMBER) ((intptr_t) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define CONTAINER_OF(ptr, type, member) ({                      \
    const typeof(((type *)0)->member) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - OFFSETOF(type,member) );})

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_INIT_HEAD(name) \
    name.prev = name.next = &(name)

#define LIST_HEAD(name) \
    LIST_HeadTypeDef name = LIST_HEAD_INIT(name)

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define LIST_Entry(ptr, type, member) \
    CONTAINER_OF(ptr, type, member)

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define LIST_ForEachEntry(pos, head, member)				\
    for (pos = LIST_Entry((head)->next, typeof(*pos), member);	\
         &pos->member != (head); 	\
         pos = LIST_Entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define LIST_ForEachEntrySafe(pos, n, head, member)			\
    for (pos = LIST_Entry((head)->next, typeof(*pos), member),	\
         n = LIST_Entry(pos->member.next, typeof(*pos), member);	\
         &pos->member != (head);					\
         pos = n, n = LIST_Entry(n->member.next, typeof(*n), member))

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int LIST_Empty(const LIST_HeadTypeDef *head)
{
    return head->next == head;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __LIST_Add(LIST_HeadTypeDef *_new,
                                 LIST_HeadTypeDef *prev,
                                 LIST_HeadTypeDef *next)
{
    next->prev = _new;
    _new->next = next;
    _new->prev = prev;
    prev->next = _new;
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void LIST_AddTail(LIST_HeadTypeDef *_new, LIST_HeadTypeDef *head)
{
    __LIST_Add(_new, head->prev, head);
}

static inline void LIST_AddHead(LIST_HeadTypeDef *_new, LIST_HeadTypeDef *head)
{
    __LIST_Add(_new, head, head->next);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __LIST_Del(LIST_HeadTypeDef *prev, LIST_HeadTypeDef *next)
{
    next->prev = prev;
    prev->next = next;
}

#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)
/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void LIST_Del(LIST_HeadTypeDef *entry)
{
    __LIST_Del(entry->prev, entry->next);
    entry->next = (LIST_HeadTypeDef*)LIST_POISON1;
    entry->prev = (LIST_HeadTypeDef*)LIST_POISON2;
}
#endif
