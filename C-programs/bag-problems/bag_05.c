#include<stdio.h>

void bag_05_space_optimized(); // bingo

int main(){
    return 0;
}

int max(int a, int b){return (a>b)?a:b;}
/*
    Now there are two different fees in one object, like the volume and the weight,
    so we should add one dimension to get the max value.
    Anyway, we should ensure the state transfering equation first.
    dp[i][j][k] = max{dp[i-1][j][k], dp[i-1][j-volume[i]][k-weight[i]]+value[i]}
    Also, we can only use array with two dimensions by reversely ergodic it.
    dp[j][k] = max{dp[j][k], dp[j-volume[i]][k-weight[i]]+value[i]}
*/
void bag_05_space_optimized()
{
    int n, v, w;
    scanf("%d %d %d", &n, &v, &w);
    int volume[n+1], weight[n+1], value[n+1];
    int dp[v+1][w+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", volume+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", weight+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", value+i);
    for ( int i = 0; i <= v; i++ ) for ( int j = 0; j <= w; j++ ) dp[i][j] = 0;
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = v; j >= volume[i]; j-- ) {
            for ( int k = w; k >= weight[i]; k-- ) {
                dp[j][k] = max(dp[j][k], dp[j-volume[i]][k-weight[i]]+value[i]);
            }
        }
    }
    printf("%d", dp[v][w]);
    return;
}