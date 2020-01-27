#include <stdio.h>

typedef struct node
{
	int data;
	long long adr;
}Linklist;

Linklist *head,*last;
int n;

int main()
{
	head=(Linklist*)malloc(sizeof(Linklist));
	last=head;
	scanf("%d",&n);
	int i,x;
	for (i=1;i<=n;i++)
	{
		scanf("%d",&x);
		Linklist *p;
		p=(Linklist*)malloc(sizeof(Linklist));
		p->data=x;
		p->adr=(long long)(last)^(long long)(p);

	}
	return 0;
}
