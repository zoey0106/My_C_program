#include "myDS.h"
#include "basic.h"

// HEAD is point to FOODPAPA (id: 0)
void my_insert(struct node* HEAD, int ID, char *Name, int node_id){
	//先找節點是否存在，存在再建立新的節點
	struct node *p = HEAD;

	for(;p!=NULL;p = p ->next){
		if(p->id == ID){
			break;//找到自動break
		}
	}
	if(p == NULL){
		// If it doesn't exit such ID, print "INVALID OPERATION"
		printf("INVALID OPERATION\n");
	}
	else{
		// Please insert a new node(store Name & node_id)
		struct node *node = (struct node*)calloc(1,sizeof(struct node));//先建立一個新的節點
		strncpy(node->name,Name,MAX_Name-1);
		node ->id = node_id;
		struct node *temp = p->next;
		p->next = node;
		node->next = temp;
		// after the node which id is ID
	}
}
void my_delete(struct node* HEAD, char *Name){
	// Delete the node which store the Name.
	//先找節點是否存在
	struct node *p = HEAD;

	for(;p!=NULL;p = p ->next){
		if(strcmp(p->name,Name)==0){
			break;//找到自動break
		}
	}
	
	if(p == NULL){
		// If it doesn’t exit such Name, print “INVALID OPERATION”.
		printf("INVALID OPERATION\n");
	}
	else{
		//若是真的找到node還需要把它前面的node找出來
		struct node *p2 = HEAD;
		for(;p2!=NULL;p2=p2->next){
			if(p2->next == p){
			p2->next = p->next;//把最前面和最後面連接起來
				break;//p2會是需要被刪除的node的前一個節點
			}
		}
		
		//刪除node
		free(p);
	}
}
void my_swap(struct node *HEAD, char *Name1, char *Name2){
	// Swap the node which store Name1 and Name2
	//先找節點是否存在
	struct node *p = HEAD;
	struct node *p2 = HEAD;
	
	for(;p!=NULL;p=p->next){
		if(p->next==NULL){
			p = NULL;
			break;
		}
		if(strcmp(p->next->name,Name1)==0){//因為第一個不能做動作，因此可以直接用next下去找(迴圈看不到第一個節點)
			break;
		}
	}
	for(;p2!=NULL;p2 = p2->next){
		if(p2->next == NULL){
			p2 = NULL;
			break;
		}
		if(strcmp(p2->next->name,Name2)==0){
			break;
		}
	}

	if(p == NULL||p2 == NULL){//任一找不到
	// If either of the node doesn’t exit, print “INVALID OPERATION”
		printf("INVALID OPERATION\n");
	}
	else{
		//代表兩點連接在一起
		int state = 0;
		if(p->next == p2){
			state = 1;//p在前面
		}
		if(p2->next == p){
			state = 2;//p2在前面
		}

		//兩點沒有連接在一起的話 a->b->c->d   b/d要換
		if(state == 0){
			struct node *temp = p->next;//a->next = b
			struct node *temp2 = p2->next;//c->next = d
			p->next = temp2;//a->d
			p2->next = temp;//c->b
			struct node *temp3 = temp->next;//b->next = c
			struct node *temp4 = temp2->next;//d->next = NULL or anything
			temp->next = temp4;//b->next = d->next  b->NULL
			temp2->next = temp3;//d->next = b->next d->c
			//a->d->c->b->NULL
		}
		else{//兩者分別在前後
			//p在前面
			if(state == 1){//a->b->c->~  b/c要換
				struct node *temp = p->next;//a->next = b
				p->next = p2->next;//a->c
				struct node *temp2 = p2->next->next;//c->next = ~
				p2->next->next = temp;//c->b
				temp ->next = temp2;//b->~
				// a->c->b->~
			}//p2在前面
			else{
				struct node *temp = p2->next;//a->next = b
				p2->next = p->next;//a->c
				struct node *temp2 = p->next->next;//c->next = ~
				p->next->next = temp;//c->b
				temp ->next = temp2;//b->~
				// a->c->b->~
			}
		}
	}
	// NOTICE: don't just swap the node's value
	// You need to break the link and recombine it
}
void my_print_id(struct node *HEAD, char *Name){
	// Print the id of the corresponding Name.
	//先找節點是否存在
	struct node *p = HEAD;

	for(;p!=NULL;p = p ->next){
		if(strcmp(p->name,Name)==0){
			break;//找到自動break
		}
	}
	if(p==NULL){
		printf("INVALID OPERATION\n");
	}
	else{
		printf("%d\n",p->id);
	}
	// If Name doesn’t exit, print “INVALID OPERATION”
}
void my_print_name(struct node *HEAD, int ID){
	// Print the name of the corresponding ID
	//先找節點是否存在，存在再建立新的節點
	struct node *p = HEAD;

	for(;p!=NULL;p = p ->next){
		if(p->id == ID){
			break;//找到自動break
		}
	}
	if(p == NULL){
		// If it doesn't exit such ID, print "INVALID OPERATION"
		printf("INVALID OPERATION\n");
	}
	else{
		printf("%s\n",p->name);
	}
	// If ID doesn’t exit, print “INVALID OPERATION”
}
void my_result(struct node* HEAD){
	// Print out all the information in the linked list orderly
	// in the format “ID NAME”. (start from HEAD)
	struct node *p = HEAD;
	for(;p!=NULL;p = p ->next){
		printf("%d %s\n",p->id,p->name);
	}
}
