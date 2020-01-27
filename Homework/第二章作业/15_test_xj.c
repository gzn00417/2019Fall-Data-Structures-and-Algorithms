#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *preXORnext;
}polynode;

polynode* create(polynode **preNode, polynode **nextNode); //创建环形链表
void output(polynode* head, polynode* prepre);

int main(){
    polynode *pre, *next;
    polynode *head = create(&pre, &next);
    printf("顺时针：");
    output(head, pre);
    return 0;
}

polynode *create(polynode **preNode, polynode **nextNode){
    polynode *head = (polynode*)malloc(sizeof(struct Node));
    int x, len=0, n=0;
    polynode *p = head;
    polynode *prep = 0;   //初始头节点的异或就相当于next，而0异或某个数等于它本身
    polynode *nextp;
    polynode *first = NULL, *second = NULL;
    printf("输入链表长度："); 
    scanf("%d", &len);
    getchar();
    printf("输入链表内容："); 
    for(n=1; n<=len; n++){
        scanf("%d", &x);
        polynode *newnode = (polynode*)malloc(sizeof(struct Node));
        if (n == 1) first = newnode;
        if (n == 2) second = newnode;
        newnode->data = x;
        nextp = newnode;
        p->preXORnext = (polynode*)((long long)prep ^ (long long)nextp);
        prep = p;
        p = newnode;
    }
    p->preXORnext = (polynode*)((long long)prep ^ (long long)first);	//将尾指针的链域与第一个节点相关联
    first->preXORnext = (polynode*)((long long)p ^ (long long)second);  //形成环后，更新第一个节点的链域
    *preNode = p;
    *nextNode = second;
    return head;
}

void output(polynode *head, polynode *prepre){
    polynode *first = head->preXORnext;
    polynode *pre = first;
    printf("%d", first->data);
    polynode *p = (polynode*)((long long)pre->preXORnext ^ (long long)(prepre));
    while(p != first){
        printf(" %d", p->data);
        prepre = pre;
        pre = p;
        p = (polynode*)((long long)pre->preXORnext ^ (long long)(prepre));
    }
}

