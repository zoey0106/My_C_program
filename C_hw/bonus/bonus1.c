#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char map[1500][1500];//記得調
int int_map[1500][1500] ={0};
int n,m;
void DFS(int i,int j,int index){
    int_map[i][j] = index;
    if(i != 0){
        if(map[i-1][j] == '.' && int_map[i-1][j] == 0){
            DFS(i-1,j,index);
        }
    }
    if(j != 0){
        if(map[i][j-1] == '.' && int_map[i][j-1] == 0){
            DFS(i,j-1,index);
        }
    }
    if(i != n-1){
        if(map[i+1][j] == '.' && int_map[i+1][j] == 0){
            DFS(i+1,j,index);
        }
    }
    if(j != m-1){
        if(map[i][j+1] == '.' && int_map[i][j+1] == 0){
            DFS(i,j+1,index);
        }
    }

}
void f_room(){
    int room = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j] == '.' && int_map[i][j] == 0){
                room++;
                DFS(i,j,room);
            }
        }
    }
    printf("%d\n",room);
}
int main(){
    scanf("%d %d",&n,&m); // n = height m = width

    for(int i=0;i<n;i++){
        scanf("%s",map[i]);
    }
    f_room();
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