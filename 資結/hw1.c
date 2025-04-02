#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int totalcost=0;
typedef struct node_data
{
    int id;
    int weight;
    int linkers;//sum of linkers
    int parent_link[5000];//裝link的id//-1代表已刪要跳過不要看
    int check_deleted;//1=deleted
    int parent_check;
    int parent_root;//真正的直系
    int child;
}node_list;
typedef struct node_count
{
    int sum;
    int times;
}node_c;

//node_list list[node+1];
node_list list[5000];//global
node_c data[5000];
int count=0;
int link[3][5000000];
int link_check[1000000];



void totalcost_counter(int node,int packet_size){

    for(int i=0;i<node;i++){
here:
        if(list[i].child==0){
            list[i].child=-1;
            data[list[i].parent_root].sum += list[i].weight+data[i].sum;
            data[list[i].parent_root].times += ((list[i].weight+data[i].sum)/packet_size + data[i].times);
            if((list[i].weight+data[i].sum)%packet_size!=0){
                data[list[i].parent_root].times++;
            }
            list[list[i].parent_root].child--;

            if(list[i].parent_root==0){
                if(list[list[i].parent_root].child==0){
                    break;
                }
            }
            //若減完後的root有child變成0
            if(list[list[i].parent_root].child==0){
                list[list[i].parent_root].child=-1;
                //若指向0了
                if(list[list[i].parent_root].parent_root==0){
                    int next2=list[i].parent_root;
                    list[0].child--;
                    data[0].sum += list[next2].weight+data[next2].sum;
                    data[0].times += ((list[next2].weight+data[next2].sum)/packet_size + data[next2].times);
                        if((list[next2].weight+data[next2].sum)%packet_size!=0){
                            data[0].times++;
                        }
                    if(list[0].child==0){
                        break;//表示算完了
                    }
                }
                else{
                    int next=list[list[i].parent_root].parent_root;
                    int original=list[i].parent_root;
                    list[next].child--;
                    data[next].sum += list[original].weight+data[original].sum;
                    data[next].times += ((list[original].weight+data[original].sum)/packet_size + data[original].times);
                        if((list[original].weight+data[original].sum)%packet_size!=0){
                            data[next].times++;
                        }
                    if(list[next].child==0){
                        i=next;
                        goto here;
                    }

                }

            }

        }
    }
}
//return 0=ok 1=flase
int check_cycle(int node,int target){
    int next = list[target].parent_root;
    int update = target ;
    int return_num = -1 ;
    while(1){
        if(next==target&&next!=0){
            return_num=1;
            break;
        }
        else if(next == 0){
            return_num=0;
            break;
        }
        update = next;
        next=list[update].parent_root;
    }

    return return_num;
}
//這邊更改值就直接更改了要小心
int find_solution(int node,int packet_size,int links){

        for(int i=1;i<node;i++){
            for(int j=0;j<links;j++){
                if(link_check[j]==0&&link[1][j]==i){
                    link_check[j]=1;
                    list[i].parent_check=1;
                    list[i].parent_root=link[2][j];
                    list[list[i].parent_root].child++;
                    break;
                }
                else if(link_check[j]==0&&link[2][j]==i){
                    link_check[j]=1;
                    list[i].parent_check=1;
                    list[i].parent_root=link[1][j];
                    list[list[i].parent_root].child++;
                    break;
                }
            }
        }
        /*
        //
        totalcost_counter(node,packet_size);
        //
        int total_temp=data[0].times;
        */   
        //change here
        //原本小孩也要還原
        
        int kids[50000];
        for(int i=0;i<node;i++){
            kids[i]=list[i].child;
        }//記得原本的小孩是多少

        totalcost_counter(node,packet_size);
        for(int i=0;i<node;i++){
            list[i].child=kids[i];
        }

        int total_temp=data[0].times;
        for(int i=links/2;i<links;i++){
                for(int i=0;i<node;i++){
                    kids[i]=list[i].child;
                 }
                if(link_check[i]==0){
                    int link1=link[1][i];
                    int link2=link[2][i];
                    //存原本的資料
                    int keep_original_link1=list[link1].parent_root;//存link1原本的root

                    //改變root//從link1開始//先做一邊
                    list[list[link1].parent_root].child--;
                    list[link1].parent_root=link2;
                    list[link2].child++;

                    int check = check_cycle(node,link1);//0表示可以換

                    if(check==0){
                        for(int i=0;i<node;i++){
                            data[i].sum=0;
                            data[i].times=0;
                        }
                      
                        totalcost_counter(node,packet_size);
                        int compare_total=data[0].times;
                        if(total_temp<=compare_total){
                            list[link1].parent_root=keep_original_link1;
                            for(int i=0;i<node;i++){
                            list[i].child=kids[i];
                            }
                        }
                        else{
                            for(int i=0;i<node;i++){
                            list[i].child=kids[i];
                            }
                            list[list[link1].parent_root].child--;
                            list[link2].child++;
                            total_temp=compare_total;
                            link_check[i]=1;
                        }
                    }
                    else{
                        link_check[i]=1;
                        list[link1].parent_root=keep_original_link1;
                        list[list[link1].parent_root].child++;
                        list[link2].child--;
                    }
                }
        }
    //記得測試要拿掉下面的"//"
    
    return total_temp;

}


int main(){

    int node;
    int links;
    int packet_size;
    int link_id;

    scanf("%d %d %d",&node,&links,&packet_size);



    //node讀取
    for(int i=0;i<node;i++){
        scanf("%d %d",&list[i].id,&list[i].weight);
        list[i].linkers=0;
        list[i].check_deleted=0;
        list[i].parent_check=0;
        list[i].child=0;
        data[i].times=0;
        data[i].sum=0;
        //吞進去了
    }

    int link1,link2;
    //linker讀取

    list[0].parent_check=1;
    list[0].parent_root=0;//自己的root
    list[0].linkers++;//only會有一個自己


    for(int i=0;i<links;i++){
        scanf("%d %d %d",&link_id,&link1,&link2);
        link[1][i]=link1;
        link[2][i]=link2;
        link_check[i]=0;
    }

    
    int totals=find_solution(node,packet_size,links);//ver2
    
    int check2=-1;
    for(int i=0;i<node;i++){
        
        check2=check_cycle(node,i);
        if(check2==1){
            break;
        }
    }
  

    if(check2==0){  
        
    for(int i=0;i<node;i++){
        list[i].child=0;
        data[i].sum=0;
        data[i].times=0;
    }
    for(int i=1;i<node;i++){
        int child2=list[i].parent_root;
        list[child2].child++;
    }
    totalcost_counter(node,packet_size);
    printf("%d %d\n",node,data[0].times);
    for(int i=0;i<node;i++){
        printf("%d %d\n",list[i].id,list[i].parent_root);
    }
    }

    system("PAUSE");
    return 0;
}
