#include <iostream>
#include <string.h>
#include <stdio.h>
#include <limits.h>

using namespace std;


/**
*    Requirement 8:
*    Create a hash table of a student enrollment system in an elementary school where data contain family
*    name, first name, middle name, age, gender, id number, contact number, and address. Illustrate your
*    work just like the illustration in this topic.
*    Due Date: 18 Nov 2020
* 
*    by Cali
* 
* 
**/
class Student{ // for every directory in Student class, contains family name, firstname, middlename, age, gender, studentnumber, contactnumber, and address values.
    private:
        string familyName;
        string firstName;
        string middleName;
        int age;
        string gender;
        int studentNumber;
        string contactNumber;
        string address;
    
    public:
        Student(int studentNum, string _familyName, string _firstName, int _age, string _gender, string _middleName ="", string _contactNumber = "", string _address =""): studentNumber(studentNum), familyName(_familyName), firstName(_firstName), age(_age), gender(_gender), middleName(_middleName), contactNumber(_contactNumber), address(_address){}
        string getFamilyName(){
            return familyName;
        }
        string getFirstName(){
            return firstName;
        }
        string getMiddleName(){
            return middleName;
        }
        int getAge(){
            return age;
        }
        string getGender(){
            return gender;
        }
        string getContactNumber(){
            return contactNumber;
        }
        string getAddress(){
            return address;
        }
        int getStudentNumber(){
            return studentNumber;
        }
        void setFamilyName(string givenFamilyName){
            familyName=givenFamilyName;
        }
        void setFirstName(string givenFirstName){
            firstName=givenFirstName;
        }
        void setMiddleName(string givenMiddleName){
            middleName=givenMiddleName;
        }
        void setContactNumber(string givenContactNumber){
            contactNumber=givenContactNumber;
        }
        void setAddress(string givenAddress){
            address=givenAddress;
        }
        void setAge(int givenAge){
            age=givenAge;
        }
        void setGender(string givenGender){
            gender=givenGender;
        }
        void setStudentNumber(int givenStudentNumber){
            studentNumber=givenStudentNumber;
        }
    
};

class Node: public Student{ //Node pointing to directory Student. It contains dataID and ptr for nextNode.
    private:
        int dataID;
        Node* nextNode = NULL;
    public:
        Node(int dataId, int studNum, string _familyName, string _firstName, int _age, string _gender, string _middleName ="", string _contactNumber = "", string _address ="") : Student(studNum, _familyName, _firstName,_age, _gender,  _middleName, _contactNumber, _address), dataID(dataId){}
        
        Node* getNext(){
            return nextNode;
        }
        int getDataID(){
            return dataID;
        }
        void setNext(Node* givenNext){
            nextNode=givenNext;
        }
};

class HashTable{ //Hashtable class with defined TABLE_SIZE of 25, dynamic studentCount and studentNumber, along with pointer to pointer table.
    private:
        int TABLE_SIZE=25;
        Node **table;
        int studentCount=0;
        int studentNumber=1;
    
    public:
        HashTable(){
            table=new Node*[TABLE_SIZE]();
            for(int counter=0; counter<TABLE_SIZE; counter++){
                *(table+counter)=NULL;
            }
        }      
        int hash(string key){
            int hashValue=0;
            for(int i=0; i<key.length(); i++){
                if((key[i]>= 'a')&&(key[i]<= 'z')){
                    key[i]-=32;
                } 
            }
            for(int i=0; i<key.length(); i++){
                hashValue+=key[i];
            }
            return hashValue;
        }
        int hashMap(int hashKey){
            int hashMapIndex=hashKey%TABLE_SIZE;
            return hashMapIndex;
        }
        void displayTable(){
            if(studentCount==0){
                cout << "[DataDisplay] Hash Table is empty.\n[DataDisplay] Nothing to display here." << endl;
                return;
            }
            cout << "[DataDisplay] ";
            for(int i=0; i<TABLE_SIZE; i++){
                cout << "Table[" << i << "]: ";
                if(table[i] == NULL){
                    cout << "Empty" << endl;
                } else{
                    Node *temp=table[i];
                    do{
                        cout << "\n\tData ID:\t" << temp->getDataID() << endl;
                        cout << "\tStudent Number:\t" << temp->getStudentNumber() << endl;
                        cout << "\tFamily Name:\t" << temp->getFamilyName() << endl;
                        cout << "\tFirst Name:\t" << temp->getFirstName() << endl;
                        cout << "\tMiddle Name:\t" << temp->getMiddleName() << endl;
                        cout << "\tAge:\t\t" << temp->getAge() << endl;
                        cout << "\tGender:\t\t" << temp->getGender() << endl;
                        cout << "\tContact Number:\t" << temp->getContactNumber() << endl;
                        cout << "\tAddress:\t" << temp->getAddress() << endl; 
                        temp=temp->getNext();

                    }while(temp!=NULL);
                }
            }
        }
    
