/*****************************************/
/*          About HDU 5992              */
/***************************************/
#include <bits/stdc++.h>
#define sq(x) (x)*(x)
using namespace std;
const int MAXN = 2e5+4;
typedef long long LL;
int idx;
inline int read()
{
    int x(0),f(1);
    char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct Point
{
    int x[2];
    int w,id;
    const bool operator <(const Point &tp)const
    {
        return x[idx]<tp.x[idx];
    }
};
Point pt[MAXN];
Point q;
typedef pair<LL,Point> PDN;
priority_queue<PDN> que;
int k=2,m=1;
struct KDTree
{
    Point p[MAXN<<2];
    int sz[MAXN<<2];
    void build(int l,int r,int rt,int dep)
    {
        if(l>r)return;
        sz[rt]=r-l;
        sz[rt<<1]=sz[rt<<1|1]=-1;
        idx=dep%2;
        int mid=(l+r)>>1;
        nth_element(pt+l,pt+mid,pt+r+1);
        p[rt]=pt[mid];
        build(l,mid-1,rt<<1,dep+1);
        build(mid+1,r,rt<<1|1,dep+1);
    }
    void query(int rt,int m,int dep,Point q)
    {
        if(sz[rt]==-1)return;
        int idx=dep%k,left=rt<<1,right=rt<<1|1;
        PDN tmp=PDN(0,p[rt]);
        for(int i=0;i<k;i++)tmp.first+=sq(1LL*(p[rt].x[i]-q.x[i]));
        if(q.x[idx]>p[rt].x[idx])swap(left,right);
        if(sz[left]!=-1)query(left,m,dep+1,q);
        bool flag=false;
        if((int)que.size()<m)
        {
            if(p[rt].w<=q.w)
                que.push(tmp);
            flag=true;
        }
        else
        {
            if(tmp.first<que.top().first&&p[rt].w<=q.w)que.pop(),que.push(tmp);
            if(tmp.first==que.top().first&&p[rt].w<=q.w&&p[rt].id<que.top().second.id)que.pop(),que.push(tmp);
            if(sq(q.x[idx]-p[rt].x[idx])<que.top().first)flag=true;  //查询另外部分矩形和圆形是否相交
        }
        if(sz[right]!=-1&&flag)query(right,m,dep+1,q);
    }
}T;
int n,ask;
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        n=read();ask=read();
        for(int i=0;i<n;i++)
        {
            pt[i].id=i;
            pt[i].x[0]=read();pt[i].x[1]=read();pt[i].w=read();
        }
        T.build(0,n-1,1,0);
        while(ask--)
        {   q.x[0]=read();q.x[1]=read();q.w=read();
            T.query(1,m,0,q);
            printf("%d %d %d\n",que.top().second.x[0],que.top().second.x[1],que.top().second.w);
            que.pop();
        }
    }
    return 0;
}