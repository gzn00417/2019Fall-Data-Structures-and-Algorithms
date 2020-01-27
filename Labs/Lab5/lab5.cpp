#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h>
using namespace std;
#define Swap(x, y) (a[x] = a[x] ^ a[y], a[y] = a[x] ^ a[y], a[x] = a[x] ^ a[y])
#define N 1000000
int a[N + 5];

void HeapAdjust(int x, int n) //调整堆
{
    if (x * 2 > n) return;
    int maxi = x * 2 + 1 > n ? x * 2 : (a[x * 2] < a[x * 2 + 1] ? x * 2 : x * 2 + 1);
    if (a[maxi] < a[x]) Swap(x, maxi), HeapAdjust(maxi, n);
}

void HeapSort(int n)
{
    for (int i = n; i >= 1; i--) HeapAdjust(i, n); //建立最小堆
    for (int i = n; i > 1; i--)
    {
        Swap(1, i); //取出堆根节点
        HeapAdjust(1, i - 1); //调整堆，此时大小减1
    }
}

void Print(int n)
{
    for (int i = 1; i < n; i++) printf("%d ", a[i]);
    printf("%d\n\n", a[n]);
}

void SelectSort(int n)
{
    int mini;
    for (int i = 1; i < n; i++)
    {
        mini = i;
        for (int j = i + 1; j <= n; j++)
            if (a[j] < a[mini]) mini = j;
        if (i != mini) Swap(i, mini);
    }
}

#define M 10
int main()
{
    freopen("init.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    DWORD sta, end;
    scanf("%d", &n);
    for (int j = 1; j <= 5; j++)
    {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sta = GetTickCount();
        for (int i = 1; i <= M; i++) HeapSort(n);
        end = GetTickCount();
        printf("Heap%d %.6lfs\n", j, (double)(end - sta) / 1000 / M);
    }
    for (int j = 1; j <= 5; j++)
    {
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        sta = GetTickCount();
        SelectSort(n);
        end = GetTickCount();
        printf("Select%d %.6lfs\n", j, (double)(end - sta) / 1000 / M);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}