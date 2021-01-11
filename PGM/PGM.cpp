/*** HDU 5995   ***/
#include <bits/stdc++.h>
#define MAXN 135
using namespace std;
const double eps = 1e-9;
struct Trie
{
    int next[MAXN][7],fail[MAXN],ed[MAXN];
    int root,L,cnt;
    int newnode()
    {
        for(int i=1;i<=6;i++)
            next[L][i]=-1;
        ed[L++]=0;
        return L-1;
    }
    void init()
    {
        L=0;
        root=newnode();
    }
    void Insert(int *buf,int len)          
    {
        int now=root;
        for(int i=0;i<len;i++)
        {
            int id=buf[i];
            if(next[now][id]==-1)
                next[now][id]=newnode();
            now=next[now][id];
        }
        ed[now]=1;
    }
    void build()
    {
        queue<int> q;
        fail[root]=root;
        for(int i=1;i<=6;i++)
        {
            if(next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                q.push(next[root][i]);
            }
        }
        while(!q.empty())
        {
            int now=q.front();
            q.pop();
            if(ed[fail[now]])
                ed[now]=1;
            for(int i=1;i<=6;i++)
            {
                if(next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    q.push(next[now][i]);
                }
            }
        }
    }
};
Trie AC;
int N;
struct Matrix
{
    double mat[MAXN][MAXN];
};
Matrix unit;
Matrix operator *(Matrix a,Matrix b)
{
    Matrix ans;
    memset(ans.mat,0,sizeof(ans.mat));
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            for(int k=1;k<=N;k++)
                ans.mat[i][j]=(ans.mat[i][j]+a.mat[i][k]*b.mat[k][j]);
    return ans;
}
int n,len;
int buf[MAXN];
Matrix tmp;
int main()
{
    int t;
    scanf("%d",&t);
    for(int i=0;i<MAXN;i++)unit.mat[i][i]=1;
    while(t--)
    {
        scanf("%d%d",&n,&len);
        AC.init();
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<len;j++)
                scanf("%d",&buf[j]);
            AC.Insert(buf,len);
        }
        AC.build();
        memset(tmp.mat,0,sizeof(tmp.mat));
        N=AC.L;
        for(int i=0;i<N;i++)
        {
            if(AC.ed[i])
            {
                tmp.mat[i+1][i+1]=1;
                continue;
            }
            for(int j=1;j<=6;j++)
            {
                int id=AC.next[i][j];
                tmp.mat[i+1][id+1]+=1.0/6;
            }
        }
        for(int i=1;i<=30;i++)
            tmp=tmp*tmp;
        int cnt=0;
        for(int i=0;i<N;i++)
        {
            if(AC.ed[i])
                cnt++,printf("%.6f%c",tmp.mat[1][i+1],cnt==n?'\n':' ');
        }
    }
    return 0;
}