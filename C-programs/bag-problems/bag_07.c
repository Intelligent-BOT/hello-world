#include<stdio.h>
#include<string.h>

void bag_07_tree(); // bingo

int main(){
    return 0;
}
/*
    More fussily, when the objects have dependency, we shouldn't only consider
    one host object with its subsidiaries, but pack them to an object group,
    then do a bag_01 on every group to get the volumn = 0 to v-cost[i] 's value.
    Then the host object and it's subsidiaries can be considered as v-cost[i]+1
    objects, in which the object with cost[i]+k volumn has dp[k]+value[i] value,
    the it is changed to bag_06.
*/
/*
    Furthurmore, the dependency can be given by so called "forest" in graph theory,
    which means that every subsidiaries should be considered as a subtree, the it
    is upgraded to a arborescence dynamic programming.
*/
int head[110]={0}, edge[110]={0}, nextedge[110]={0}, dp[110][110]={0};
int cost[110]={0}, value[110]={0};
void add(int * index, int node, int end)
{
    edge[*index] = end;
    nextedge[*index] = head[node];
    head[node] = (*index)++;
    return;
}
void dfs(int root, int v)
{
    for ( int i = cost[root]; i <= v; i++ ) dp[root][i] = value[root];
    for ( int i = head[root]; i != -1; i = nextedge[i] ) {
        int temp = edge[i];
        dfs(temp, v);
        for ( int j = v; j > cost[root]; j-- ) {
            for ( int k = 0; k <= j-cost[root]; k++ ) {
                if ( dp[root][j] < dp[root][j-k]+dp[temp][k] ) {
                    dp[root][j] = dp[root][j-k]+dp[temp][k];
                }
            }
        }
    }
    return;
}
void bag_07_tree()
{
    int n, v, root, node, index = 0;
    scanf("%d %d", &n, &v);
    for ( int i = 0; i < 110; i++ ) head[i] = -1;
    for ( int i = 1; i <= n; i++ ) {
        scanf("%d %d %d", cost+i, value+i, &node);
        if ( node == -1 ) root = i;
        else add(&index, node, i);
    }
    dfs(root, v);
    printf("%d", dp[root][v]);
    return;
}