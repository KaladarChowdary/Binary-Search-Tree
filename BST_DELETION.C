#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
	int data;
	struct node *lchild, *rchild;
};

struct node *root = NULL;

//FUNCTION DECLARATIONS
void inorder(struct node*);
void insert();
void func1(struct node*, int);
void init(struct node*, int);


// (1)Finding parent of the node with given data

//Takes node and value
//Check with node, Check with the children
//Root node is special case
//If any child is equal return the parent
//Else call the same function with appropriate child
//Lesser than left child? Call with left child
//Greater than right child? Call with right
struct node* findp(struct node* parent,int data){
	struct node* l;
	struct node* r;
	l = parent->lchild;
	r = parent->rchild;
	
	if(l == NULL && r==NULL){
		printf("\nGiven node not present");
		exit(1);
	}else if( l == NULL && data < parent->data){
		printf("\nGiven node not present");
		exit(1);		
	}else if( r == NULL && data> parent->data){
		printf("\nGiven node not present");
		exit(1);
	}
	
	if( l->data == data || r->data == data){
		return parent;
	}else if( data < l->data){
		return findp(l, data);
	}else if(data > r->data){
		return findp(r, data);
	}else{
		printf("\nGiven node not present");
		exit(1);	
	}
}

//(2)Check for the children
//Returns the number of children
int number(struct node* parent){
	int n = 0;
	
	if(parent->lchild != NULL){
		n++;
	}
	if(parent->rchild != NULL){
		n++;
	}
	
	return n;
}


struct node * infix(struct node* root){
	struct node *trav;
	struct node *parent;
	
	
	if(root->lchild != NULL){
		parent = root;
		trav = root->lchild;
		
		while(trav->rchild != NULL){
			parent = trav;
			trav = trav->rchild;
		}
		
		parent->lchild = trav->lchild;
	}else if(root->rchild != NULL){
		parent = trav;
		trav = root->rchild;
		
		while(trav->lchild != NULL){
			trav = trav->lchild;
		}
		parent->rchild = trav->rchild;
	}else{
		printf("\nThis node doesn't have any infix successor or infix predecessor");
		exit(1);
	}
	
	return trav;
}


//FUNCTIONS TO DELETE GIVEN NODE
//	CONSIDER SPECIAL CASES
//	SEARCH FOR THE NODE
//	FIND IT'S INFIX SUCESSOR IF NOT INFIX PREDECESSOR
//	REMOVE IT FROM THAT TREE 
//	REPLACE WITH PARENT

//Mini procedure we'll use in another function
//  Assuming that this will be called on node that exists and has value
//	Takes just a node 
//	If there's a left child, finds infix predecessor
//	Else finds infix successor
//	Else No predecessor or successor

void del(int data){

////	Find the parent of the node with given data
////	Check for the children
////	No child case
////	Single child case
////	Multiple child case
	bool left;
	struct node* replace;
	
	struct node* parent = findp(root, data);
	
	struct node* l = parent->lchild;
	struct node* r = parent->rchild;
	struct node* d;
	if(data == l->data){
		d = l;
		left = true;
	}else{
		d = r;
		left = false;
	}
	
	int nchild = number(d);
	
	switch(nchild){
		case 0:
			if(left)
				parent->lchild = NULL;
			else 
				parent->rchild = NULL;
			break;
		case 1:
			replace = infix(d);
			if(left)
				parent->lchild = replace;
			else
				parent->rchild = replace;
			
			replace->lchild = d->lchild;
			replace->rchild = d->rchild;
			free(d);
			break;
		case 2:
			replace = infix(d);
			if(left)
				parent->lchild = replace;
			else
				parent->rchild = replace;
			
			replace->lchild = d->lchild;
			replace->rchild = d->rchild;
			break;
	}
}



int main(){
	
	insert();
	printf("Printing the tree through inorder traversal");
	inorder(root);
	
	printf("\nDeleting 5 from the tree");
	del(5);
	printf("\nPrinting the tree after deleting 5");
	inorder(root);
	
	printf("\n\n\n\n\n\n\n\n\n");
	return 1;
}


//From BST.C
//Takes node and data
//Assigns data to node
//Makes both children as Null
void init(struct node *parent, int data){
	parent->data = data;
	parent->lchild = NULL;
	parent->rchild = NULL;}

//FROM BST.C
//Takes node and data
//*Assuming that node is already filled
//Inserts the data into the corrected position in the tree
void func1(struct node *parent, int data){

	if(parent != NULL){

		if(data <= parent->data){
			if(parent->lchild == NULL){
				parent->lchild = (struct node *)malloc(sizeof(struct node));
				init(parent->lchild, data);
			}else{
				func1(parent->lchild, data);
			}
		}else{
			if(parent->rchild == NULL){
				parent->rchild = (struct node *)malloc(sizeof(struct node));
				init(parent->rchild, data);
			}else{
				func1(parent->rchild, data);
			}
		}
	}
}

//Inside the function:
//Give no of values to be inserted
//Enter all the values
// Tree is created
void insert(){
	int i,n, value;
	
	printf("\nNo of values to insert: ");
	scanf("%d", &n);
	if(n<=0)
		exit(1);
		

	
	for(i = 1; i<= n ; i++){
		if(root == NULL){
		root = (struct node *)malloc(sizeof(struct node));
		scanf("%d", &value);
		init(root,value);
		continue;
		}
		fflush(stdin);
		scanf("%d", &value);
		
		func1(root, value );
	}
	
		printf("\nTress is successfully created with all the given elements\n\n");

}

//FROM BST.C
//Prints the tree in inorder
void inorder(struct node *parent){
	if(parent != NULL){
		inorder(parent->lchild);
		printf(" %d ", parent->data);
		inorder(parent->rchild);
	}
	
}


	
