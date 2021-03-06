
//1 HAVE A FULL BINARY SEARCH TREE WHEN THE PROGRAM STARTS
//2 HAVE A FUNCTION TO GET THE ADDRESS OF ANY NODE YOU DESIRE
//
//1 DIVIDE EVERY CODE INTO SMALLEST COMPONENTS
//2 EXECUTE THE SMALLEST FUNCTIONS 
//3 EVERY PROBLEM BECOMES HUNDRED TIMES EASIER

#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *lchild, *rchild;
};

struct node *root = NULL;
//Function Declarations
void init(struct node *parent,int data);
void insert(struct node *parent, int data);
void initialize();
void inorder(struct node *parent);
struct node* address(struct node *parent, int data);

// Write New Function Code Here


int main(){
	
	initialize();
	inorder(root);
	
	
//	THE BINARY SEARCH TREE
//	               200
//	     100               300
//	  50      150        250      350
//	25 75   125 175   225 275   325 375	

//To get the address of node 250 type,
//           address(root, 250)
	
// TEST THE NEW FUNCTION HERE
printf("\n %d", address(root,5)->data);



	
	printf("\n\n\n\n\n\n\n");
	return 1;
}

//Insert data and nullify children
void init(struct node *parent,int data){
	parent->data = data;
	parent->lchild = NULL;
	parent->rchild = NULL;
}

//Recursive insertion of single value
void insert(struct node *parent, int data){
//	Assuming parent is filled
	if( data < parent->data){
		if(parent->lchild == NULL){
			parent->lchild = (struct node*)malloc(sizeof(struct node));
			init(parent->lchild,data);
		}else{
			insert(parent->lchild, data);
		}
	} else if (data > parent->data){
		if(parent->rchild == NULL){
			parent->rchild = (struct node *)malloc(sizeof(struct node));
			init(parent->rchild, data);
		}else{
			insert(parent->rchild, data);
		}
	} else{
		printf("\n Two nodes aren't supposed to have same value in BST");
	}
	

}

//Create the binary search tree with predefined values
void initialize(){
//	Function to initialize data into node and nullify it's children
//	Function for recursive insertion
//	Insert root
//	Create array of remaining elements
//	Insert each of them
	root = (struct node *)malloc(sizeof(struct node));
	init(root, 200);
	int values[] = {100, 300, 50, 150, 250, 350, 25, 75, 125, 175, 225, 275, 325, 375};
	int i;
	
	for(i = 0; i<14; i++){
		insert(root, values[i]);
	}
}

//Inorder Traversal
void inorder(struct node *parent){
	if(parent != NULL){
		inorder(parent->lchild);
		printf(" %d ", parent->data);
		inorder(parent->rchild);
	}
}

//Get the address of given node
struct node* address(struct node *parent, int data){
	if(parent == NULL){
		printf("\n Given value isn't present. Ending the program abrutptly");
		exit(1);
	}
	
	if(parent -> data == data){
		return parent;
	}else if( data < parent->data){
		return address(parent->lchild, data);
	}else{
	   return address(parent->rchild, data);}
		
}
