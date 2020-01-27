#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define Point_Num 100
#define Child_Num 2
class Tree
{
	public:
		char val;
		Tree *son[Child_Num],*fa;
		Tree()
		{
			for (int i=0;i<Child_Num;i++) son[i]=NULL;
			fa=NULL;
		}
		void init(char value){val=value;}
		void add(Tree *child,int child_num)
		{
			son[child_num]=child;
			child->fa=this;
		}
		bool leaf(){return this==NULL?false:son[0]==NULL&&son[1]==NULL;}
};
class node
{
	public:
		Tree *data;
		node *next;
};
class Queue//head<x<=tail
{
	public:
		node *head,*tail;
		Queue()
		{
			head=new node();
			head->next=NULL;
			tail=head;
		}
		bool empty(){return head==tail;}
		void push(Tree *member)
		{
			node *x=new node();
			x->data=member;
			tail->next=x;
			x->next=NULL;
			tail=x;
		}
		Tree *pop()
		{
			if (empty()) return NULL;
			Tree *pop_obj=front();
			node *last=head;
			head=head->next;
			delete last;
			return pop_obj;
		}
		Tree *front(){return head->next->data;}
		Tree *back(){return tail->data;}
};
class Stack
{
	public:
		node *top;
		bool empty(){return top->next==NULL;}
		Stack()
		{
			top=new node();
			top->data=NULL;
			top->next=NULL;
		}
		void push(Tree *member)
		{
			node *x=new node();
			x->data=member;
			x->next=top;
			top=x;
		}
		Tree *pop()
		{
			if (empty()) return NULL;
			Tree *pop_obj=get_top();
			node *last=top;
			top=top->next;
			delete last;
			return pop_obj;
		}
		Tree *get_top()
		{
			if (empty()) return NULL;
			return top->data;
		}
};

void level_trave(Tree *head)
{
	Queue qu;
	for (qu.push(head);!qu.empty();)
	{
		for (int i=0;i<Child_Num;i++) if (qu.front()->son[i]!=NULL) qu.push(qu.front()->son[i]);
		printf("%c ",qu.pop()->val);
	}
}

void pre_order_recursion(Tree *head)
{
	printf("%c ",head->val);
	if (head->son[0]!=NULL) pre_order_recursion(head->son[0]);
	if (head->son[1]!=NULL) pre_order_recursion(head->son[1]);
}

void in_order_recursion(Tree *head)
{
	if (head->son[0]!=NULL) in_order_recursion(head->son[0]);
	printf("%c ",head->val);
	if (head->son[1]!=NULL) in_order_recursion(head->son[1]);
}

void post_order_recursion(Tree *head)
{
	if (head->son[0]!=NULL) post_order_recursion(head->son[0]);
	if (head->son[1]!=NULL) post_order_recursion(head->son[1]);
	printf("%c ",head->val);
}

void pre_order_non_recur(Tree *head)
{
	Stack sta;
	Tree *x=head;
	while (!sta.empty()||x!=NULL)
	{
		if (x!=NULL)
		{
   			printf("%c ",x->val);
			sta.push(x);
			x=x->son[0];
		}
		else x=sta.pop()->son[1];
	}
}

void in_order_non_recur(Tree *head)
{
	Stack sta;
	Tree *x=head;
	while (!sta.empty()||x!=NULL)
	{
		if (x!=NULL)
		{
			sta.push(x);
			x=x->son[0];
		}
		else
		{
   			if (sta.get_top()!=NULL) printf("%c ",sta.get_top()->val);
			x=sta.pop()->son[1];
		}
	}
}

void post_order_non_recur(Tree *head)
{
	Stack sta;
	Tree *t,*cur,*pre;
	sta.push(head);
	while (!sta.empty())
	{
		t=sta.get_top();
		if ((t->son[0]==NULL&&t->son[1]==NULL)||(pre!=NULL&&(pre==t->son[0]||pre==t->son[1])))
		{
			cur=sta.pop();
			printf("%c ",cur->val);
			pre=cur;
		}
		else
		{
			if (t->son[1]!=NULL) sta.push(t->son[1]);
			if (t->son[0]!=NULL) sta.push(t->son[0]);
		}
	}
}

bool complete_binary_tree(Tree *head)
{
	Queue qu;
	qu.push(head);
	Tree *last=NULL;
	while (!qu.empty())
	{
		if ((qu.front()->son[0]==NULL&&qu.front()->son[1]!=NULL)||(last->leaf()&&!last->leaf())) return false;
		for (int i=0;i<Child_Num;i++) if (qu.front()->son[i]!=NULL) qu.push(qu.front()->son[i]);
		last=qu.pop();
	}
	return true;
}

char LCA(Tree *head,Tree *x,Tree *y)
{
	Tree *a=x,*b=y;
	while (a!=b)
	{
		a=(a==head?y:a->fa);
		b=(b==head?x:b->fa);
	}
	return a->val;
}

int main()
{
	freopen("init.txt","r",stdin);
	//freopen("ans.txt","w",stdout);
	Tree *list[Point_Num];
	int n,head_num,numx,numy;
	char x,chx,chy;
	scanf("%d\n",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%c ",&x);
		list[i]=new Tree();
		list[i]->init(x);
	}
	scanf("%d",&head_num);
	for (int i=0,di,si,ni;i<n-1;i++)//dad_i son_i num_i
	{
		scanf("%d%d%d",&di,&si,&ni);
		list[di]->add(list[si],ni);
	}
	
	printf("level_trave:          ");	level_trave(list[head_num]);			printf("\n");
	printf("pre_order_recursion:  ");	pre_order_recursion(list[head_num]);	printf("\n");
	printf("in_order_recursion:   ");	in_order_recursion(list[head_num]);		printf("\n");
	printf("post_order_recursion: ");	post_order_recursion(list[head_num]);	printf("\n");
	printf("pre_order_non_recur:  ");	pre_order_non_recur(list[head_num]);	printf("\n");
	printf("in_order_non_recur:   ");	in_order_non_recur(list[head_num]);		printf("\n");
	printf("post_order_non_recur: ");	post_order_non_recur(list[head_num]);	printf("\n");

	cout<<"complete_binary_tree: "<< boolalpha << complete_binary_tree(list[head_num])<<endl;
	scanf("%c %c",&chx,&chy);
	for (int i=0;i<n;i++)
	{
		if (list[i]->val==chx) numx=i;
		if (list[i]->val==chy) numy=i;
	}
	cout<<"lowest_common_ancestor: " <<	LCA(list[head_num],list[numx],list[numy]) <<endl;

	fclose(stdin);
	//fclose(stdout);
	return 0;
}
