/*
Michael kulinich
2328386
kulinich@chapman.edu
CPSC350-01
Assignment 3
This assignment analyzes a code file and
checks if all the delimiters are correct
*/

#include "GenStack.h"
#include <iostream>
#include <fstream>

using namespace std;

//this method looks for he delimiters inside of the file
//this switch statement looks at the character i in the line
//and looks for each delimiter. if its an opening delimiter
//then it will be pushed to a stack
//if it is a closing delimiter, then it will be compared to the top of the stack
//if the stack is empty or the top of the stack doesnt match the closing delimiter,
// then the program ends and cout the location of the error in the file.
//else pop the stack
void findDelimiter(string& line, GenStack<char>& myStack, int& lineCount, ifstream& inFile);

int main(int argc, char const *argv[]) {

  ifstream inFile;
  string inputFile;
  string anotherFile = "n";//Used for loop control if user wants to check another file
  string line; //iterate linke by line through file
  int lineCount = 1; //count what line the reader is on
  inputFile = argv[1];
  GenStack<char> myStack(10);

  //while loop to ask user if they want to run another test
  while(true)
  {
        //if this is the first file user opens from commandline
        //then open the command lined argument file to read
        if(anotherFile == "n"){
         inFile.open(inputFile);// open the command lined argument file to read
        }
        //if the user has already opened the file through command line
        //then ask for the name of their file
        if(anotherFile == "y"){
          cout << "Enter a proper file name('exit' to exit): " << endl;
          cin >> inputFile;
          if(inputFile == "exit"){
            exit(1);
          }
          inFile.open(inputFile);
        }

        //while loop to make sure user enters proper file name
        while(true)
        {
            if(!inFile)
            {
              cout << "unable to open file: " << inputFile << endl;
              cout << "Enter a proper file name('exit' to exit): " << endl;
              cin >> inputFile;
              if(inputFile == "exit"){
                exit(1);
              }
              inFile.open(inputFile);
            }
            //the file was able to open
            else
            {
              break;
            }
        }


    //read line by line from the file
    while (getline(inFile, line))
    {
      findDelimiter(line, myStack, lineCount, inFile);
      lineCount++;
     }



     //if the stack is empty than the file is good.
     //Also check if user wants to input another file
      if(myStack.isEmpty()){
        cout << "The file " << inputFile << " is good." << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "Would you like to read another file?('y' yes. 'no' no)" << endl;
        cin >> anotherFile;
        lineCount = 1;
        inFile.close();
        //if the user wants to enter another file, the while loop will
        //itterate again. If the user says no, the program ends
        if(anotherFile != "y"){
          inFile.close();
          exit(1);
        }
      }
      //the stack is not empty so there is an error mostlikely at the end
      //of the file, it would be an extra opening delimiter
      else
      {
        cout << "NOT GOOD. reached the end of file and there is an" << endl;
        cout << "Extra " << myStack.pop() << " on line " << --lineCount << endl;
        inFile.close();
        exit(1);
      }
    }
  return 0;
}

void findDelimiter(string& line, GenStack<char>& myStack, int& lineCount, ifstream& inFile){
    //go character by character per each line
    for(int i = 0; i < line.size(); ++i){

        switch(line[i]){
          case '[':
            myStack.push('[');
            break;
          case '(':
            myStack.push('(');
            break;
          case '{':
            myStack.push('{');
            break;

          case ']':
            if(myStack.isEmpty()){
              cout << "error on line: " << lineCount << ", extra ]" << endl;
              inFile.close();
              exit(1);
            }
            if(myStack.peek() != '['){
              cout << "error on line: " << lineCount <<  endl;
              cout << "] is not the proper closer for " << myStack.pop() << endl;
              inFile.close();
              exit(1);
            }
            myStack.pop();
            break;

          case ')':
            if(myStack.isEmpty()){
              cout << "error on line: " << lineCount << ", extra )" << endl;
              inFile.close();
              exit(1);
            }
            if(myStack.peek() != '('){
              cout << "error on line: " << lineCount <<  endl;
              cout << ") is not the proper closer for " << myStack.pop() << endl;
              inFile.close();
              exit(1);
            }
            myStack.pop();
            break;


          case '}':
            if(myStack.isEmpty()){
              cout << "error on line: " << lineCount << ", extra }" << endl;
              inFile.close();
              exit(1);
            }
            if(myStack.peek() != '{'){
              cout << "error on line: " << lineCount <<  endl;
              cout << "} is not the proper closer for " << myStack.pop() << endl;
              inFile.close();
              exit(1);
            }
            myStack.pop();
            break;
          default:
            break;
          }
    }
}
