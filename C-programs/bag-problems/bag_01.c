#include<stdio.h>

void bag_01_basic();// bingo
void bag_01_space_complexity_optimized();// bingo
void bag_01_must_full();// bingo
void bag_01_inferior_optimized();// bingo

int main(){
    bag_01_basic();
    return 0;
}

int max(int a, int b){return(a>b)?a:b;}
/*
    First of all, let's ensure the state transfer equation.
    dp[i][v] = max{dp[i-1][v], dp[i-1][v-cost[i]]+value[i]}
*/
void bag_01_basic()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n];
    int dp[n+1][v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 0; i < n; i++ ) scanf("%d", &value[i]);
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            dp[i][j] = 0;
        }
    }
    // Here where I have forgetted, now review it.
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            if ( j >= cost[i-1] ) {
            // Here where I have forgetted, now review it.
                dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-cost[i-1]] + value[i-1]));
            } else {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
                // Here where I have forgetted, now review it.
            }
        }
    }
    printf("%d", dp[n][v]);
    return;
}
/*
    Now we find a way to optimize the space complexity.
    We can get the max value of the biggest volume by reversely operate the dp.
*/
void bag_01_space_complexity_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n], dp[v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 0; i < n; i++ ) scanf("%d", &value[i]);
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    // Here where I have forgetted, now review it.
    for ( int i = 0; i < n; i++ ) {
        for ( int j = v; j > 0; j-- ) {
            if ( j >= cost[i] ) {
                dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
            }
        }
    }
    printf("%d", dp[v]);
    return;
}
/*
    On the other hand, when the question ask us to fill the bag conpulsively,
    we can change the mode of initialization, thus get the solution of the question.
*/
#define INF 999999
void bag_01_must_full()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n], dp[v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 0; i < n; i++ ) scanf("%d", &value[i]);
    dp[0] = 0;
    for ( int i = 1; i <= v; i++ ) dp[i] = -INF;
    // Here where I have forgetted, now review it.
    for ( int i = 0; i < n; i++ ) {
        for ( int j = v; j > 0; j-- ) {
            if ( j >= cost[i] ) {
                dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
            }
        }
    }
    printf("%d", dp[v]);
    return;
}
/*
    Actually, we can furthur optimize the program, as the inferior of the very bag j
    is v-sum{value[j..n]}, we can artifitially change the inferior of every volumn in
    the loop, and the advantage of this optimization only reflect when the v is big.
*/
void bag_01_inferior_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n], dp[v+1], sum[n];
    for ( int i = 0; i < n; i++ ) scanf("%d", &cost[i]);
    for ( int i = 0; i < n; i++ ) scanf("%d", &value[i]);
    // Here where I have forgetted, now review it.
    sum[n-1] = cost[n-1];
    for ( int i = n - 2; i > -1; i-- ) sum[i] = sum[i+1] + cost[i];
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    for ( int i = 0; i < n; i++ ) {
        int inferior = max(v-sum[i], cost[i]);
        for ( int j = v; j >= inferior; j-- ) {
            if ( j >= cost[i] ) {
                dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
            }
        }
    }
    printf("%d", dp[v]);
    return;
}