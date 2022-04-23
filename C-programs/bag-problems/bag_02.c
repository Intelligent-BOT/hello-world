#include<stdio.h>

void bag_02_basic(); // bingo
void bag_02_simple_optimized(); // bingo
void bag_02_space_optimized(); // bingo

int main(){
    return 0;
}

int max(int a, int b){return(a>b)?a:b;}
/*
    Now every object has an infinite number to use.
    We also ensure the state transfer equation first.
    dp[i][v] = max{dp[i-1][v], dp[i-1][v-k*cost[i]]+k*value[i]|0<=k*cost[i]<=v}
*/
void bag_02_basic()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n+1], value[n+1];
    int dp[n+1][v+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 1; i <= n; i++ ) scanf("%d", &value[i]);
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            dp[i][j] = 0;
        }
    }
    // Here where I have forgetted, now review it.
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            for ( int k = 0; k * cost[i] <= v; k++ ) {
                if ( j >= k * cost[i] ){
                    dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-k*cost[i]]+k*value[i]));
                } else {
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                    // Here where I have forgetted, now review it.
                }
            }
        }
    }
    // for ( int i = 0; i <= n; i++ ) {
    //     for ( int j = 0; j <= v; j++ ) {
    //         printf("%d ", dp[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d", dp[n][v]);
    return;
}
/*
    Now we consider two simple optimization.
    If cost[i]<=cost[j] && value[i]>=value[j], we can eliminate the j object immediately.
    If cost[i]>v, we can eliminate the i object immediately.
    However, this two way are too simple to solve the question.
*/
void bag_02_simple_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n+1], value[n+1];
    int dp[n+1][v+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 1; i <= n; i++ ) scanf("%d", &value[i]);
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            dp[i][j] = 0;
        }
    }
    for ( int i = 0; i < n - 1; i++ ) {
        if ( cost[i] > v ) value[i] = 0;
        for ( int j = i + 1; j < n; j++ ) {
            if ( cost[i] >= cost[j] && value[i] <= value[j] ) {
                value[i] = 0;
            }
        }
    }
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            for ( int k = 0; k * cost[i] <= j; k++ ) {
                 if ( j >= k * cost[i] ){
                    dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-k*cost[i]]+k*value[i]));
                } else {
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                }
                // Here where I have forgetted, now review it.
            }
        }
    }
    printf("%d", dp[n][v]);
    return;
}
/*
    Obviously, we can optimize the algorithm by compress the dp array to one dimension.
    Think of it, we can just adjust the order of loop to achieve the goal, because it 
    means that we can choose any number of the object, which accord with the requirement.
*/
void bag_02_space_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n], dp[v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 0; i < n; i++ ) scanf("%d", &value[i]);
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            if ( j >= cost[i] ) {
                dp[j] = max(dp[j], dp[j-cost[i]]+value[i]);
            }
        }
    }
    printf("%d", dp[v]);
    return;
}