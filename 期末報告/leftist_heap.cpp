#include <bits/stdc++.h>
#define MAXN 100001

using namespace std;
struct Lheap{
	int val,dis;
	Lheap *l,*r;
};
Lheap* tree[MAXN];
int fa[MAXN];
void init(Lheap* &t,int val){
	t=new Lheap;
	t->val=val;
	t->l=t->r=NULL;
	t->dis=0;
}
int findset(int x)
{
	int y,root,t;
	y=x;
	while(y!=fa[y])y=fa[y];
	root=y;
	y=x;
	while(fa[y]!=y){
		t=fa[y];
		fa[y]=root;
		y=t;
	}
	return root;
}
int Union(int x,int y){
	int fx=findset(x);
	int fy=findset(y);
	if(fx==fy)return -1;
	fa[fx]=fy;
	return fy;
}
int dis(Lheap *a){return (a)?(a->dis):(-1);}
Lheap* merge(Lheap* a,Lheap *b){
	if(a==NULL)return b;
	if(b==NULL)return a;
	if(b->val>a->val)swap(a,b);
	a->r=merge(a->r,b);
	if(dis(a->l)<dis(a->r))swap(a->l,a->r);
	a->dis=dis(a->r)+1;
	return a;
}
Lheap* delmax(Lheap *a){
	if(!a)return NULL;
	return merge(a->l,a->r);
}
int solve(int fx,int fy){
	Lheap *t1,*t2,*t3,*t4;
	init(t1,tree[fx]->val/2);
	t3=delmax(tree[fx]);
	t3=merge(t1,t3);
	init(t2,tree[fy]->val/2);
	t4=delmax(tree[fy]);
	t4=merge(t2,t4);
	fy=Union(fx,fy);
	tree[fy]=merge(t3,t4);
	return tree[fy]->val;
}
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			int atk;
			scanf("%d",&atk);
			fa[i]=i;
			init(tree[i],atk);
		}
		int que;
		scanf("%d",&que);
		while(que--){
			int x,y;
			scanf("%d%d",&x,&y);
			int fx=findset(x),fy=findset(y);
			if(fx!=fy)printf("%d\n",solve(fx,fy));
			else printf("-1\n");
		}
		for(int i=1;i<=n;i++)delete tree[i];
	}
	return 0;
}
