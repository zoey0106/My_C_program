#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct 
{
    int id;
    int link1;
    int link2;
}anslist;
typedef struct 
{
    int id;
    double x;
    double y;
    
}list;
typedef struct 
{
    int id;
    int link;
    int link2;
    double numer;
    double deno_link1;
    double deno_link2; 
    int chosen;
}info;  

list data[100000];
info linker[100000];
anslist chosen_link[100000];//if we choose link, put it in
int track_chosen_link = 0;
int nodes[100000];//check node had been chosen before
double power,noise;
//算兩點間距離 預設:id = 按照順序給從0開始
double distant(int id,int id2){
    double x = data[id].x;
    double y = data[id].y;
    double x2 = data[id2].x;
    double y2 = data[id2].y;

    x = x - x2;//their distance
    y = y - y2;

    x = x*x;
    y = y*y;

    x = x + y ;//x= x^2+y^2 x=x's d y=y's d

    y = sqrt(x);

    return y;
}
//算p/dl^3
double sinr_numer(int id,int id2){
    double numer = distant(id,id2);
    numer = numer*numer*numer;
    numer = power/numer;

    return numer;
}
//算sinr值//1=ok 0=not ok
int sinr_counter(int id,int id2,int link){
    
    int compare = 1;
    if(track_chosen_link==0){
        if(linker[link].numer<linker[link].deno_link1){
            compare=0;
        }
    }
    else{
        //先處理新的
        for(int i=0;i<track_chosen_link;i++){
            linker[link].deno_link1 += sinr_numer(chosen_link[i].link1,id2);
      
        }

        if(linker[link].numer<linker[link].deno_link1){
            compare=0;
        }
        else{
            //處理舊的
            for(int i=0;i<track_chosen_link;i++){
                int linkerid=chosen_link[i].id;
                linker[linkerid].deno_link1 += sinr_numer(id,chosen_link[i].link2);
                
                if(linker[linkerid].numer<linker[linkerid].deno_link1){
                    compare=0;
                    for(int j=i;j>=0;j--){
                        linkerid=chosen_link[j].id;
                        linker[linkerid].deno_link1 -= sinr_numer(id,chosen_link[j].link2);
                        
                    }
                    break;
                }
            }
        }
    }
  
    return compare;
}



int main(){

    int node,link;
    
    scanf("%d %d %lf %lf",&node,&link,&power,&noise);

    int id,x,y;
    double x2,y2;
    //輸入節點資料
    for(int i=0;i<node;i++){
        scanf("%d %lf %lf",&id,&x2,&y2);
        data[i].id = id;
        data[i].x = x2;
        data[i].y = y2;
        
        nodes[i] = 0;
    }
    //輸入link資料
    for(int i=0;i<link;i++){
        scanf("%d %d %d",&id,&x,&y);
        linker[i].id = id;
        linker[i].link = x;//node A
        linker[i].link2 = y;//node B
        linker[i].numer = sinr_numer(x,y);;
        linker[i].deno_link1 = noise;
    }

    for(int i=0; i<link ;i++){

        if(nodes[linker[i].link]==0&&nodes[linker[i].link2]==0){
        
            int sinr = sinr_counter(linker[i].link,linker[i].link2,linker[i].id);
            if(sinr==1){
               
                    chosen_link[track_chosen_link].id = i;
                    chosen_link[track_chosen_link].link1 = linker[i].link;
                    chosen_link[track_chosen_link].link2 = linker[i].link2;
                    linker[i].chosen=1;//選擇了
                    nodes[linker[i].link]=1;
                    nodes[linker[i].link2]=1;
                    track_chosen_link++;
                
            }
         
        }
       
     
    }
    

    printf("%d\n",track_chosen_link);
    for(int i=0;i<track_chosen_link;i++){
  
        printf("%d %d %d\n",chosen_link[i].id,chosen_link[i].link1,chosen_link[i].link2);
        
    }
    

    system("PAUSE");
    return 0;  
}