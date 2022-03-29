#include <iostream>

using namespace std;

struct Node{  //initializing the struct of each Node which contains the integer value (data) and Node ptr (next).
    int data;
    Node* next;
};

struct Node* head;

bool isEmpty(){ //function to check whether the linkedlist is empty using the head reference.
    if(head==NULL){
        return 1; //returns 1 as value for true (the linkedlist is empty).
    }
    else{
        return 0; //returns 0 as value for false (the linked list is not empty).
    }
}

bool doesNumExist(int data){ //function to check whether the number given by the user exists in the linked list.
    struct Node* temp;
    temp=head;
    int cont = 0; //integer cont 0 I use to stop the loop when the first occurence of data is in the linked list.
    while((temp!=NULL)&&(cont!=1)){ //traversing while loop to check each data inside the linked list.
        if(temp->data==data){ //integer cont usage: I used it as a flag to end the loop when the data exists in the linked list.
            cont=1;
        }
        temp=temp->next;
    }
    if(cont==1){ //return 1 if data existed in the linked list.
        return 1;
    }
    else{ //return 0 if the data didn't exist in the linked list.
        return 0;
    }
}

void createNode(int data){ //void function to create a Node and to link them accordingly to one another in the singly linked list.
    struct Node* temp;
    temp = new Node();
    temp->data = data;
    temp->next = head;
    head = temp;
}

void display(){ //void function to display/list the values in the linked list in a traversing manner.
    struct Node* temp;
    temp = head;
    if(isEmpty()==1){ //if statement created to check if the linked list is empty, there is nothing to display.
        printf("[!] Stack is empty, nothing to display!");
        return;
    }
    else{ //if the linked list is not empty, surely, there is something to display.
        printf("[3] ");
        while(temp!=NULL){ //traversing loop used to display each data in the linked list using a dynamic value for temp.
            cout << temp->data << "->";
            temp = temp->next;
        }
        printf("END"); //signify end of the linkedlist.
        return;
    }
}

void deleteNode(int data){ //void function created to delete a Node using the argument int data given by the user.
    struct Node* temp = head; //to initialize the node ptr temp.
    struct Node* prev; //to check the previous pointer of the node to be deleted (crucial for connecting the previous node and the next node).
    if(isEmpty()==1){ //if statement to check if the linkedlist is empty or not. It is to check if there is a linked list present in the first place.
        printf("\n[!] You cannot delete a node in an empty Node!");
        return;
    }
    else if(doesNumExist(data)==0){ //another if statement to check if the number given by the user (to be deleted) exists in the linked list in the first place.
        printf("\n[!] You cannot delete %d in the linked list because it doesn't exist!", data);
        return;
    }
    else{
        if(temp->data==data){ //in the case that the key to be deleted is the first data.
            head = temp->next; //changing the head ref for easier deletion.
            free(temp); //delete node temp.
            return;
        }
        else{ //in the case that it's not the first data to be deleted.
            while((temp!=NULL)&&(temp->data!=data)){ //while loop designed to check each data value in the linked list (to find the node to be deleted) and to keep track of the previous node.
                prev=temp; 
                temp=temp->next;
            }
            prev->next=temp->next; //once the data is found, the previous node's next ptr must be connected to the temp's nextptr to connect the linkedlist.
            free(temp); //delete node temp.
            return;
        }
    }
}

void getPos(int data){ //void function created to find the position of the data in the linked list.
    struct Node* temp=head; 
    int counter=0; //integer counter to get the position of the data using counter++ per traverse of the linkedlist.
    int cont=0; //same integer used to check whether the loop should continue or not.
    if(isEmpty()==1){ //if statement used to check whether the linked list is empty in the first plac
        printf("\n[!] You cannot find a node in an empty Node!");
        return;
    }
    else if(doesNumExist(data)==0){ //another if statement used to check whether the number to find actually exists in the linked list.
        printf("\n[!] You cannot find %d in the linked list because it doesn't exist!", data);
        return;
    }
    else{ //if the linked list is not empty and the number exists in the linked list.
        while((temp!=NULL)&&(cont!=1)){ //while loop that ends if the linked list has reached its end or the data value has been found.
            if(temp->data==data){ //if statement that changes the integer cont to 1 to signify that the data has been found the linkedlist, ending the loop.
                cont=1;
            }
            temp=temp->next; //dynamic changing of the value of temp to properly traverse through the linkedlist.
            counter++; //increasing value for counter for every travel of the nodes in the linked list.
        }
        if(cont==0){ //if somehow the data hasn't been found in the linked list.
            printf("\n[!] %d doesn't exist in the linked list!", data);
            return;
        }
        else{ //if the data has been found in the linkedlist.
            printf("\n[4] %d is in position %d", data, counter);
            return;
        }
    }
}

int main()
{
    head=NULL;
    int choice;
    int given;
    cout << "This program creates a singly linked list in C++ that can insert, delete, display, and check stack nodes.\n";
    do{
        printf("\n*********************************************");
        printf("\n\t 1. Insert a node.");
        printf("\n\t 2. Delete a node.");
        printf("\n\t 3. Show the list of the stack.");
        printf("\n\t 4. Find a node or data of the list");
        printf("\n\t 5. Ask if the stack is empty");
        printf("\n\t 0. Exit.");
        printf("\n*********************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        switch(choice){
            case 1:
                printf("[1] What value do you want to insert? ");
                cin >> given;
                createNode(given);
                printf("%d is inserted.", given);
                break;
            case 2:
                printf("[2] Which value do you want to delete? ");
                cin >> given;
                deleteNode(given);
                printf("%d is deleted.", given);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("[4] Which value do you want to find? ");
                cin >> given;
                getPos(given);
                break;
            case 5:
                if(isEmpty()==1){
                    printf("[5] The stack is empty!");
                }
                else{
                    printf("[5] The stack is not empty!");
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
