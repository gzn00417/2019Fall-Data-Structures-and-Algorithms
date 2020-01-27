void preprocessing(int x)
{
    if (!x) return;
    int y=l[x];
    while (y) y=r[y];
    next[y]=x;
    preprocessing(l[x]);
    preprocessing(r[x]);
}
void trave(int root)
{
    int x=root;
    while (x) x=l[x];
    while (x)
    {
        printf("%d ",x);
        x=next[x];
    }
}