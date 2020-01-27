#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
class Point
{
public:
    class Edge
    {
    public:
        int val;
        Edge *next_edge;
        Point *origin, *terminal;
        Edge(){next_edge=NULL;origin=terminal=NULL;}
        void adjacency(Point *ori, int edge_val, Point *term)
        {
            val=edge_val;
            origin=ori;
            terminal=term;
            next_edge=ori->last_edge;
            ori->last_edge=this;
        }
    };
    int num;
    bool vis;
    Edge *last_edge;
    Point *next_point;
    Point(){last_edge=NULL;next_point=NULL;}
    void add_point(int number,Point **head)
    {
        num=number;
        if (*head==NULL) *head=this;
    	else
        {
            Point *back=*head;
            for (;back->next_point!=NULL;back=back->next_point);
            back->next_point=this;
        }
    }
    void add_edge(int edge_val, int term_num, Point *head)
    {
        Edge *new_edge=new Edge();
        Point *term;
        for (term=head;term!=NULL;term=term->next_point) if (term->num==term_num) break;
        if (term==NULL) printf("Error");
        new_edge->adjacency(this, edge_val, term);
    }
};
class Node
{
public:
	Point *data;
	Node *next;
	Node(){next=NULL;}
    void add(Point *p, Node **last)
    {
        data=p;
		if ((*last)!=NULL) (*last)->next=this;
        (*last)=this;
    }
};
class Queue//head<x<=tail
{
public:
	Node *head,*tail;
	Queue()
	{
		head=new Node();
		head->next=NULL;
		tail=head;
	}
	bool empty(){return head==tail;}
	void push(Point *member)
	{
		Node *x=new Node();
		x->data=member;
		tail->next=x;
		x->next=NULL;
		tail=x;
	}
	Point *pop()
	{
		if (empty()) return NULL;
		Point *pop_obj=front();
		Node *last=head;
		head=head->next;
		delete last;
		return pop_obj;
	}
	Point *front(){return head->next->data;}
};
class Stack
{
public:
	Node *top;
    Stack(){top=new Node();}
	bool empty(){return top->next==NULL;}
	void push(Point *member)
	{
		Node *x=new Node();
		x->data=member;
		x->next=top;
		top=x;
	}
	Point *pop()
	{
		if (empty()) return NULL;
		Point *pop_obj=get_top();
		Node *last=top;
		top=top->next;
		delete last;
		return pop_obj;
	}
	Point *get_top()
	{
		if (empty()) return NULL;
		return top->data;
	}
};

char str[28] = ".abegidfkclhj";

//  邻接表
Point *Find_Point(int point_num,Point *head){for (Point *x=head;x!=NULL;x=x->next_point) if (x->num==point_num) return x;return NULL;}
void Setclear(Point *head){for (Point *x=head;x!=NULL;x=x->next_point) x->vis=false;}
void Print_List(Node *first){for (Node *x=first;x!=NULL;x=x->next) printf(" %c",str[x->data->num]);printf("\n");}
void DFS_points(Point *p, Node **first, Node **last, Point *start)
{
    Node *x=new Node();
    if (p==start) *first=x;
    x->add(p,last);
    for (Point::Edge *e=p->last_edge;e!=NULL;e=e->next_edge) if (!e->terminal->vis)
    {
        e->terminal->vis=true;
        DFS_points(e->terminal, first, last, start);
    }
}
void DFS_recur(Point *head, Point *start)//邻接表-深搜-递归
{
    Setclear(head);
    Node *first=NULL, *last=NULL;
    start->vis=true;
    DFS_points(start, &first, &last, start);
    Print_List(first);
}
void DFS_non_recur(Point *head, Point *start)//邻接表-深搜-非递归
{
    Setclear(head);
    Stack sta;
    sta.push(start);
    start->vis=true;
    Node *x,*first,*last=NULL;
    while (!sta.empty())
    {
        x=new Node();
        if (sta.get_top()==start) first=x;
        x->add(sta.pop(),&last);
        for (Point::Edge *e=x->data->last_edge;e!=NULL;e=e->next_edge)
        if (e->terminal->vis==false)
        {
            e->terminal->vis=true;
            sta.push(e->terminal);
        }
    }
    Print_List(first);
}
void BFS(Point *head, Point *start)//邻接表-广搜
{
    Setclear(head);
    Queue qu;
    qu.push(start);
    Node *x,*first,*last=NULL;
    start->vis=true;
    while (!qu.empty())
    {
        x=new Node();
        if (qu.front()==start) first=x;
        x->add(qu.pop(),&last);
        for (Point::Edge *e=x->data->last_edge;e!=NULL;e=e->next_edge)
            if (e->terminal->vis==false) 
			{
                e->terminal->vis=true;
            	qu.push(e->terminal);
			}
    }
    Print_List(first);
}
void Print_Adjacency_List(Point *head)//输出邻接表
{
    for (Point *p=head;p!=NULL;p=p->next_point)
    {
        printf("%c :",str[p->num]);
        for (Point::Edge *e=p->last_edge;e!=NULL;e=e->next_edge)
            printf(" ( %c --> %c )",str[e->origin->num],str[e->terminal->num]);
        cout<<endl;
    }
}

