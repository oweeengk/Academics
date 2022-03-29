#include <iostream>

using namespace std;

struct Node* head; //assigning a global variable pointer head for code-wide use.

struct Node{ //setting up the Node and its variables.
    public:
        int data;
        Node* prevPtr;
        Node* nextPtr;
};

struct Node* createNode(int x){ //assigning the struct for creating a Node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); //allocating a block of memory from heap (using dynamic memory allocation)
    
    newNode->data = x; //during the creation of Nodes, the data is given whereas the pointers are initialized as NULL.
    newNode->prevPtr = NULL;
    newNode->nextPtr = NULL;
    
    return newNode;
}

bool isLinkedListEmpty(){ //boolean function used to check if the linkedlist is empty.
    struct Node* temp = head;
    if(temp==NULL){
        return true;
    }
    else {
        return false;
    }
}

void InsertAtHead(int x){ //function created to insert a created node based on the variable head as reference, which I set up to be the first variable.
    struct Node* nodeInserted = createNode(x);
    if(head==NULL){
        head = nodeInserted; //for the case of initialization.
        return;
    }
    head->prevPtr = nodeInserted; //these last lines of InsertAtHead function is to connect the pointers in each node to one another.
    nodeInserted->nextPtr = head;
    head = nodeInserted;
}

void PrintNodes(){ // function created to print nodes in a straightforward manner.
    struct Node* temp = head;
    if(isLinkedListEmpty()==true){ //it shouldn't print anything if the linkedlist is empty.
        printf("[4] Linked list is empty.");
        return;
    }
    printf("[4]: ");
    while(temp!=NULL){ //while statement that continues until the temp variable is at its end (NULL).
        printf("%d ", temp->data); //printing the data in the nodes.
        temp=temp->nextPtr; //dynamic changing of the value of temp.
    }
    printf("\n");
}

void ReversePrintNodes(){ //similar to PrintNodes() function except in a reversed manner (bonus).
    struct Node* temp = head;
    if(isLinkedListEmpty()==true){ //it shouldn't print anything if the linkedlist is empty.
        printf("[5] Linked list is empty.");
        return;
    } 
    
    while(temp->nextPtr!=NULL){ 
        temp = temp->nextPtr; //a dynamic changing of the value of temp.
    }
    
    printf("[5] ");
    while(temp!=NULL){
        printf("%d ", temp->data); //reverse printing of the nodes data within the linkedlist.
        temp=temp->prevPtr;
    }
    printf("\n");
}

bool doesNumExist(int x){ //this boolean function is created to check whether the number given exists in the linkedlist
    struct Node* temp = head;
    int ans = 0; //I just wanted to do this, really.
    while(temp!=NULL){ //this while statement traverses around the linkedlist checking whether the given number exists in the linked list.
        if(temp->data==x){
            ans=1;
            temp=NULL;
        }
    }
    if(ans==0){
        return false;
    }
    else{
        return true;
    }
}

struct Node* getPos(int x){ //this function is used to find the address of the given data value.
    struct Node* temp = head;
    if(isLinkedListEmpty()==true){ //this function is useless if the linkedlist is empty in the firstplace
        printf("\nThe linked list is empty");
        return NULL;
    }
    else{
        while(temp->data!=x){ //this while statement dynamically finds the data value of each node to and returns the pointer value.
            temp=temp->nextPtr;
        }
        return temp;
    }
}

void deleteNode(int x){ //this is a void function used to delete a node given the integer value x.
    if((isLinkedListEmpty()==true)||(doesNumExist(x)==false)){ //this if statement is used to check if either linked list is empty or the number doesn't exist, because if either is true, this function is essentially useless.
        printf("\nInvalid argument!");
        return;
    }
    struct Node* temp = getPos(x); //node pointer used to find the position (address) of the given data value in the linked list
    struct Node* prev = temp->prevPtr; //node pointer used to find the previous pointer of the given node.
    struct Node* next = temp->nextPtr; //node pointer used to find the next pointer of the given node.
    if((prev==NULL)&&(next==NULL)){ //this means that the given is the only node in the linkedlist.
        head=head->nextPtr; //changing head reference to next pointer to properly delete the given node.
        delete(temp);
        return;
    }
    else{
        if((prev==NULL)||(next==NULL)){
            if(next!=NULL){ //this means that the previous node doesn't exist. (The node given is the first in the linkedlist.)
                next->prevPtr=NULL; //nullify the previous node pointer.
                delete(temp); //delete the node given.
                head=head->nextPtr; //changing the value of head reference node to the head nextPtr.
                
            }
            else{ // this means that the next node doesn't exist. (The node given is the last of the linkedlist.)
                prev->nextPtr=NULL;  //to change the previous nodes' next pointer to NULL.
                delete(temp); //deleting the node given.
            }
        }
        else{ //in the case that the next and previous nodes exist (The node given is in the middle of the linkedlist.)
            prev->nextPtr = next; //connecting the previous node's nextPtr to be the next node after the node given.
            next->prevPtr = prev; //connecting the next node's prevPtr to be the previous node before the node given.
            delete(temp);
        }
    }
    
}

int main()
{
    head=NULL; //initializing the value of global variable as NULL.
    int choice;
    int given;
    cout << "This program creates a doubly linked list in C++ that can add, delete, and check nodes.\n";
    do{
        printf("\n*********************************************");
        printf("\n\t 1. Insert a node.");
        printf("\n\t 2. Delete a node.");
        printf("\n\t 3. Check if the node is empty.");
        printf("\n\t 4. Print nodes.");
        printf("\n\t 5. Reverse node printing.");
        printf("\n\t 0. Exit.");
        printf("\n*********************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        switch(choice){
            case 1:
                printf("[1] What value do you want to insert? ");
                cin >> given;
                InsertAtHead(given);
                printf("%d is inserted.", given);
                break;
            case 2:
                printf("[2] Which value do you want to delete? ");
                cin >> given;
                deleteNode(given);
                break;
            case 3:
                if(isLinkedListEmpty()==true){
                    printf("[3] The node is empty.");
                }
                else{
                    printf("[3] The node is not empty.");
                }
                break;
            case 4:
                PrintNodes();
                break;
            case 5:
                ReversePrintNodes();
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
