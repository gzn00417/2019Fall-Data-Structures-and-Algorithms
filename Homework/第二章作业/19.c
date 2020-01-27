#include <stdio.h>
#include <malloc.h>

typedef struct node{
	int data;
	struct node * next;
}Link;

Link* add(Link *h,int x)
{
	Link *p;
	p=(Link*)malloc(sizeof(Link));
	p->data=x;
	p->next=NULL;
	h->next=p;
	return p;
}

void split(Link *h1,Link *h2)
{
	int index=0;
	Link *q,*pre=h1,*last=h2;
	for (q=h1->next;q!=NULL;q=q->next)
	{
		index++;
		if (index%2==0)
		{
			last->next=q;
			pre->next=q->next;
			q->next=NULL;
			last=q;
			q=pre;
		}
		else pre=q;
	}
	return;
}

void print(Link *h)
{
	Link *p;
	for (p=h->next;p!=NULL;p=p->next) printf("%d ",p->data);
	printf("\n");
	return;
}

int main()
{
	Link *head1,*last,*head2;
	head1=(Link*)malloc(sizeof(Link));
	head2=(Link*)malloc(sizeof(Link));
	last=head1;
	int n,x,i;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%d",&x);
		last=add(last,x);
	}
	split(head1,head2);
	print(head1);
	print(head2);
	return 0;
}
