void floyd(int n)
{
    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<=n;i++)
        {
            for (int j=1;j<=n;j++) a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
        }
    }
}
int mid_point(int n)
{
    floyd(n);
    int lowp=INF;
    for (int i=1;i<=n;i++)
    {
        b[i]=INF;
        for (int j=1;j<=n;j++) b[i]=min(b[i],a[j][i]);
        lowp=(b[i]<b[lowp]?i:lowp);
    }
    return lowp;
}