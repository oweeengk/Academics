/**
	A c/c++ source file normally starts with the include preprocessor directive. This file is "inserted” to the c/c++ source file making the functions in the included file visible/accessible to the source file. An "included” file may, of course, contain include preprocessor directives as well. The goal is to simply literally insert the contents of the included files in the c/c++ source file, replacing the preprocessor directives in the correct order. When a header file is included more than once, insert the first include and disregard the succeeding ones.
**/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void displayInclude(string);	//displayInclude function to display the contents of the said file.
vector<string> previous;    //initialize a string vector for the list of previously displayed lines (we use vectors because of the resizing factor over the arrays)

int main(){
    string fileName;
    cin >> fileName;
    displayInclude(fileName);	//call the function after opening the said file.
    
    return 0;
}

void displayInclude(string fileName){
    ifstream reader(fileName);	//input stream file to operate on files
    bool isHeader;	//boolean value for checking whether it is the Header of the file or not.
    
    if(reader.is_open()){
        string line;
        isHeader = false;
		
        while(getline(reader, line)){
            stringstream ss(line); //associates string line with a stream to read it as if it were a stream.
            string str;
            ss >> str;

            if(str.compare("#include") == 0){
                ss >> str;
                string f = str.substr(1,str.length()-2);
                if(find(previous.begin(), previous.end(), f) != previous.end()){	//traverses through the vector from beginning to end to check if the statement has been displayed before or not.
                    continue;
                }

                previous.push_back(f);	//adds the value of f (string) into the vector<string> for future purposes
                displayInclude(f);	//recursion of the displayInclude function passing in the arguments of string f.
                isHeader = true; 
            }
            
			if(!line.empty() && isHeader == false){	//checks if the line isn't empty, and whether it is not the header, it will skip the headers.
                cout << line << endl;
			}
            isHeader = false;
        }
        
    }
}