        void insertData(string familyName, string firstName, string middleName, string contactNumber, string address, int age, string gender){
            int dataID=hash(familyName);
            int position=hashMap(dataID);
            if(table[position]==NULL){
                table[position]=new Node(dataID, studentNumber++, familyName, firstName, age, gender, middleName, contactNumber, address);
            } 
            else{
                Node *temp=table[position];
                while(temp->getNext()!=NULL){
                    temp = temp->getNext();
                }
                Node *newNode = new Node(dataID, studentNumber++, familyName, firstName, age, gender, middleName, contactNumber, address);
                temp->setNext(newNode);
            }
            cout << "\n[DataInsertion] Data is inserted at index: " << position << endl;
            studentCount++;
        }
        
        Node *find(string key, int studentNumber=-1){ // understand, edit
            int dataID = hash(key);
            int position = hashMap(dataID);
            Node* temp = table[position];
            while(temp!=NULL){
                if(temp->getDataID() == dataID){
                    if(studentNumber != -1){
                        if(temp->getStudentNumber() == studentNumber){
                            return temp;
                        } else {
                            temp = temp->getNext();
                            continue;
                        }
                    } else {
                        return temp;
                    }
                }
                temp = temp->getNext();
            }
            return temp;
        }
        void deleteData(string key){ //edit, understand
            Node *toDelete = find(key);
            if(studentCount==0){
                cout << "[DataDeletion] Hash Table is empty.\n[DataDeletion] Nothing to delete here." << endl;
                return;
            }
            else if(toDelete==NULL){
                printf("[DataDeletion] Data doesn't exist.");
                return;
            }
            int dataID = hash(key);
            int position = hashMap(dataID);
            Node* binNode = table[position];
            if(binNode == toDelete){
                    table[position] = toDelete->getNext();
            } else {
                while(binNode->getNext() != toDelete){
                    binNode = binNode->getNext();
                }
                binNode->setNext(toDelete->getNext());
            }
            printf("[DataDeletion] Data ID: %d is deleted.", dataID);
            delete toDelete;
            studentCount--;
        }
        
        void updateData(string key){
            int dataID = hash(key);
            int position = hashMap(dataID);
            Node* current = table[position];
            Node* temp = find(key);
            
            if(studentCount==0){
                cout << "[DataUpdate] Hashmap is empty, nothing to search." << endl;
                return;
            }
            else if(temp==NULL){
                cout << "[DataUpdate] Given family name does not exist!" << endl;
                return;
            }
            else{
                string familyName; string firstName; string middleName; string contactNumber; string address; string gender;
                int age;
                cout << "[DataUpdate] Current:" << endl;
                int studentNumber = temp->getStudentNumber();
                cout << "\t[Current] Data ID:\t\t" << temp->getDataID() << endl;
                cout << "\t[Current] Student Number:\t" << temp->getStudentNumber() << endl;
                cout << "\t[Current] Family Name:\t\t" << temp->getFamilyName() << endl;
                cout << "\t[Current] First Name:\t\t" << temp->getFirstName() << endl;
                cout << "\t[Current] Middle Name:\t\t" << temp->getMiddleName() << endl;
                cout << "\t[Current] Age:\t\t\t" << temp->getAge() << endl;
                cout << "\t[Current] Gender:\t\t" << temp->getGender() << endl;
                cout << "\t[Current] Contact Number:\t" << temp->getContactNumber() << endl;
                cout << "\t[Current] Address:\t\t" << temp->getAddress() << endl;
                cout << "\t[DataUpdate] New Data: " << endl;
                cout << "\t[New] Student Number: " << temp->getStudentNumber() << endl;
                cout << "\t[New] Please enter new family name: ";
                getline(cin, familyName);
                cout << "\t[New] Please enter new first name: ";
                getline(cin, firstName);
                cout << "\t[New] Please enter new middle name: ";
                getline(cin, middleName);
                cout << "\t[New] Please enter new gender: ";
                getline(cin, gender);
                cout << "\t[New] Please enter new contact number: ";
                getline(cin, contactNumber);
                cout << "\t[New] Please enter new address: ";
                getline(cin, address);
                cout << "\t[New] Please enter new age: ";
                cin >> age;
                
                deleteData(key);
                insertData(familyName, firstName, middleName, contactNumber, address, age, gender);
                
            }
        }
        
