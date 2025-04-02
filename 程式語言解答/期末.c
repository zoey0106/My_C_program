#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Record {
    int id;
    char name[21];
    int studentid;
    char classroom[5];
    char email[41];
    char phone[16];
    int deleteorselect;//刪除的話改成-1選擇的話改成1
} record;

typedef struct correctRecord{
    int id;
    char name[21];
    int studentid;
    char classroom[5];
    char email[41];
    char phone[16];
    int deleteorselect;
} rightrecord;
int getNextToken(char *command, int index, char *token);
int finddatabase(char *command,int index,char *buffer,record *database,int num1,int databasecorrect[],int orandnone);
void deletedatabase(char *command,int index,char *buffer,record *database,int num1);
int selectdatabase(char *command,int index,char *buffer,record *database,int num1,int array[]);
int fromtoptolow(int order,record *database,rightrecord *undatabase,int num1,int array[]);
int fromlowtotop(int order,record *database,rightrecord *undatabase,int num1,int array[]);
void printanddelete(record *database,int num1,int array[],int order,rightrecord *undatabase);
char   *deleteChar  (char *str,char c)
{
    char *head = NULL;
    char *p = NULL;
    if(str ==NULL){
        return NULL;
    }
    head = p = str;
    while(*p++){
        if(*p != c){
            *str++ = *p;
        }
    }
    *str = '\0';
    return head;
}
int main(){

    int num1,num2;//num1是幾個資料num2是幾個指令
    scanf("%d %d",&num1,&num2);
    record database[num1];
    rightrecord undatabase[num1];
    //改成0了
    memset(&database[0], 0, sizeof(database));
    memset(&undatabase[0],0,sizeof(database));
    int id;
    char name[21];
    int studentid;
    char classroom[5];
    char email[41];
    char phone[16];
    for (int i=0; i < num1; i++) {
        scanf("%d %s %d %s %s %s", &id, name, &studentid,classroom,email,phone);
        database[i].id=id;
        strcpy(database[i].name, name);
        database[i].studentid=studentid;
        strcpy(database[i].classroom, classroom);
        strcpy(database[i].email, email);
        strcpy(database[i].phone, phone);
    }
    //datacorrect
    //以下為定義的數字代表的意義
    //ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;

    //指令的次數
    while(num2>0){
    char command[1000]={0};//指令
    char buffer[1000]={0};//各字串分割內容
    scanf("%[^;]",command);//把指令輸入
    int index;
    index = 0;//從0開始找
    while(index>=0){
        index=getNextToken(command,index,buffer);
        int order=-1;
        int array[7]={0};//出現順序
        if(buffer[0]==10){
            int g=1;
            for(int i=0;i<6;i++){
                int mid=buffer[g];
                buffer[i]=mid;
                g++;
            }
            buffer[6]=0;
        }
        if(strcmp(buffer,"SELECT")==0){
            order=selectdatabase(command,index,buffer,database,num1,array);
             //印出
        if(order==0){
            printanddelete(database,num1,array,0,undatabase);
            break;
        }
        else if(order%10==0&&order>0){
            printanddelete(database,num1,array,order,undatabase);
            break;
        }
        else if(order%10!=0&&order>0){
            printanddelete(database,num1,array,order,undatabase);
            break;
        }
        }
        else if(strcmp(buffer,"DELETE")==0){
            deletedatabase(command,index,buffer,database,num1);
            printanddelete(database,num1,array,-1,undatabase);
            break;
        }
        //有ORDER的話再排//select的話直接印
        //把database裡面deleteorselect值為 -1 or 1 的數字複製到undatabase裡
        //刪除
    }
            num2--;
    }
    return 0;
}

