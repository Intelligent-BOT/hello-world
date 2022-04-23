#include<stdio.h>
int time[101]={0}, value[101]={0}, dp[1001]={0};
int max(int a, int b){return(a>b)?a:b;}
int main(){
    int t, m;
    scanf("%d %d", &t, &m);
    for(int i = 0; i < m; i++ ) scanf("%d %d", &time[i], &value[i]);
    for(int i = 0; i < m; i++ ) for(int j = t; j > 0; j-- ) if(time[i] <= j) dp[j] = max(dp[j], dp[j-time[i]]+value[i]);
    printf("%d", dp[t]);
    return 0;
}