        void search(string key){
            int dataID=hash(key);
            int position = hashMap(dataID);
            Node* temp = table[position];

            if(studentCount==0){
                cout << "[DataSearch] Hashmap is empty, nothing to search." << endl;
                return;
            }
            else{
                if(temp==NULL){
                    cout << "[DataSearch] Data given does not exist in the hash map!" << endl;
                    return;
                }
                cout << "\nData ID:\t" << temp->getDataID() << endl;
                cout << "Student Number:\t" << temp->getStudentNumber() << endl;
                cout << "Family Name:\t" << temp->getFamilyName() << endl;
                cout << "First Name:\t" << temp->getFirstName() << endl;
                cout << "Middle Name:\t" << temp->getMiddleName() << endl;
                cout << "Age:\t\t" << temp->getAge() << endl;
                cout << "Gender:\t\t" << temp->getGender() << endl;
                cout << "Contact Number:\t" << temp->getContactNumber() << endl;
                cout << "Address:\t" << temp->getAddress() << endl;
            }
        }   
};

int main(){
    int age; string familyName=""; string firstName=""; string middleName=""; string contactNumber=""; string address=""; string gender="";
    HashTable *table = new HashTable();
    bool cont=true; int choice;
    
    do{
        printf("\n\t\t\t\t   H A S H - M A P\t\t\t");
        printf("\n\t\t*************************************************");
        printf("\n\t\t*\t\t (1) Insert data\t\t*");
        printf("\n\t\t*\t\t (2) Delete data\t\t*");
        printf("\n\t\t*\t\t (3) Show data\t\t\t*");
        printf("\n\t\t*\t\t (4) Update data\t\t*");
        printf("\n\t\t*\t\t (5) Find data\t\t\t*");
        printf("\n\t\t*\t\t (0) Exit.\t\t\t*");
        printf("\n\t\t*************************************************");
        printf("\nEnter choice: ");
        cin >> choice;
        cin.ignore(1,'\n');
        switch(choice){
            case 0:
                printf("[0] Program terminated.");
                delete table;
                break;
            case 1:
                cout << "[DataInsertion] Please enter last name: ";
                getline(cin, familyName);
                printf("[DataInsertion] Please enter first name: ");
                getline(cin, firstName);
                printf("[DataInsertion] Please enter middle name: ");
                getline(cin, middleName);
                printf("[DataInsertion] Please enter contact number: ");
                getline(cin, contactNumber);
                printf("[DataInsertion] Please enter address: ");
                getline(cin, address);
                printf("[DataInsertion] Please enter gender: ");
                getline(cin, gender);
                printf("[DataInsertion] Please enter age: ");
                cin >> age;
                table->insertData(familyName, firstName, middleName, contactNumber, address, age, gender);
                break;
            case 2:
                printf("[DataDeletion] Please enter family name to be deleted: ");
                getline(cin, familyName);
                table->deleteData(familyName);
                
                break;
            case 3:
                table->displayTable();
                break;
            case 4:
                printf("[DataUpdate] Please enter family name to be updated: ");
                getline(cin, familyName);
                table->updateData(familyName);
                break;
            
            case 5:
                printf("[DataSearch] Please enter family name to be searched: ");
                getline(cin, familyName);
                table->search(familyName);
                break;

            default:
                printf("[!] Given number is not within the choices!");
                break;
        }
    }while(choice!=0);
    

    return 0;
}
