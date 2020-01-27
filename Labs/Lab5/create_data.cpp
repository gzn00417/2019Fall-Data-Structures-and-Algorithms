#include <cstdio>
#include <cstdlib>
#define N 100000
#define M (1 << 30)
int main()
{
    freopen("init.txt", "w", stdout);
    printf("%d\n", N);
    for (int j = 1; j <= 5; j++, printf("\n"))
        for (int i = 1; i <= N; i++)
        {
            int x = rand() % M + 1, y = rand() % 15;
            x = x << y;
            printf("%d ", x);
        }
    fclose(stdout);
    return 0;
}
