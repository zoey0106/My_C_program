#ifndef myDS_H
#define myDS_H
struct node{
    char name[15];
	int id;
    struct node *next;
};
void my_insert(struct node*, int, char*, int);
void my_delete(struct node*, char*);
void my_swap(struct node*, char*, char*);
void my_print_id(struct node*, char*);
void my_print_name(struct node*, int);
void my_result(struct node*);
#endif

