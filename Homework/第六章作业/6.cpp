#include <cstdio>
#include <iostream>
#define N 100
struct score
{
    char name;
    float grade;
    int place;
} a[N], tmp, base;
struct point
{
    int l, r;
} sta[N];

int main()
{
    freopen("init.txt", "r", stdin);
    int n;
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) scanf("%c %f %d\n", &a[i].name, &a[i].grade, &a[i].place);
    for (int i = 1; i <= n; i++) printf("%c %.2f %d\n", a[i].name, a[i].grade, a[i].place);
    int l, r, top = 1;
    sta[top].l = 1;
    sta[top].r = n;
    while (top > 0)
    {
        l = sta[top].l;
        r = sta[top].r;
        top--;
        base = a[l];
        int h = l, t = r;
        while (h < t)
        {
            while (h < t && a[t].grade >= base.grade) t--;
            while (h < t && a[h].grade <= base.grade) h++;
            if (h < t)
            {
                tmp = a[h];
                a[h] = a[t];
                a[t] = tmp;
            }
        }
        a[l] = a[h];
        a[h] = base;
        if (l <= h - 1)
        {
            top++;
            sta[top].l = l;
            sta[top].r = h - 1;
        }
        if (h + 1 <= r)
        {
            top++;
            sta[top].l = h + 1;
            sta[top].r = r;
        }
    }
    printf("\n");
    for (int i = 1; i <= n; i++) printf("%c %.2f %d\n", a[i].name, a[i].grade, a[i].place);
    return 0;
}
