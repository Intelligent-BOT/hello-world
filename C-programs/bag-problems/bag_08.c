#include<stdio.h>
/*
    Congratulations!
    When we read here, it is proved that common bag questions can't defeat us,
    however, there are still several classic versions of bag questions, now
    let's discuss them one by one.
*/
void bag_08_solution_self_output(); // bingo
void bag_08_solution_self_upper_output(); //bingo
void bag_08_solution_totality(); // bingo
void bag_08_optimal_solutions(); // bingo
void bag_08_kth_optimal_solution(); // bingo

int main(){
    return 0;
}
int max(int a, int b){return (a>b)?a:b;}
/*
    When we are asked to output the optimal solution itself, we should record
    the route and find the very route reversely.
    Now we ensure the pseudo code.
    for i = n to 1
        if ( dp[i][v] == dp[i-1][v-cost[i]] + value[i] ) print i
*/
void bag_08_solution_self_output()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n];
    int dp[n+1][v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", cost+i);
    for ( int i = 0; i < n; i++ ) scanf("%d", value+i);
    for ( int i = 0; i <= n; i++ ) for ( int j = 0; j <= v; j++ ) dp[i][j] = 0;
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            if ( j >= cost[i-1] ) {
                dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-cost[i-1]]+value[i-1]));
            } else {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
        }
    }
    for ( int i = n; i > 0; i-- ) {
        if ( dp[i][v] == dp[i-1][v-cost[i-1]]+value[i-1] ) printf("%d ", i);
    }
    return;
}
/*
    When we are asked to output the lexicographic solution, we just need to
    save the solution into an array and reversely output it. 
*/
void bag_08_solution_self_upper_output()
{
    int n, v, cnt=0;
    scanf("%d %d", &n, &v);
    int cost[n], value[n], path[n];
    int dp[n+1][v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", cost+i);
    for ( int i = 0; i < n; i++ ) scanf("%d", value+i);
    for ( int i = 0; i < n; i++ ) path[i] = 0;
    for ( int i = 0; i <= n; i++ ) for ( int j = 0; j <= v; j++ ) dp[i][j] = 0;
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            if ( j >= cost[i-1] ) {
                dp[i][j] = max(dp[i][j], max(dp[i-1][j], dp[i-1][j-cost[i-1]]+value[i-1]));
            } else {
                dp[i][j] = max(dp[i][j], dp[i-1][j]);
            }
        }
    }
    for ( int i = n; i > 0; i-- ) if ( dp[i][v] == dp[i-1][v-cost[i-1]]+value[i-1] ) path[cnt++] = i;
    for ( int i = cnt - 1; i > -1; i-- ) printf("%d ", path[i]);
    return;
}
/*
    When we are asked to output the totality of solutions, we just need to memory
    the number of solutions when ergodic the dp.
    We should add the following state tranferring equation.
    dp[i][j] = dp[i-1][j] + dp[i][j-cost[i]]
*/
void bag_08_solution_totality()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], dp[v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", cost+i);
    for ( int i = 0; i <= v; i++ ) dp[i] = 0;
    dp[0] = 1;
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = v; j >= cost[i-1]; j-- ) {
            for ( int k = 1; k * cost[i-1] <= j; k++ ) {
                dp[j] += dp[j-k*cost[i-1]];
            }
        }
    }
    printf("%d", dp[v]);
    return;
}
/*
    When we are asked to output the totality number of the optimal solutions,
    we need to use another array to memory the number of optimal solutions.
    We can ensure the pseudo as follows.
    for i = 1..n
        for j = 0..v
            dp[i][j] = max{dp[i-1][j], dp[i-1][j-cost[i]]+value[i]}
            number[i][j] = 0
            if ( dp[i][j] == dp[i-1][j] ) number[i][j] += number[i-1][j]
            if ( dp[i][j] == dp[i-1][j-cost[i]]+value[i] ) number[i][j] += number[i-1][j-cost[i]]
*/
void bag_08_optimal_solutions()
{
    int n, v;
    scanf("%d %d", &n, &v);
    int cost[n], value[n];
    int dp[n+1][v+1], op[n+1][v+1];
    for ( int i = 0; i < n; i++ ) scanf("%d", cost+i);
    for ( int i = 0; i < n; i++ ) scanf("%d", value+i);
    for ( int i = 0; i <= n; i++ ) {
        for ( int j = 0; j <= v; j++ ) {
            dp[i][j] = 0;
            op[i][j] = 1;
        }
    }
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = 1; j <= v; j++ ) {
            dp[i][j] = dp[i-1][j];
            op[i][j] = op[i-1][j];
            if ( j >= cost[i-1] ) {
                if ( dp[i][j] < dp[i-1][j-cost[i-1]]+value[i-1] ) {
                    dp[i][j] = dp[i-1][j-cost[i-1]]+value[i-1];
                    op[i][j] = op[i-1][j-cost[i-1]];
                } else if ( dp[i][j] == dp[i-1][j-cost[i-1]]+value[i-1] ) {
                    op[i][j] = op[i-1][j]+op[i-1][j-cost[i-1]];
                }
            }
        }
    }
    printf("%d", op[n][v]);
    return;
}
/*
    Don't count your chickens before they are hatched!
    When we are asked to output the sub-optimal solution or kth-optimal solution,
    we should add one dimension to the dp to discord the kth-optimail solution
*/
#define INF 999999
void bag_08_kth_optimal_solution()
{
    int k, v, n, ans = 0;
    scanf("%d %d %d", &k, &v, &n);
    int cost[n+1], value[n+1], temp[k+1];
    int dp[v+1][k+1];
    for ( int i = 1; i <= n; i++ ) scanf("%d %d", cost+i, value+i);
    for ( int i = 0; i <= v; i++ ) for ( int j = 0; j <= k; j++ ) dp[i][j] = -INF;
    dp[0][1] = 0;
    for ( int i = 1; i <= n; i++ ) {
        for ( int j = v; j >= cost[i]; j-- ) {
            for ( int l = 1, p1 = 1, p2 = 1; l <= k; l++ ) temp[l] = ( dp[j][p1] > dp[j-cost[i]][p2] + value[i] ) ? ( dp[j][p1++] ) : ( dp[j-cost[i]][p2++] + value[i] );
            for ( int l = 1; l <= k; l++ ) dp[j][l] = temp[l];
        }
    }
    for ( int i = 1; i <= k; i++ ) ans += dp[v][i];
    printf("%d", ans);
    return;
}