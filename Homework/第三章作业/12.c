struct tree
{
	int data;
	int depth;
	struct tree *l,*r;
};
int maxdep(tree *root)
{
	int dep=0;
	tree *q[MAX];
	root->depth=1;
	for (head=1,tail=1;head<=tail;head++)
	{
		if (q[head]->depth>dep) dep=q[head]->depth;
		if (q[head]->l!=NULL) q[++tail]=q[head]->l,q[head]->l->depth=q[head]->depth+1;
		if (q[head]->r!=NULL) q[++tail]=q[head]->r,q[head]->r->depth=q[head]->depth+1;
	}
	return dep;
}
