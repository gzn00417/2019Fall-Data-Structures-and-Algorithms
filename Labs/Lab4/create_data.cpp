#include <cstdio>
#include <cstdlib>
#define N 1024
#define M 2048
bool f[M + 5];
int main()
{
    freopen("data.txt", "w", stdout);
    printf("%d\n", N);
    for (int i = 1; i <= N; i++)
    {
        int x = rand() % M + 1;
        if (!f[x] && x % 2 != 0)
        {
            printf("%d ", x);
            f[x] = true;
        }
        else
            i--;
    }
    fclose(stdout);
    return 0;
}
