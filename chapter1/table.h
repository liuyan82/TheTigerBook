
typedef struct table * Table_;

struct table
{
    string id;
    int value;
    Table_ tail;
};

Table_ Table(string id, int value, Table_ tail);
int lookup(string id, Table_ head);
Table_ update(string id, int value, Table_ head);