//邻接矩阵
void Print_Adjacency_Matrix(int n, int ***matrix)//输出邻接矩阵
{
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
            if ((*matrix)[i][j]!=0) cout<<(*matrix)[i][j]<<' ';
            else cout<<'.'<<' ';
        printf("\n");
    }
}
void Shift_From_Matrix_To_List(Point **head, int n, int ***matrix)//邻接矩阵-->邻接表
{
    Point *x;
    for (int i=1;i<=n;i++)
	{
		x=new Point();
        x->add_point(i,head);
	}
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++) if ((*matrix)[i][j]>0)
        {
            Find_Point(i,*head)->add_edge((*matrix)[i][j],j,*head);
            Find_Point(j,*head)->add_edge((*matrix)[i][j],i,*head);
        }
    }
}
#define N 100
bool v[N+10];
int trave_order[N+10],trave_num;
void Print_List_Matrix(){for (int i=1;i<=trave_num;i++) printf(" %c",str[trave_order[i]]);printf("\n");}
void DFS_points_Matrix(int p, int n, int ***matrix)//邻接矩阵-深搜-递归
{
    trave_order[++trave_num]=p;
    for (int i=1;i<=n;i++) if ((*matrix)[p][i]&&!v[i])
    {
        v[i]=true;
        DFS_points_Matrix(i,n,matrix);
    }
}
void DFS_recur_Matrix(int start, int n, int ***matrix)//邻接矩阵-深搜-递归
{
    memset(v,0,sizeof(v));
    trave_num=0;
    v[start]=true;
    DFS_points_Matrix(start, n, matrix);
    Print_List_Matrix();
}
void DFS_non_recur_Matrix(int start, int n, int ***matrix)//邻接矩阵-深搜-非递归
{
    memset(v,0,sizeof(v));
    stack<int> sta;
    trave_num=0;
    sta.push(start);
    v[start]=true;
    while (!sta.empty())
    {
        trave_order[++trave_num]=sta.top();
        sta.pop();
        for (int i=1;i<=n;i++) if ((*matrix)[trave_order[trave_num]][i]&&!v[i])
        {
            v[i]=true;
            sta.push(i);
        }
    }
    Print_List_Matrix();
}
void BFS_Matrix(int start, int n, int ***matrix)//邻接矩阵-广搜
{
    memset(v,0,sizeof(v));
    queue<int> qu;
    trave_num=0;
    v[start]=true;
    qu.push(start);
    while (!qu.empty())
    {
        trave_order[++trave_num]=qu.front();
        qu.pop();
        for (int i=1;i<=n;i++) if ((*matrix)[trave_order[trave_num]][i]&&!v[i])
        {
            v[i]=true;
            qu.push(i);
        }
    }
    Print_List_Matrix();
}

int main()
{
    freopen("init.txt","r",stdin);
    //freopen("answer.txt","w",stdout);
	int n,m,start;  // n: points ; m: edges
    Point *head=NULL,*x;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		x=new Point();
        x->add_point(i,&head);
	}
    scanf("%d",&m);
    int **matrix=new int *[n+1];
    for (int i=0;i<=n;i++) matrix[i]=new int [n+1];// Build Adjacency Matrix
    for (int i=0;i<=n;i++) for (int j=0;j<=n;j++) matrix[i][j]=0;
    for (int i=1,l,r,v;i<=m;i++)
    {
        scanf("%d%d%d",&l,&r,&v);
        matrix[l][r]/*=matrix[r][l]*/=v;    // 邻接表-->邻接矩阵
        Find_Point(l,head)->add_edge(v,r,head);
        //Find_Point(r,head)->add_edge(v,l,head); //  无向图(若为有向图则删除)
    }
    scanf("%d",&start);//   搜索起始点(默认为1)
    cout<<endl;
    // Shift_From_Matrix_To_List(&head, n, &matrix);                        //邻接矩阵-->邻接表
    cout<<"Adjacency_Matrix :"<<endl;   Print_Adjacency_Matrix(n,&matrix);  //打印邻接矩阵
    cout<<"Adjacency_List :"  <<endl;   Print_Adjacency_List(head);         //打印邻接表
    cout<<endl<<"List :"<<endl<<endl;
    cout<<"DFS_recur     ";DFS_recur    (head, Find_Point(start, head));    //邻接表-深搜-递归  O(n+2×m)
    cout<<"DFS_non_recur ";DFS_non_recur(head, Find_Point(start, head));    //邻接表-深搜-非递归O(n+2×m)
    cout<<"BFS           ";BFS          (head, Find_Point(start, head));    //邻接表-广搜      O(n+2×m)
    cout<<endl<<"Matrix :"<<endl<<endl;
    cout<<"DFS_recur     ";DFS_recur_Matrix     (start, n, &matrix);        //邻接矩阵-深搜-递归   O(n²)
    cout<<"DFS_non_recur ";DFS_non_recur_Matrix (start, n, &matrix);        //邻接矩阵-深搜-非递归 O(n²)
    cout<<"BFS           ";BFS_Matrix           (start, n, &matrix);        //邻接矩阵-广搜       O(n²)
    fclose(stdin);
    fclose(stdout);
    return 0;
}
