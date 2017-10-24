#include "util.h"
#include "table.h"
#include "string.h"

Table_ Table(string id, int value, Table_ tail)
{
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

int lookup(string id, Table_ head)
{
    while (head != NULL)
    {
        if (strcmp(head->id, id) == 0)
            return head->value;
        head = head->tail;
    }
    return 0;
}

Table_ update(string id, int value, Table_ head)
{
    return Table(id, value, head);
}
