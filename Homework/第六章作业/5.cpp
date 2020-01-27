typedef struct celltype
{
    records data;
    celltype *next;
} List;

void InsertSort(int arr[])
{
    List *head;
    head = (*List)malloc(sizeof(List));
    head->data = arr[1];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < head->data)
        {
            List *y;
            y = (*List)malloc(sizeof(List));
            y->data = arr[i];
            y->next = head;
            head = y;
        }
        List *x = head;
        for (; x->next != NULL; x = x->next)
            if (arr[i] <= x->next->data) break;
        List *y;
        y = (*List)malloc(sizeof(List));
        y->data = arr[i];
        y->next = x->next;
        x->next = y;
    }
    for (List *x = head; x != NULL; x = x->next) printf("%d ", x->data);
}

void SelectSort(int arr[])
{
    List *head, *last;
    for (int i = 1; i <= n; i++)
    {
        int minx = 0x7fffffff, x;
        for (int j = i; j <= n; j++)
            if (arr[j] < minx) minx = arr[j], x = j;

        List *y;
        y = (*List)malloc(sizeof(List));
        y->data = minx;
        y->next = NULL;
        if (i == 1)
            head = y;
        else
        {
            last->next = y;
        }
        last = y;
        int t = arr[x];
        arr[x] = arr[i];
        arr[i] = t;
    }
    for (List *x = head; x != NULL; x = x->next) printf("%d ", x->data);
}
