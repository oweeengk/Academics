#include <iostream>

using namespace std;

struct Node{ //setting a struct for Node containing an integer data (value) and a Node ptr next.
    int data;
    struct Node* next;
};

struct Node* head; //setting a global var struct Nodeptr for head ref
struct Node* tail;//setting a global var struct Nodeptr for tail ref

bool isEmpty(){ //function to check whether the linkedlist is empty using the head reference.
    if(head==NULL){
        return 1; //returns 1 as value for true (the linkedlist is empty).
    }
    else{
        return 0; //returns 0 as value for false (the linked list is not empty).
    }
}

void Enqueue(int data){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node)); //creating a temporary Node for data manipulation
    if(tail==NULL){ //if this is the first node to be enqueued.
        tail=temp; //assign the value of tail to temp to signify it is the tail flag for future purposes.
        tail->next=NULL; //the nextptr of the tail is set to NULL because there is no next ptr for the tail.
        tail->data=data; //setting the value of tail.data to the value inserted by user.
        head=tail; //assigning the value of head to temp to signify it is the head flag for future purposes.
    }
    else{ //in the case that the node enqueued is not the first node.
        tail->next=temp; //setting the nextptr of the tail into the temp node created.
        temp->data=data; //assigning the data given by the user into the temp node.
        temp->next=NULL; //there is no next ptr for the temp node.
        tail=temp; //lastly, setting the tail node into the temp node.
    }
}

void Dequeue(int data){
    struct Node* temp = head; //for data manipulation, starting with the temp ptr into the head ptr.
    if(isEmpty()==1){ //in the case that the node list is empty in the first place.
        printf("[2] List is empty! Nothing to delete."); //there is nothing to delete.
        return; //ending the whole function.
    }
    else{
        if(temp->next!=NULL){ //in the case that the linkedlist contains more than 1 node.
            temp=temp->next; //to set the temp to the next ptr to connect the missing linkedlist.
            printf("[2] %d is deleted from the queue\n", head->data); //to display 
            free(head); //to delete the node
            head = temp; //to connect the linkedlist to the next data.
        } 
        else{ //else, in the case that there is only 1 node in the linked list.
            printf("[2] %d is deleted from the queue\n", head->data); //display that the node deleted.
            free(head); //to delete the node.
            head = NULL; //set the head ptr to NULL because the linkedlist is now empty.
            tail = NULL;//set the tail ptr to NULL because the linkedlist is now empty.
        }
    }
}

void display(){ //void function to display the contents of the queued list.
    struct Node* temp = head; //setting a temp node ptr and setting it to head ref for data manipulation and data traversion.
    if(isEmpty()==1){ //in the case that the linkedlist is empty in the first place.
        printf("[!] Queue list is empty! Nothing to display here."); //display msg that the linkedlist is empty, thus, there is nothing to display.
        return; //to end the function call.
    }
    else{ //else, the linkedlist is not empty.
        printf("[3] Queue list: ");
        while(temp!=NULL){ //while statement used to continue until the temp ptr reaches the end of the linked list.
            printf("%d -> ", temp->data); //display the data contained in the temp data.
            temp = temp->next; //to assign the value of temp to the next node for every repetition of the while loop.
        }
        printf("END"); //signify end of the linkedlist.
    }
    
}

int main()
{
    head=NULL; //initialize the value of head ref to NULL (meaning the linkedlist is empty).
    tail=NULL;//initialize the value of tail ref to NULL (meaning the linkedlist is empty).
    int choice;
    int given;
    cout << "This program creates a singly linked list in C++ that can enqueue, dequeue, display, and check whether the queue list is empty\n";
    do{
        printf("\n*********************************************");
        printf("\n\t 1. Enqueue.");
        printf("\n\t 2. Dequeue.");
        printf("\n\t 3. Display the queue list.");
        printf("\n\t 4. Check if queue is empty.");
        printf("\n\t 0. Exit");
        printf("\n*********************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        switch(choice){
            case 1:
                printf("[1] What value do you want to insert? ");
                cin >> given;
                Enqueue(given);
                printf("[!] %d is inserted.", given);
                break;
            case 2:
                Dequeue(given);
                break;
            case 3:
                display();
                break;
            case 4:
                if(isEmpty()==1){
                    printf("[4] The queue list is empty!");
                }
                else{
                    printf("[4] The queue list is not empty!");
                }
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
