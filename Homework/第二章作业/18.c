#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	int data;
	struct node *next;
}Linklist;

Linklist *head,*last;
int n;

int main()
{
	head=(Linklist*)malloc(sizeof(Linklist));
	last=head;
	scanf("%d",&n);
	int i,x,ans=-1;
	Linklist *p;
	for (i=1;i<=n;i++)
	{
		scanf("%d",&x);
		p=(Linklist*)malloc(sizeof(Linklist));
		p->data=x;
		last->next=p;
		p->next=NULL;
		last=p;
	}
	scanf("%d",&x);
	for (p=head->next;p!=NULL;p=p->next)
	{
		ans++;
		if (p->data==x)
		{
			printf("%d\n",ans);
			return 0;
		}
	}
	p=(Linklist*)malloc(sizeof(Linklist));
	p->data=x;
	last->next=p;
	p->next=NULL;
	for (p=head->next;p!=NULL;p=p->next) printf("%d ",p->data);
	return 0;
}
