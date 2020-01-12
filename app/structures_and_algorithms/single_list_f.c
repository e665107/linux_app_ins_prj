#include "single_list_f.h"
#include <stdlib.h>
#include "fatal.h"

void insert_list(llink *list, int item)
{
    llink new = malloc(sizeof(struct List));

    if (!new)
        return;

    new->vertex = item;
    new->next = NULL;

    if (!*list)
    {
        *list = new;
        return;
    }

    llink cur = *list;

    while (cur->next)
        cur = cur->next;

    cur->next = new;
}

void display_list(llink list)
{
    while (list)
    {
        printf("%d ", list->vertex);
        list = list->next;
    }

    printf("\n");
}

llink insert_list_recursive(llink list, int item)
{
    if (!list)
    {
        llink new = malloc(sizeof(struct List));

        if (!new)
            return new;

        new->vertex = item;
        new->next = NULL;
        return new;
    }

    list->next = insert_list_recursive(list->next, item);
    return list;
}

llink search_list(llink list, int item)
{
    llink retval = NULL;

    while (list && !retval)
    {
        if (list->vertex == item)
            retval = list;

        list = list->next;
    }

    return retval;
}

int list_length(llink list)
{
    int length = 0;

    while (list)
    {
        length++;
        list = list->next;
    }

    return length;
}

llink find_item(llink list, int vertex)
{
    while (list)
    {
        if (list->vertex == vertex)
            return list;

        list = list->next;
    }

    return NULL;
}

void delete_item_advanced(llink node)
{
    llink next = node->next;

    if (next)
    {
        node->vertex = next->vertex;
        node->next = next->next;
        free(next);
    }

    else
        printf("cannot delete %d for its the last item\n", node->vertex);
}

llink get_middle_item(llink list)
{
    llink one_p = list, two_p = list;

    while (two_p)
    {
        two_p = two_p->next;

        if (two_p)
            two_p = two_p->next;

        if (two_p)
            one_p = one_p->next;
    }

    return one_p;
}

llink get_klast_item(llink list, int k)
{
    int i = 1;
    llink cur = list, curk = list;

    while (i++ <= k && cur)
        curk = curk->next;

    if (i > k && !curk)
        return cur;

    if (!curk)
        return NULL;

    while (curk)
    {
        cur = cur->next;
        curk = curk->next;
    }

    return cur;
}

llink merge_list(llink list1, llink list2)
{
    llink cur1 = list1, cur2 = list2;
    llink selected, newlist = NULL, newlist_cur = NULL;

    while (list1 && list2)
    {
        if (list1->vertex < list2->vertex)
        {
            selected = list1;
            list1 = list1->next;
        }

        else
        {
            selected = list2;
            list2 = list2->next;
        }

        if (!newlist)
        {
            newlist = selected;
            newlist_cur = newlist;
        }

        else
        {
            newlist_cur->next = selected;
            newlist_cur = newlist_cur->next;
        }
    }

    if (list1)
    {
        if (!newlist_cur)
            newlist = list1;

        else
            newlist_cur->next = list1;
    }

    if (list2)
    {
        if (!newlist_cur)
            newlist = list2;

        else
            newlist_cur->next = list2;
    }

    return newlist;
}

llink merge_list_recursive(llink list1, llink list2)
{
    if (list1 && list2)
    {
        if (list1->vertex < list2->vertex)
        {
            list1->next = merge_list_recursive(list1->next, list2);
            return list1;
        }

        else
        {
            list2->next = merge_list_recursive(list1, list2->next);
            return list2;
        }
    }

    else if (list1)
        return list1;

    else
        return list2;
}

void reverse_non_recursive(llink *list)
{
    llink prev = NULL, cur = *list, next;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *list = prev;
}

llink reverse_recursive(llink *list, llink cur)
{
    if (!cur)
        return NULL;

    llink prev = reverse_recursive(list, cur->next);
    cur->next = NULL;

    if (prev)
        prev->next = cur;

    else
        *list = cur;

    return cur;
}

int if_has_ring(llink list)
{
    llink cur_one = list, cur_two = list;
    int retval = 0;

    while (cur_two)
    {
        cur_one = cur_one->next;
        cur_two = cur_two->next;

        if (cur_two)
            cur_two = cur_two->next;

        if (cur_one == cur_two)
        {
            retval = 1;
            break;
        }
    }

    return retval;
}

void make_ring(llink list, llink that)
{
    llink cur = list;

    if (!cur)
        return;

    while (cur->next)
        cur = cur->next;

    cur->next = that;
}

llink find_item(llink list, int vertex)
{
    llink cur = list;

    while (cur)
    {
        if (cur->vertex == vertex)
            return cur;

        cur = cur->next;
    }

    return NULL;
}

