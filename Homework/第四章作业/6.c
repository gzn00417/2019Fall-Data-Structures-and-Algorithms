void Prim(int n, int start)
{
    int i,j,x,t,ans=0;
    for (i=1;i<=n;i++)
    {
        low[i]=v[start][i];
        point[i]=start;
    }
    point[start]=0;
    for (i=1;i<n;i++)
    {
        t=INF;
        x=0;
        for (j=1;i<=n;i++) if (point[j]&&low[j]<t)
        {
            x=j;
            t=low[j];
        }
        ans+=t;
        for (j=1;j<=n;j++) if (point[j]&&v[x][j]<low[j])
        {
            low[j]=v[x][j];
            point[j]=x;
        }
    }
}