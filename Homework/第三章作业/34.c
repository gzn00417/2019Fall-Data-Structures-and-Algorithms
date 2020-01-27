void print_tree(int x)
{
    if (x<=0) return;
    printf("(%d",key[x]);
    if (left[x]||right[x]) printf(":");
    print_tree(left[x]);
    if (left[x]&&right[x]) printf(",");
    print_tree(right[x]);
    printf(")");
}