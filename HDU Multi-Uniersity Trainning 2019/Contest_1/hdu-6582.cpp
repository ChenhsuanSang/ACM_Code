//
// Created by Popery on 2019/7/23.
//

#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
#define ll long long
const ll inf=0x3f3f3f3f3f3f3f3f;
const int maxm=200500;
const int maxn=200050;
struct Edge
{
    ll next;ll to;ll w;ll fa;
}edge[maxm],edge2[maxm];
struct node
{
    int num;
    int dist;
    node(ll _num=0,ll _dist=0):num(_num),dist(_dist){}
    friend bool operator<(node a,node b)
    {
        return a.dist>b.dist;
    }
};
ll head[maxn],head2[maxn],cnt,cnt2;
ll dist[maxn],n,m,Start,End;
ll depth[maxn];
ll x[maxm],y[maxm],w[maxm];
void add(ll u,ll v,ll w)
{
    edge[cnt].next=head[u];edge[cnt].to=v;edge[cnt].w=w;head[u]=cnt++;
}
void add2(ll u,ll v,ll w)
{
    edge2[cnt2].next=head2[u];edge2[cnt2].to=v;edge2[cnt2].w=w;edge2[cnt2].fa=u;head2[u]=cnt2++;
    edge2[cnt2].next=head2[v];edge2[cnt2].to=u;edge2[cnt2].w=0;edge2[cnt2].fa=v;head2[v]=cnt2++;
}
void dij(int x)
{
    memset(dist,0x3f,sizeof(dist));
    priority_queue<node>q;q.push(node(x,0));dist[x]=0;
    while(!q.empty())
    {
        node u=q.top();q.pop();ll now=u.num;
        for(ll i=head[now];i!=-1;i=edge[i].next)
        {
            ll v=edge[i].to;
            if(dist[v]>dist[now]+edge[i].w)
            {
                dist[v]=dist[now]+edge[i].w;q.push(node(v,dist[v]));
            }
        }
    }
}
bool bfs()//分层;
{
    memset(depth,0,sizeof(depth));
    queue<int>q;
    q.push(Start);
    depth[Start]=1;
    while(!q.empty())
    {
        int temp=q.front();
        q.pop();
        for(ll i=head2[temp];i!=-1;i=edge2[i].next)
        {
            ll v=edge2[i].to;
            if(depth[v]||edge2[i].w<=0)
                continue;
            depth[v]=depth[temp]+1;
            q.push(v);
        }
    }
    return depth[End];//若为0表示没法到达也就是没有路径了；
}
int dfs(ll u,ll maxflow)
{
    if(u==End)
        return maxflow;
    int add=0;
    for(int i=head2[u];i!=-1&&add<maxflow;i=edge2[i].next)
    {
        ll v=edge2[i].to;
        if(depth[v]!=depth[u]+1)
            continue;
        if(edge2[i].w==0)
            continue;
        int tempflow=dfs(v,min(edge2[i].w,maxflow-add));
        edge2[i].w-=tempflow;
        edge2[i^1].w+=tempflow;
        add+=tempflow;
    }
    return add;
}
int dinic()
{
    ll ans=0;
    while(bfs())
    {
        ans+=dfs(Start,inf);
    }
    return ans;
}
int main()
{
    int tt;
    scanf("%d",&tt);
    while(tt--)
    {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head));memset(head2,-1,sizeof(head2));cnt=cnt2=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x[i],&y[i],&w[i]);add(x[i],y[i],w[i]);
        }
        Start = 1; End = n;
        dij(Start);
        for(int i=1;i<=m;i++)
            if(dist[y[i]]==dist[x[i]]+w[i])
                add2(x[i],y[i],w[i]);
        int ans=dinic();
        printf("%d\n",ans);
    }
}