int getNextToken(char *command, int index, char *token) {
    int start = index;
    int end = index;
    int v=0;
    while(1){
    if (command[end] == ' '){
        int i=start;
        int end2=end;
        if(command[end-1]==','){
            end2--;
        }
        while(i<end2){
            *(token+v)=command[i];
            v++;
            i++;
        }
        *(token+v)=0;
        return end+1;
    }
    else if(command[end]==0){
        int i=start;
        while(i<end){
            *(token+v)=command[i];
            v++;
            i++;
        }
        *(token+v)=0;
        return -1;//是負的話還有最後一個字元
    }
    else{
        end++;
    }
    }
}
//ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
//回傳一個值代表它有幾個正確的比對資料
//orandnone==0 代表不需重複比對 ==1代表要找這個條件同時deleteorselect=-1or1的
int finddatabase(char *command,int index,char *buffer,record *database,int num1,int databasecorrect[],int orandnone){
    index=getNextToken(command,index,buffer);
    int whichsubject=0;
    if(strcmp(buffer,"ID")==0){
        whichsubject=1;
    }
    else if(strcmp(buffer,"StudentID")==0){
        whichsubject=2;
    }
    else if(strcmp(buffer,"Class")==0){
        whichsubject=3;
    }
    else if(strcmp(buffer,"Email")==0){
        whichsubject=4;
    }
    else if(strcmp(buffer,"Phone")==0){
        whichsubject=5;
    }
    else if(strcmp(buffer,"Name")==0){
        whichsubject=6;
    }
    index=getNextToken(command,index,buffer);
    int v=0;
    if(orandnone==0){
    if(strlen(buffer)==2){
           if(strcmp(buffer,">=")==0){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id >= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                 }
              //int studentid
            }
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid >= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone >= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }
        }
        else if(strcmp(buffer,"<=")==0){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id <= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid <= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone <= number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }
        }
    }
    else if(strlen(buffer)==1){
        if(buffer[0]=='>'){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id > number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid > number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone > number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }

        }
        else if(buffer[0]=='<'){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id < number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid < number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone < number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }
        }
        else if(buffer[0]=='='){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id == number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid == number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone == number){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                }
            }//class
            else if(whichsubject==3){
                for(int i=0;i<num1;i++){
                    if(strcmp(buffer,database[i].classroom)==0){
                        databasecorrect[v]=i;
                        v++;
                    }
                }
            }//6//char name
            else if(whichsubject==6){
                for(int i=0;i<num1;i++){
                    if(strcmp(buffer,database[i].name)==0){
                        databasecorrect[v]=i;
                        v++;
                    }
                }
            }
        }
    }
    else if(strlen(buffer)==4){
            //4char email
            index=getNextToken(command,index,buffer);
            if(whichsubject==4){
                        char c = '%';
                        char b='"';
                        deleteChar(buffer,b);
                        deleteChar(buffer,c);
                    for(int i=0;i<num1;i++){
                    if(strstr(database[i].email,buffer)){
                        databasecorrect[v]=i;
                        v++;
                    }
                }
            }
    }
    }
    else if(orandnone==1){
        if(strlen(buffer)==2){
           if(strcmp(buffer,">=")==0){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id >= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].id >= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
              //int studentid
            }
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid >= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].studentid >= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone >= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].phone >= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }
        }
        else if(strcmp(buffer,"<=")==0){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id <= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].id <= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid <= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].studentid <= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone <= number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].phone <= number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }
        }
    }
    else if(strlen(buffer)==1){
        if(buffer[0]=='>'){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id > number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].id > number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid > number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].studentid > number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone > number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].phone > number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }

        }
        else if(buffer[0]=='<'){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id < number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].id < number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid < number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].studentid < number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone < number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].phone < number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }
        }
        else if(buffer[0]=='='){
            index=getNextToken(command,index,buffer);
            //int id
            if(whichsubject==1){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].id == number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].id == number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int studentid
            else if(whichsubject==2){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].studentid == number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].studentid == number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//int phone
            else if(whichsubject==5){
                int number;
                number = strtoul(buffer,NULL,0);//把字串變成數字
                for(int i=0;i<num1;i++){
                    if(database[i].phone == number&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;//存入ID
                        v++;
                    }
                    else if(database[i].phone == number&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                 }
            }//class
            else if(whichsubject==3){
                for(int i=0;i<num1;i++){
                    if(strcmp(buffer,database[i].classroom)==0&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else if(strcmp(buffer,database[i].classroom)==0&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                }
            }//6//char name
            else if(whichsubject==6){
                for(int i=0;i<num1;i++){
                    if(strcmp(buffer,database[i].name)==0&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else if(strcmp(buffer,database[i].name)==0&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                }
            }
        }
    }
    else if(strlen(buffer)==4){
            //4char email
            index=getNextToken(command,index,buffer);
            if(whichsubject==4){
                for(int i=0;i<num1;i++){
                        //找尋裡面是否有這個字串
                        //刪除"%"
                        char c = '%';
                        char b='"';
                        deleteChar(buffer,b);
                        deleteChar(buffer,c);
                    if(strstr(database[i].email,buffer)!=NULL&&database[i].deleteorselect==-1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else if(strstr(database[i].email,buffer)!=NULL&&database[i].deleteorselect==1){
                        databasecorrect[v]=i;
                        v++;
                    }
                    else{
                        database[i].deleteorselect=0;
                    }
                }
            }
    }
    }
    if(index==-1){
        return -v;
    }
    else{
    return v;
    }
}
//找到真正要刪掉的就把database的id設成-1 1=or 2=and 0=none
//deleselenone 要的deleteorselect=1or-1(刪除和印出) 不要的ID直接設為0  1=delete 2=select
void finaldatabase(char *command,int index,char *buffer,record *database,int num1,int databasecorrect[],int howmanycorrect,int orand,int deleselenone){
    //delete
    if(deleselenone==1){
        if(orand==0){
            for(int i=0;i<howmanycorrect;i++){
                database[databasecorrect[i]].deleteorselect=-1;
                //把database的ID改成-1就算刪掉
            }
        }
        else if(orand==1){
            for(int i=0;i<howmanycorrect;i++){
                database[databasecorrect[i]].deleteorselect=-1;
                //把database的參數改成-1就算刪掉
            }
            int num=finddatabase(command,&index,buffer,database,num1,databasecorrect,0);
            for(int i=0;i<num;i++){
                database[databasecorrect[i]].deleteorselect=-1;
                //把database的參數改成-1就算刪掉
            }
        }//明天寫&就應該可以把大多的東西敲完了，只差排序，有ORDER就排沒ORDER就按照順序一個個印
        else if(orand==2){
                //最後加一個0 1:表示不需多重比對none/or 需兩條件and
                for(int i=0;i<howmanycorrect;i++){
                database[databasecorrect[i]].deleteorselect=-1;
                //把database的參數改成-1就算刪掉
                }
                howmanycorrect=finddatabase(command,index,buffer,database,num1,databasecorrect,1);
                for(int i=0;i<howmanycorrect;i++){
                database[databasecorrect[i]].deleteorselect=-1;
                //把database的參數改成-1就算刪掉
                }
        }
    }//select後把它存在undatabase再來判斷是否有orderby
    else if(deleselenone==2){
        if(orand==0){
            for(int i=0;i<howmanycorrect;i++){
                if(database[databasecorrect[i]].deleteorselect!=-1){
                database[databasecorrect[i]].deleteorselect=1;
                //把database的ID改成1就算留下
                }
            }
        }
        else if(orand==1){
            for(int i=0;i<howmanycorrect;i++){
                if(database[databasecorrect[i]].deleteorselect!=-1){
                database[databasecorrect[i]].deleteorselect=1;
                //把database的參數改成1就算留下
                }
            }
            int num=finddatabase(command,&index,buffer,database,num1,databasecorrect,0);
            for(int i=0;i<num;i++){
                if(database[databasecorrect[i]].deleteorselect!=-1){
                database[databasecorrect[i]].deleteorselect=1;
                //把database的參數改成1就算留下
                }
            }
        }
        else if(orand==2){
            //最後加一個0 1:表示不需多重比對none/or 需兩條件and
                for(int i=0;i<howmanycorrect;i++){
                if(database[databasecorrect[i]].deleteorselect!=-1){
                database[databasecorrect[i]].deleteorselect=1;
                //把database的參數改成1就算留下
                }
                }
                howmanycorrect=finddatabase(command,index,buffer,database,num1,databasecorrect,1);
                for(int i=0;i<howmanycorrect;i++){
                if(database[databasecorrect[i]].deleteorselect!=-1){
                database[databasecorrect[i]].deleteorselect=1;
                //把database的參數改成1就算留下
                        }
                }
        }
    }
}
void deletedatabase(char *command,int index,char *buffer,record *database,int num1){
    //叫出database的時候要用箭頭
    int databasecorrect[301]={-1};
    while(index>=0){
        index=getNextToken(command,index,buffer);
        int howmanycorrect;
        if(strcmp(buffer,"WHERE")==0){
            //有一個陣列讓我存有可能的答案,如果比對正確,存ID
            //還沒寫=mark
            howmanycorrect=finddatabase(command,index,buffer,database,num1,databasecorrect,0);
            //表示沒有or/and
            if(howmanycorrect<0){
                //0的話表示不需比對直接式這樣的資料刪除
                finaldatabase(command,index,buffer,database,num1,databasecorrect,-howmanycorrect,0,1);
                break;
            }
            //上面讓他回傳一個值代表它有幾個正確的比對資料
        }
        if(strcmp(buffer,"OR")==0){
            //找到真正要刪掉的就把database的id設成-1
           finaldatabase(command,index,buffer,database,num1,databasecorrect,howmanycorrect,1,1);

        }
        if(strcmp(buffer,"AND")==0){
           finaldatabase(command,index,buffer,database,num1,databasecorrect,howmanycorrect,2,1);

        }
    }
}
int selectdatabase(char *command,int index,char *buffer,record *database,int num1,int array[]){
     /*
ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
    */
    int checkorder=0;
    int check=1;//確認是第幾個
    index=getNextToken(command,index,buffer);
    int checkround=0;
    //把順序決定好了
    while(checkround!=1){
        if(buffer[0]=='I'){
            array[1]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='S'){
            array[2]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='C'){
            array[3]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='E'){
            array[4]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='P'){
            array[5]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='N'){
            array[6]=check;
            check++;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
        else if(buffer[0]=='*'){
            array[1]=1;
            array[2]=3;
            array[3]=4;
            array[4]=5;
            array[5]=6;
            array[6]=2;
            index=getNextToken(command,index,buffer);
            if(buffer[0]=='F'){
                checkround=1;
            }
        }
    }
    int databasecorrect[301]={-1};
    int howmanycorrect;
    while(index>=0){
        index=getNextToken(command,index,buffer);
        int check2=0;
        if(strcmp(buffer,"WHERE")==0){
            check2=1;
        }
        if(check2==1){
            //有一個陣列讓我存有可能的答案,如果比對正確,存ID
            //還沒寫=mark
            howmanycorrect=finddatabase(command,index,buffer,database,num1,databasecorrect,0);
            //表示沒有or/and
            if(howmanycorrect<0){
                //0的話表示不需比對直接式這樣的資料刪除
                finaldatabase(command,index,buffer,database,num1,databasecorrect,-howmanycorrect,0,2);
                break;
            }
            //上面讓他回傳一個值代表它有幾個正確的比對資料
        }//mark
        if(strcmp(buffer,"OR")==0){
            //找到真正要刪掉的就把database的id設成1
           finaldatabase(command,index,buffer,database,num1,databasecorrect,howmanycorrect,1,2);

        }
        if(strcmp(buffer,"AND")==0){
           finaldatabase(command,index,buffer,database,num1,databasecorrect,howmanycorrect,2,2);

        }
        /*
ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
    */
        if(strcmp(buffer,"BY")==0){
            index=getNextToken(command,index,buffer);
            checkorder=1;
            int howreturn=0;
            if(buffer[0]=='I'){
                howreturn=1;
            }
            else if(buffer[0]=='S'){
                howreturn=2;
            }
            else if(buffer[0]=='C'){
                howreturn=3;
            }
            else if(buffer[0]=='E'){
                howreturn=4;
            }
            else if(buffer[0]=='P'){
                howreturn=5;
            }
            else if(buffer[0]=='N'){
                howreturn=6;
            }
            index=getNextToken(command,index,buffer);
            if(strcmp(buffer,"DESC")==0){
                return howreturn*10;
            }
            else if(strcmp(buffer,"ASC")==0){
                return howreturn*10+1;
            }
        }
    }//0代表不用排  (10整除)desc代表大到小  不整除asc代表小到大
    if(checkorder==0){
        return 0;
    }
}
void printanddelete(record *database,int num1,int array[],int order,rightrecord *undatabase){
    if(order==-1){
        for(int i=0;i<num1;i++){
            if(database[i].deleteorselect==-1){
                undatabase[i].deleteorselect=-1;
            }
        }
    }//不用排印出//印出後database[i]->deleteorselect=0;
    else if(order==0){
        for(int i=0;i<num1;i++){
            if(undatabase[i].deleteorselect!=-1){
                if(database[i].deleteorselect==1){
                    //印出後要1改成0//ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
                    //照順序印出
                    for(int v=1;v<7;v++){
                        for(int g=1;g<7;g++){
                            if(array[g]==v){
                                if(g==1){
                                    printf("%d ",database[i].id);
                                    break;
                                }
                                else if(g==2){
                                    printf("%d ",database[i].studentid);
                                    break;
                                }
                                else if(g==3){
                                    printf("%s ",database[i].classroom);
                                    break;
                                }
                                else if(g==4){
                                    printf("%s ",database[i].email);
                                    break;
                                }
                                else if(g==5){
                                    printf("%s ",database[i].phone);
                                    break;
                                }
                                else if(g==6){
                                    printf("%s ",database[i].name);
                                    break;
                                }
                            }
                        }
                    }
                    printf("\n");
                    database[i].deleteorselect=0;
                }
            }
        }
    }//大到小印出
    else if(order%10==0){
        int number=fromtoptolow(order,database,undatabase,num1,array);
            for(int i=0;i<number;i++){
                    //印出後要1改成0//ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
                    //照順序印出
                    for(int v=1;v<7;v++){
                        for(int g=1;g<7;g++){
                            if(array[g]==v){
                                if(g==1){
                                    printf("%s ",undatabase[i].id);
                                    break;
                                }
                                else if(g==2){
                                    printf("%s ",undatabase[i].studentid);
                                    break;
                                }
                                else if(g==3){
                                    printf("%s ",undatabase[i].classroom);
                                    break;
                                }
                                else if(g==4){
                                    printf("%s ",undatabase[i].email);
                                    break;
                                }
                                else if(g==5){
                                    printf("%s ",undatabase[i].phone);
                                    break;
                                }
                                else if(g==6){
                                    printf("%s ",undatabase[i].name);
                                    break;
                                }
                            }
                    printf("\n");
                    database[i].deleteorselect=0;
                }
            }
        }
    }//小到大印出
    else if(order%10!=0){
         int number=fromlowtotop(order,database,undatabase,num1,array);
         for(int i=0;i<number;i++){
                    //印出後要1改成0//ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
                    //照順序印出
                    for(int v=1;v<7;v++){
                        for(int g=1;g<7;g++){
                            if(array[g]==v){
                                if(g==1){
                                    printf("%s ",undatabase[i].id);
                                    break;
                                }
                                else if(g==2){
                                    printf("%s ",undatabase[i].studentid);
                                    break;
                                }
                                else if(g==3){
                                    printf("%s ",undatabase[i].classroom);
                                    break;
                                }
                                else if(g==4){
                                    printf("%s ",undatabase[i].email);
                                    break;
                                }
                                else if(g==5){
                                    printf("%s ",undatabase[i].phone);
                                    break;
                                }
                                else if(g==6){
                                    printf("%s ",undatabase[i].name);
                                    break;
                                }
                            }
                    printf("\n");
                    database[i].deleteorselect=0;
                }
            }
    }
}
}//排列大小//按照順序排後存在undatabase裡然後照個數印出在mark:undatabase裡的東西
int fromtoptolow(int order,record *database,rightrecord *undatabase,int num1,int array[]){
    int count=0;
    int count2=0;
    int subject=order/10;
    for(int i=1;i<7;i++){
        if(array[i]!=0){
            count2++;
        }
    }
    //ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
    if(subject==1){
        int check[301]={0};
        for(int i=0;i<count2;i++){
            int max=-1;
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].id>max&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    max=database[v].id;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }
    else if(subject==2){
        int check[301]={0};
        for(int i=0;i<count2;i++){
            int max=-1;
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].studentid>max&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    max=database[v].studentid;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }
    else if(subject==5){
            int check[301]={0};
        for(int i=0;i<count2;i++){
            int max=-1;
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].phone>max&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    max=database[v].phone;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }


}//排列小大
int fromlowtotop(int order,record *database,rightrecord *undatabase,int num1,int array[]){
    int count=0;
    int count2=0;
    int subject=order/10;
    for(int i=1;i<7;i++){
        if(array[i]!=0){
            count2++;
        }
    }
    //ID=1;StudentID=2;Class=3;Email=4;Phone=5; Name=6;
    if(subject==1){
        int check[301]={0};
        for(int i=0;i<count2;i++){
            long long int mini=1e12;//這裡有可能太小
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].id<mini&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    mini=database[v].id;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }
    else if(subject==2){
                int check[301]={0};
        for(int i=0;i<count2;i++){
            long long int mini=1e12;//這裡有可能太小
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].studentid<mini&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    mini=database[v].studentid;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }
    else if(subject==5){
        int check[301]={0};
        for(int i=0;i<count2;i++){
            long long int mini=1e12;//這裡有可能太小
            int check2=-1;//確認有沒有找到
            for(int v=0;v<num1;v++){
                if(database[v].phone<mini&&undatabase[v].deleteorselect!=-1&&check[v]==0){
                    mini=database[v].phone;
                    check2=v;
                }
            }
            if(check2!=-1){
                check[check2]=1;
                undatabase[i].id=database[check2].id;
                undatabase[i].studentid=database[check2].studentid;
                strcpy(undatabase[i].classroom, database[check2].classroom);
                strcpy(database[i].email, database[check2].email);
                strcpy(database[i].phone, database[check2].phone);
                strcpy(database[i].name,database[check2].name);
                check2=-1;
            }
        }
        return count2;//幾個要印直接印undatabase的內容
    }

}
