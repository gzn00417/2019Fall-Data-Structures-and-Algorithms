#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct node{
	char data;
	struct node * next;
}Link;

Link* add(Link *h,char x)
{
	Link *p;
	p=(Link*)malloc(sizeof(Link));
	p->data=x;
	p->next=NULL;
	h->next=p;
	return p;
}

void print(Link *h,int len)
{
	Link *p;
	int l=len;
	for (p=h->next;p!=NULL&&l>0;p=p->next,l--) printf("%c",p->data);
	printf("\n");
	return;
}

void substr(Link *h,int m,int n)
{
	int i=0;
	Link *p=h;
	for (;i<m;i++) p=p->next;
	print(p,n);
	return;
}

int main()
{
	Link *head1,*last;
	head1=(Link*)malloc(sizeof(Link));
	last=head1;
	int l,i,m,n;
	char s[100];
	scanf("%s",s);
	l=strlen(s);
	for (i=0;i<l;i++) last=add(last,s[i]);
	scanf("%d%d",&m,&n);
	substr(head1,m,n);
	getchar();
	return 0;
}
