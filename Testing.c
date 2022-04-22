
//1 HAVE A FULL BINARY SEARCH TREE WHEN THE PROGRAM STARTS
//2 HAVE A FUNCTION TO GET THE ADDRESS OF ANY NODE YOU DESIRE


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

// New Function Declarations
struct node * lv(int data);
struct node * sv(int data);
struct node *is(int data);
struct node *ip(int data);

// New Function Code

//prt(25) returns address of parent of node 25
//Assuming parent's data is already checked
struct node *prt(struct node *p, int data);

//f1(25) returns parent to the smallest node in subtree with root 25
struct node *f1(int data);
//f2(25) returns the parent of infix successor
struct node *f2(int data);
//g1(25) returns parent of largest node in 25 subtree
struct node *g1(int data);
//g2(25) returns parent of infix predecessor to 25
struct node *g2(int data);

void delete(int data){
	struct node *neww;
	int left;

//  Find the node to be deleted
	struct node *del = address(root, data);
	

	
//	Find the parent of the node to be deleted;
	struct node *pt = prt(root, data);

	
//Find whether the node to be deleted is left child or not
	if(pt->lchild == del){
//		If node to be deleted is leftchild then left = 1
	 left = 1;
//printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>LEFT CHILD");

	  }
	else {
//	    Else left would be zero
//printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>RIGHT CHILD");

	left = 0;}

//If it doesn't have any children then Nullify
	if(del->lchild == NULL && del->rchild == NULL){
		
		if(left == 1){
			pt->lchild = NULL;			
		}else{
			pt->rchild = NULL;
		}
		
	
		return;

	}
	
//Atleast Left Child
	if(del->lchild != NULL){
//		lchild of the del is itself infix predecessor

		if(del->lchild->rchild == NULL){
			neww = del->lchild;
//			printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>new->data = %d", neww->data);
			neww->rchild = del->rchild;
			del->rchild = NULL;
			neww->lchild = NULL;
			
			if(left == 1){
				
				pt->lchild = neww;

			}
			else{
			

				pt->rchild = neww;
			} 
			
//			printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>pt->data = %d, pt->Rchild->data = %d", pt->data, pt->rchild->data);
			
			return;			
		}
		
		struct node *ipp = g2(data);

		struct node *ip = ipp->rchild;
		ipp->rchild = ip->lchild;
		
		ip -> lchild = del -> lchild;
		ip -> rchild = del -> rchild;
		
		if(left == 1) pt -> lchild = ip;
		else pt -> rchild = ip;
		
		return;	
		
		
	} else {
		if(del->rchild->lchild == NULL ){
			if(left == 1) pt->lchild = del->rchild;
			else pt->rchild = del->rchild;
			return;	
		}
		
		struct node *isp = f2(data);
		struct node *is = isp->lchild;
		isp->lchild = is->rchild;
		
		is->lchild = del->lchild;
		is->rchild = del->rchild;
		
		if(left == 1){
		 pt->lchild = is;}
		else {
		pt->rchild = is;}
		
		return;	
		
	}
}

int main(){
	
	initialize();
	printf("Printing all the nodes in tree\n");
	inorder(root);

	int values[] = {100, 300, 50, 150, 250, 350, 25, 75, 125, 175, 225, 275, 325, 375};
	int l = 14;
	
	
//	THE BINARY SEARCH TREE
//	               200
//	     100               300
//	  50      150        250      350
//	25 75   125 175   225 275   325 375	

//To get the address of node 250 type,
//           address(root, 250)
	
// TEST THE NEW FUNCTION HERE

	
	int i;
	int test;
	for(i = 0; i<l; i++){
		test = values[i];
		printf("\n\n(Deleted %d)", test);
		delete(test);
		inorder(root);
		
	}
	
	printf("\n\n\n 200 is the root. code to delete root will be added soon");

//test = 150;
//delete(150);
//printf("\n Deleted 150\n");
//inorder(root);



	
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


//NEW FUNCTIONS 

// lv(5) would return highest value in subtree that has 5 as it's root node. Including 5 itself.
struct node * lv(int data){
	
	struct node *trav = address(root, data);
	while(trav->rchild != NULL){
		trav = trav->rchild;
	}
	
	return trav;	
}

// sv(5) would return lowest value in subtree that has 5 as it's root node. Including 5 itself.
struct node * sv(int data){
	
	struct node *trav = address(root, data);
	while(trav->lchild != NULL){
		trav = trav->lchild;
	}
	
	return trav;	
}

// is(25) finds infix successor to node with data 25. Ends abruptly if not present.
struct node *is(int data){
	struct node *parent = address(root, data);
	if(parent->rchild == NULL){
		if(parent->lchild == NULL){
			printf("\n No infix successor to %d. Ending program abruptly", data);
			exit(1);
		}
		return parent;
	} 
	else return sv(parent->rchild->data);
}

// ip(25) finds infix predecessor to node with data 25. Ends abruptly if not present.
struct node *ip(int data){
	struct node *parent = address(root, data);
	if(parent->lchild == NULL){
		if(parent->rchild == NULL){
			printf("\n No infix predecessor to %d. Ending program abruptly", data);
			exit(1);
		}
		return parent;
	} 
	else return lv(parent->lchild->data);
}



//prt(root,25) returns address of parent of node 25
//Assuming parent's data is already checked
struct node *prt(struct node *p, int data){
	if(p->lchild == NULL && p->rchild == NULL){
		printf("\n Given node is not present. Ending program abruptly.");
		exit(1);
	}

	
	if((p->lchild != NULL && p->lchild->data == data)||(p->rchild!=NULL && p->rchild->data == data)){
		return p;
	}
	
	
	if(data < p->data){
		return prt(p->lchild, data);
	}else if(data > p->data){
		return prt(p->rchild, data);
	}
}

//f1(25) returns parent to the smallest node in subtree with root 25
struct node *f1(int data){
	struct node *trav = address(root, data);
	
	if(trav->lchild == NULL){
		printf("\n Least child is node itself, ending the program abruptly");
		exit(0);
	}
	
	while(trav->lchild->lchild != NULL){
		trav = trav->lchild;		
	}
	
	return trav;
}

//f2(25) returns the parent of infix successor
struct node *f2(int data){
	struct node *trav = address(root, data);
	
	if(trav->rchild == NULL){
		printf("\n Given node doesn't have infix successor. Ending program abruptly");
		exit(1);
	}else if(trav->rchild->lchild == NULL){
		return trav;
	}
	
	return f1(trav->rchild->data);
}

//g1(25) returns parent of largest node in 25 subtree
struct node *g1(int data){
	struct node *trav = address(root, data);
	
	if(trav->rchild == NULL){
		printf("Doesn't have any larger nodes in the subtree. Ending the program abruptly");
		exit(1);
	}
	
	while(trav->rchild->rchild != NULL){
		trav = trav->rchild;
	}
	
	return trav;
}

//g2(25) returns parent of infix predecessor to 25
struct node *g2(int data){
	
	struct node *trav = address(root, data);
	
	if(trav -> lchild == NULL){
		printf("\nDoesn't have any infix predecessor. Ending program abruptly");
		exit(1);
	}else if(trav->lchild->rchild == NULL){
		return trav;
	}else{
		return g1(trav->lchild->data);
	}
	
	
}


