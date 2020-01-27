#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
using namespace std;
#define Child_Num 2
#define N 142857
#define MAX 0x7fffffff

class BSTree // 小于：左子树   大于：右子树
{
public:
    int val, LD, RD, BF;
    BSTree *son[Child_Num], *fa;
    BSTree()
    {
        for (int i = 0; i < Child_Num; i++) son[i] = NULL;
        fa = NULL;
        BF = LD = RD = 0;
    }
    void add(BSTree *child, int child_num)
    {
        son[child_num] = child;
        child->fa = this;
    }
    void sorted() // 打印中序遍历，排序结果
    {
        if (son[0] != NULL) son[0]->sorted();
        printf("%-4d", val);
        if (son[1] != NULL) son[1]->sorted();
    }
    bool leaf() { return this == NULL ? false : son[0] == NULL && son[1] == NULL; }
    int height() { return max(LD, RD); }
    void calcBF()
    {
        if (this->leaf()) { return; }
        else
        {
            if (son[0] != NULL) son[0]->calcBF(), LD = son[0]->height() + 1;
            if (son[1] != NULL) son[1]->calcBF(), RD = son[1]->height() + 1;
        }
        this->BF = LD - RD;
    }
    void insert(BSTree **head)
    {
        if (*head == NULL)
        {
            *head = this;
            return;
        }
        for (BSTree *f1 = *head, *f2 = f1; f1 != NULL; f2 = f1)
        {
            f1 = this->val <= f1->val ? f1->son[0] : f1->son[1];
            if (f1 == NULL) f2->add(this, this->val <= f2->val ? 0 : 1);
        }
    }
    void del(BSTree **head)
    {
        if (son[0] == NULL && son[1] == NULL)
        {
            fa->son[0] == this ? fa->son[0] = NULL : fa->son[1] = NULL;
            delete this;
            return;
        }
        else if (son[0] != NULL && son[1] != NULL) // 左儿子最右
        {
            BSTree *x = son[0];
            while (x->son[1] != NULL) x = x->son[1];
            this->val = x->val;
            if (x == son[0] && x->son[0] != NULL) { add(x->son[0], 0); }
            else
                x->fa->son[1] = x->son[0];
            delete x;
        }
        else
        {
            if (son[1] == NULL) // 右子树为空
            {
                if (fa != NULL) { fa->add(son[0], this == fa->son[0] ? 0 : 1); }
                else
                {
                    son[0]->fa = NULL;
                    *head = son[0];
                }
            }
            else if (son[0] == NULL) // 左子树为空
            {
                if (fa != NULL) { fa->add(son[1], this == fa->son[0] ? 0 : 1); }
                else
                {
                    son[1]->fa = NULL;
                    *head = son[1];
                }
            }
            delete this;
        }
    }
    int find_count(int value, int cnt)
    {
        if (value == this->val) return cnt;
        return value < val ? (son[0] == NULL ? -cnt : son[0]->find_count(value, cnt + 1)) : (son[1] == NULL ? -cnt : son[1]->find_count(value, cnt + 1));
    }
};

void Delete(BSTree *arr[], BSTree **head) // 删除节点
{
    int m;
    scanf("%d", &m);
    for (int i = 1, x; i <= m; i++)
    {
        scanf("%d", &x);
        if (!arr[x])
        {
            printf("None\n");
            continue;
        }
        arr[x]->del(head);
        (*head)->sorted();
        cout << endl;
    }
}

int Half_Search(int x, int n, int a[]) // 折半查找
{
    int l = 1, r = n, mid, length = 1;
    bool flag = false;
    while (l <= r)
    {
        mid = (l + r) / 2;
        if (x == a[mid])
        {
            flag = true;
            break;
        }
        (x < a[mid]) ? r = mid - 1 : l = mid + 1;
        length++;
    }
    return flag ? length : -length;
}

void Search(BSTree *head, int n, int a[]) // 查找节点
{
    clock_t sta, end;
    int m;
    int tree_succ_times = 0, tree_succ_length = 0, tree_fail_times = 0, tree_fail_length = 0;
    int half_succ_times = 0, half_succ_length = 0, half_fail_times = 0, half_fail_length = 0;
    scanf("%d", &m);

    cout << endl;

    sta = clock();
    for (int i = 1, x; i <= m; i++)
    {
        //srand((int)time(0));
        x = rand() % 2048 + 1;
        int length = head->find_count(x, 1);
        length > 0 ? (tree_succ_times += 1, tree_succ_length += length) : (tree_fail_times += 1, tree_fail_length += length);
    }
    end = clock();
    cout << "Tree:" << endl;
    printf("Success: %10d %8.3lf\n", tree_succ_times, 1.0 * tree_succ_length / tree_succ_times);
    printf("Failure: %10d %8.3lf\n", tree_fail_times, 1.0 * tree_fail_length / tree_fail_times);
    printf("It takes %.4lfs totally, %.6lfus per cmp.\n", (double)(end - sta) / CLOCKS_PER_SEC, 1000.0 * (double)(end - sta) / (tree_succ_length - tree_fail_length));

    cout << endl;

    sta = clock();
    for (int i = 1, x; i <= m; i++)
    {
        //srand((int)time(0));
        x = rand() % 2048 + 1;
        int length = Half_Search(x, n, a);
        length > 0 ? (half_succ_times += 1, half_succ_length += length) : (half_fail_times += 1, half_fail_length += length);
    }
    end = clock();
    cout << "Half:" << endl;
    printf("Success: %10d %8.3lf\n", half_succ_times, 1.0 * half_succ_length / half_succ_times);
    printf("Failure: %10d %8.3lf\n", half_fail_times, 1.0 * half_fail_length / half_fail_times);
    printf("It takes %.4lfs totally, %.6lfus per cmp.\n", (double)(end - sta) / CLOCKS_PER_SEC, 1000.0 * (double)(end - sta) / (half_succ_length - half_fail_length));

    cout << endl;
}

int main()
{
    freopen("init.txt", "r", stdin);
    int n, a[N];
    BSTree *arr[N], *head = NULL, *t;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        t = new BSTree();
        arr[a[i]] = t;
        t->val = a[i];
        t->insert(&head);
    }
    head->calcBF();
    sort(a + 1, a + n + 1);

    //Delete(arr, &head);
    Search(head, n, a);

    fclose(stdin);
    return 0;
}
