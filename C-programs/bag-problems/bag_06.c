#include<stdio.h>

void bag_06_basic(); // bingo
void bag_06_space_optimized(); // bingo

int main(){
    return 0;
}

int max(int a, int b){return (a>b)?a:b;}
/*
    Now it is a new question, the object are divided into several groups,
    and each group has an inner conflict that we can only choose one object
    in each group, so we should record the max value of i group with j volume.
    So there is a new state tranferring equation.
    dp[i][j] = max{dp[i-1][j], dp[i-1][j-cost[i]]+value[i]}
*/
void bag_06_basic()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int group[n+1];
    int cost[n+1][v+1], value[n+1][v+1], dp[n+1][v+1];
    for ( int i = 0; i <= n; i++ ) group[i] = 0;
    for ( int i = 0; i <= n; i++ ) for ( int j = 0; j <= v; j++ ) cost[i][j] = value[i][j] = dp[i][j] = 0;
    for ( int i = 1; i <= n; i++ ) {
        scanf("%d", &group[i]);
        for ( int j = 0; j < group[i]; j++ ) {
            scanf("%d %d", &cost[i][j], &value[i][j]);
        }
    }
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = v; j >= 0; j-- ) {
            for ( int k = 0; k <= group[i]; k++ ) {
                if ( j >= cost[i][k] ) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j-cost[i][k]]+value[i][k]);
                }
            }
        }
    }
    printf("%d", dp[n][v]);
    return;
}
/*
    Or we can use array with one dimension by reversely ergodic the dp.
    for i in group
        for j = v to 0
            for k in i
                dp[j] = max{dp[j], dp[j-cost[k]]+value[k]}
*/
void bag_06_space_optimized()
{
    int n, v, g, group;
    scanf("%d %d", &n, &v, &g);
    int cost[n+1], value[n+1], dp[v+1];
    int book[n+1][n+1];
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    for ( int i = 0; i <= n; i++ ) for ( int j = 0; j <= n; j++ ) book[i][j] = 0;
    for ( int i = 1; i <= n; i++ ) {
        scanf("%d %d %d", cost+i, value+i, &group);
        book[group][++book[group][0]] = i;
        // Every 0 column of book memory the objects' numbers of each group.
    }
    for ( int i = 1; i <= g; i++ ) {
        for ( int j = v; j >= 0; j-- ) {
            for ( int k = 1; k <= book[i][0]; k++ ) {
                if ( j >= cost[book[i][k]] ) {
                    dp[j] = max(dp[j], dp[j-cost[book[i][k]]] + value[book[i][k]]);
                }
            }
        }
    }
    printf("%d", dp[v]);
    return;
}