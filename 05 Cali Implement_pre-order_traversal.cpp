#include <iostream> 

using namespace std; 

#define spaces 10

struct Node{ //for every node in the binary tree, it has two children: leftChild and rightChild.
	int data; 
	Node* leftChild;
	Node* rightChild;
};


bool isEmpty(struct Node* given){ //boolean function used to check if Node is empty.
    if(given==NULL){
        return true;
    }
    else{
        return false;
    }
}

struct Node* addNode(Node *rootptr, int data){ //struct addNode used to create a Node given int data.
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    bool isEmptyNode=isEmpty(rootptr);
    if(isEmptyNode){
        rootptr=temp;
        rootptr->data=data;
        rootptr->leftChild=NULL;
        rootptr->rightChild=NULL;
    }
    else if(data<=rootptr->data){
        rootptr->leftChild=addNode(rootptr->leftChild, data);
    }
    else{
        rootptr->rightChild=addNode(rootptr->rightChild, data);
    }
}

void displayPreorder(struct Node* given){ //functions created to display the nodes in the binary tree in preorder traversal.
	if (isEmpty(given)){ //base case for the recursion.
	    return;
	}

    printf("%d - ", given->data); //Print the current data node or print the first node.
	displayPreorder(given->leftChild); //recursive Function to print the leftChild subtree.
	displayPreorder(given->rightChild); //recursive function to print the rightChild subtree.
} 

void displayTree(struct Node* given, int tabs) { 
    if (isEmpty(given)){ //base case for the recursion.
        return; 
    }
    tabs+=spaces;
    displayTree(given->rightChild, tabs); 
    printf("\n");
    for(int counter = spaces; counter<tabs; counter++){
        printf(" ");
    }
    printf("%d\n", given->data);
    displayTree(given->leftChild, tabs); 
}

int main() 
{
	struct Node *rootptr=NULL;
    int choice;
    int given;
    do{
        
        printf("\n*********************************************");
        printf("\n\t 1. Insert a node.");
        printf("\n\t 2. Display tree");
        printf("\n\t 3. Display the preorder traversal");
        printf("\n\t 0. Exit.");
        printf("\n*********************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        switch(choice){
            case 1:
                printf("[BST Insertion] What value do you want to insert? ");
                cin >> given;
                rootptr = addNode(rootptr, given);
                printf("[!] %d is inserted.", given);
                break;
            case 2:
                if(rootptr==NULL){
                    printf("[BST DisplayTree] Tree has nothing to print!");
                    break;
                }
                printf("[BST DisplayTree] ");
                displayTree(rootptr, 0);
                break;
            case 3:
                if(rootptr==NULL){
                    printf("[BST DisplayPreorderTraversal] Tree has nothing to print!");
                    break;
                }
                printf("[BST DisplayPreorderTraversal] ");
                displayPreorder(rootptr);
                break;
            case 0:
                printf("[0] Program terminated.");
                break;
            default:
                printf("[!] Given number is not within the choices!");
                break;
        }
    }while(choice!=0);
    
    
	
	return 0; 
}