#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char map[1001][1001];//記得調
int mark[1001][1001] = {0};
int min_step = 10001;
int A_xy[2];
int B_xy[2];
int n,m;
void DFS(int i,int j,int index){
    if(i == B_xy[0] && j == B_xy[1]){
        if(index < min_step){
            min_step = index;
        }
    }
    else{
        mark[i][j] = 1;
        index ++;
        if(i != 0){
            if(map[i-1][j] == 'B'){
                DFS(i-1,j,index);
            }
            else if(map[i-1][j] == '.' && mark[i-1][j] == 0){
                DFS(i-1,j,index);
            }
        }
        if(j != 0){
            if(map[i][j-1] == 'B'){
                DFS(i,j-1,index);
            }
            else if(map[i][j-1] == '.' && mark[i][j-1] == 0){
                DFS(i,j-1,index);
            }
        }
        if(i != n-1){
            if(map[i+1][j] == 'B'){
                DFS(i+1,j,index);
            }
            else if(map[i+1][j] == '.' && mark[i+1][j] == 0){
                DFS(i+1,j,index);
            }
        }
        if(j != m-1){
            if(map[i][j+1] == 'B'){
                DFS(i,j+1,index);
            }
            else if(map[i][j+1] == '.' && mark[i][j+1] == 0){
                DFS(i,j+1,index);
            }
        }
    }
}
int main(){
    scanf("%d %d",&n,&m); // n = height m = width

    for(int i=0;i<n;i++){
        scanf("%s",map[i]);
    }
    for(int i = 0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j] == 'A'){
                A_xy[0] = i;
                A_xy[1] = j;
            }
            if(map[i][j] == 'B'){
                B_xy[0] = i;
                B_xy[1] = j;
            }
        }
    }
    DFS(A_xy[0],A_xy[1],0);
    if(min_step != 10001){
        printf("YES\n");
        printf("%d\n",min_step);
    }
    else{
        printf("NO\n");
    }
    /*
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",int_map[i][j]);
        }
        printf("\n");
    }
    */
    system("pause");
    return 0;
}