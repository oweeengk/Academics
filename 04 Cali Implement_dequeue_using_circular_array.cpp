#include <iostream>
#include <algorithm>

using namespace std;

#define defSize 5 //setting a default Array Size of 5 (just for initialization purposes)

int headRef; //global variable used to find the first element in the queue (front)
int tailRef; //global variable used to find the last element in the queue (rear)
int *array = new int[defSize]; //used to create an integer ptr for a new array containing the size of defSize (which starts at 5).
int dynSize=defSize; //dynSize is used to track whether the user wants to resize the array (dynamic size).
int arrCount; //used to count the elements in the array.

bool isEmpty(){ //boolean function used to return true or false whether the queue list is empty or not.
    if((headRef==-1)&&(tailRef==-1)){ //the queued list can only be empty if the first and last ptrs are empty.
        return true; 
    }
    else{
        return false;
    }
}

bool isFull(){ //boolean function used to return true or false whether the queue list is full or not.
    if((tailRef+1)%dynSize==headRef){ //circular array equation used to check if the last index when added to 1, modulo array size will yield the same value as the front reference. 
        return true; //meaning the array is full.
    }
    else{
        return false;
    }
}

void reSize(){ //void function used to reSize the array list.
    int newSize;
    do{ //do while statement that will continue to keep asking for a valid new size of the array length until the new array size given is deemed valid (must be greater than 0 and less than 10000).
        printf("[6] Please enter a valid new size for array length: ");
        cin >> newSize;
    }while((newSize<=0)||(newSize>1000)||(newSize<=dynSize));
    int *oldArray = array; //setting a new old array pointer for temporary array to store the old array.
    array = new int[newSize]; //used to create a new integer array with the given newSize by the user.
    for(int counter=0; counter<=dynSize; counter++){
        array[counter]=oldArray[counter];
    }
    printf("[!] Array is resized to %d from %d", newSize, dynSize);
    dynSize=newSize; tailRef=arrCount-1; headRef=0; //resetting the indexes and the value for the dynamic size.
    delete [] oldArray; //delete the old array.
}

void Enqueue(int data){ //void function used for enqueuing new data given by the user.
    if(isFull()){ //if the queue list is full, there's no more point in enqueuing because there's no more space.
        printf("[!] The queue is full! There is no more space for enqueuing.");
        return;
    }
    else{ //else statement if the queue is not full.
        if(headRef==-1){ //in the case that there is only 1 variable in the queue (headRef is considered -1 but tailRef isn't -1).
            headRef=0; //change the headRef ptr from NULL (-1) to 0 (a proper index value).
        } 
        tailRef=(tailRef+1)%dynSize; //circular queue equation to find the value of the index of the tailRef in a circular array.
        array[tailRef]=data; //input the data given by the user to the array with index of tailRef.
        printf("[!] %d is inserted.", data); //to signify that enqueuing was successful.
        arrCount++; //increment the number of elements in the array.
    }
}

void Dequeue(){ //void function used as dequeuing in the array.
    if(isEmpty()){ //if statement to catch if the queue is empty, there is nothing to dequeue.
        printf("[!] The queue is empty! There is nothing to duqueue.");
        return;
    }
    else{ //else statement if the queue is not empty.
        if(headRef==tailRef){ //in the case that there is only 1 variable.
            headRef=tailRef=-1; //set both the indexes into NULL (-1).
        }
        else{ //there are more than 1 variables.
            headRef=(headRef+1)%dynSize; //circular array queue equation used to find the index of headRef.
        }
        printf("[!] Queue is dequeued"); //used to signify success in dequeueing.
        arrCount--; //decrement the number of elements in the array.
    }
}

void displayQueue()//void function used to display the elements in the circular array queue.
{
    if(isEmpty()){ //if statement to catch when the queue is empty, there is nothing to display.
        printf("[!] The queue is empty! There is nothing to display.");
        return;
    }
        
    else{ //else statement to catch when the queue is not empty.
        int counter; 
        if(headRef<=tailRef){  //if there is atleast 0-1 elements to display.
            printf("[3] ");
            for(counter=headRef; counter<=tailRef; counter++){
                printf("%d ", array[counter]);
            }
        }
        else{ //else statement when there are many elements in the array.
            counter=headRef; //starting the counter to the headRef to signify that the printing starts at the index headRef
            printf("[3] ");
            while(counter<dynSize){ //while statement that continues to go on until the newSize/size of the array is reached.
                printf("%d ", array[counter]); //prints the values in the array
                counter++; //counter increment
            }
            counter=0; //restarts the value of the counter in case 
            while(counter<=dynSize){
                printf("%d ", array[counter]);
                counter++;
            }
        }
    }
}

int main(){
    headRef=-1; tailRef=-1; arrCount=0; //initializing the variables. -1 means NULL. 
    int choice;
    int given;
    cout << "This program creates a queue circular array in C++ that can resize, enqueue, dequeue, display, and check whether the queue list is empty or full\n";
    do{
        printf("\n*********************************************");
        printf("\n\t 1. Enqueue.");
        printf("\n\t 2. Dequeue.");
        printf("\n\t 3. Display the queue list.");
        printf("\n\t 4. Check if queue is empty.");
        printf("\n\t 5. Check if the queue is full.");
        printf("\n\t 6. Resize the array");
        printf("\n\t 7. Show size of the queue");
        printf("\n\t 8. Show front of the queue");
        printf("\n\t 0. Exit");
        printf("\n*********************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        switch(choice){
            case 1:
                printf("[1] What value do you want to insert? ");
                cin >> given;
                Enqueue(given);
                
                break;
            case 2:
                Dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                if(isEmpty()==true){
                    printf("[4] The queue list is empty!");
                }
                else{
                    printf("[4] The queue list is not empty!");
                }
                break;
            case 5:
                if(isFull()==true){
                    printf("[5] The queue list is full!");
                }
                else{
                    printf("[5] The queue list is not full!");
                }
                break;
            case 6:
                reSize();
                break;
            case 7:
                printf("[7] The size of the queue is: %d", arrCount);
                break;
            case 8:
                if(isEmpty()){
                    printf("[8] The queue is empty, there is no front variable!");
                }
                else{
                    printf("[8] The front of the queue is: %d", array[headRef]);
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
