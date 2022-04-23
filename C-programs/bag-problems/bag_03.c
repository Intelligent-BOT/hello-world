#include<stdio.h>

void bag_03_basic(); // bingo
void bag_03_binarily_divided_optimized(); // bingo
void bag_03_humdrum_queue_optimized(); // wrong

int main(){
    return 0;
}

int max(int a, int b){return (a>b)?a:b;}
/*
    Now every object has a finite number which is saved in array num[].
    We also ensure the state transfering equation first.
    dp[i][j] = max{dp[i-1][j-k*cost[i]]+k*value[i] | 0<=k<=num[i]}
    And we can evaluate the complexity of the algorithm in O(v*sum(num[i])).
*/
void bag_03_basic()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n+1], value[n+1], num[n+1];
    int dp[n+1][v+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", cost+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", value+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", num+i);
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            dp[i][j] = 0;
        }
    }
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            for ( int k = 0; k * cost[i] <= v && k <= num[i] ;k++ ) {
                if ( j >= k * cost[i]) {
                    dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-k*cost[i]] + k*value[i]));
                } else {
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                }
            }
        }
    }
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
    printf("%d", dp[n][v]);
    return;
}
/*
    Another feasible optimizing mothod is consider the idea of binary,
    we can divide every object's num binarily, just like quick-power.
    we divide the num to 1,2,4,...,2^(k-1),n-2^k+1 the k meet the
    condition that num[i]-2^k+1>0, then we get an algorithm with
    the space complexity O(v*sum(log(num[i]))).
*/
void bag_03_binarily_divided_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n+1], value[n+1], num[n+1], dp[v+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", cost+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", value+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", num+i);
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    for ( int i = 1; i <= n; i++ ) {
        int now = 1;
        if ( num[i] * cost[i] >= v ) for ( int j = cost[i]; j <= v; j++ ) dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
        else while ( 1 ) {
            if ( num[i] > now ) {
                num[i] -= now;
                for ( int j = v; j >= now * cost[i]; j-- ) dp[j] = max(dp[j], dp[j-now*cost[i]]+now*value[i]);
                now *= 2;
            } else {
                now = num[i];
                for ( int j = v; j >= now * cost[i]; j-- ) dp[j] = max(dp[j], dp[j-now*cost[i]]+now*value[i]);
                break;
            }
        }
    }
    printf("%d", dp[v]);
    return;
}
/*
    Futhermore, there is the very optimized algorithm that can compress the space 
    complexity to O(v*n) by using humdrum queue to dislodge the repetition.
    Now we can ensure the state tranferring equation.
    dp[i][j] = max(dp[i][j%cost[i]+k*cost[i]]-k*value[i]) + j/cost[i]*value[i];
*/
void bag_03_humdrum_queue_optimized()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n+1], value[n+1], num[n+1], queue[n+1], book[n+1], dp[v+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d", cost+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", value+i);
    for ( int i = 1; i <= n; i++ ) scanf("%d", num+i);
    for ( int i = 0; i <= n; i++ ) queue[i] = 0;
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    for ( int i = 1; i <= n; i++ ) {
        if ( cost[i] * num[i] >= v ) for ( int j = cost[i]; j <= v; j++ ) dp[j] = max(dp[j], dp[j-cost[i]]+value[i]);
        else for ( int j = 0; j < cost[i]; j++ ) {
            int head = 0, tail = 0;
            for ( int k = 0; k <= (v-j)/cost[i]; k++ ) {
                int temp = dp[j+k*cost[i]]-k*value[i];
                while ( head < tail && queue[tail-1] <= temp ) tail--;
                book[tail] = k;
                queue[tail++] = temp;
                if ( book[head] < k - num[i] ) head++;
                dp[j+k*cost[i]] = max(dp[j+k*cost[i]], queue[head]+k*value[i]);
            } 
        }
    }
    printf("%d", dp[v]);
    return;
}