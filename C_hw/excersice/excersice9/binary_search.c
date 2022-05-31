#include <stdio.h>
#include <stdlib.h>

struct tNode{
	int data;
	struct tNode *Lchild, *Rchild;
};

struct tNode *insert(struct tNode *curNode, int data){
	//insert
	if (curNode == NULL){
		//create new node
		struct tNode *newData = (struct tNode *) malloc(sizeof (struct tNode));
		newData->data = data;
		newData->Lchild = NULL;
		newData ->Rchild = NULL;
		return newData;
	}
	else{	//find proper position
		if (data < curNode -> data) curNode -> Lchild = insert(curNode -> Lchild, data);
		else curNode ->Rchild = insert(curNode -> Rchild, data);
	}
	return curNode;
}

void traverse(struct tNode *curNode){
	if(curNode!=NULL){
		traverse(curNode->Lchild);
		printf("%d ",curNode->data);
		traverse(curNode->Rchild);
	}
}

int find(struct tNode *curNode, int target){
	for(;curNode!=NULL;){
		if(curNode->data == target){
			int data;
			int data2;
			if(curNode->Lchild == NULL){data = 0;}
			else{data = curNode->Lchild->data;}
			if(curNode->Rchild == NULL){data2 = 0;}
			else{data2 = curNode->Rchild->data;}
			return data + data2;
		}
		else if(curNode->data > target){
			curNode = curNode->Lchild;
		}
		else{
			curNode = curNode->Rchild;
		}
	}
	printf("Not in tree\n");
	return -1;
}

void delete_tree(struct tNode* curNode){
	if (curNode == NULL) return;
	delete_tree(curNode->Lchild);
	delete_tree(curNode->Rchild);
	free(curNode);
}

int main(){
	int numData = 0;
	int tmpNum;
	scanf("%d", &numData);

	struct tNode *root = NULL;

	//insert every data, all data > 0
	for (int i = 0; i < numData; i++){
		scanf("%d", &tmpNum);
		root = insert(root, tmpNum);
	}

	//traverse
	traverse(root);
	puts("");

	//find
	while(scanf("%d", &tmpNum)!=EOF){
		int sum = find(root, tmpNum);
		if (sum != -1) printf("%d\n", sum);
	}

	//free memory
	delete_tree(root);
	return 0;
}
