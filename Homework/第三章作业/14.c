int path(int x)
{
    if (x<=0) return 0;
    return max(path(left[x])+lw[x],path(right[x])+rw[x]);
}
