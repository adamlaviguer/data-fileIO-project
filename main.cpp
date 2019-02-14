#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

//the PERSON struct
struct PERSON{
  char Name[20];
  float Balance;
};

void display(PERSON a[], int N, fstream &inData);
void findRichest(PERSON P[], int N);
void deposit(string custName, PERSON a[], int N, fstream &inData);
void newCopy(fstream &inData, PERSON a[], int N);

int main(){
  string line;
  int N=0;
  //defining an fstream object named "inData"
  fstream inData;
  //using the open function to open with two args: the txt file and the in flag to read the file
  inData.open("data.txt", ios::in);
  //check to see if the file is open
  if (!inData){
    //the file does not exist
    cout<<"ERROR: The file does not exist. Program ending.\n";
    return 0;
  }
  else{
    //the file DOES exist
    cout<<"The file opened successfully.\n";
    //read each line of the file into "line" and increment N until the end of the file
    while (getline(inData, line)){
      ++N;
    }
    cout<<"The number of items in the file has been recorded.\n";
  }
  //set the read position to the start of the file
  inData.close();
  inData.open("data.txt", ios::in | ios::out);
  //create the array to hold the data from the file
  PERSON P[N];
  //read data from the file into the array P of PERSON type
  string str1, str2;
  for (int i=0; i<N;i++){
    inData>>str1>>str2;
    inData>>P[i].Balance;
    string sName= str1+" "+str2;
    strcpy(P[i].Name, sName.c_str());
  }
  //copy PERSON P to PERSON a
  PERSON a[N];
  for (int i=0; i<N; i++){
    a[i]=P[i];
  }
  //call the display function
  display(a, N, inData);
  //call the findRichest function
  findRichest(P, N);
  //get deposit info
  cout<<"Enter your full name to deposit money: ";
  string custName;
  getline(cin, custName);
  //call the deposit function
  deposit(custName, a, N, inData);
  //call the copy function
  newCopy(inData, a, N);
  //close the file
  inData.close();
  return 0;
}
//the display function
void display(PERSON a[], int N, fstream &inData){
  //read data from the file into the array P of PERSON type
  cout<<"\n\tName\t\t\tBalance\n   ---------------------------------------------\n";
  for (int i=0; i<N;i++){
    cout<<"\t"<<a[i].Name<<"\t\t"<<fixed<<setprecision(2)<<a[i].Balance<<endl;
  }
}
//the findRichest function
void findRichest(PERSON P[], int N){
  float highest, lowest;
  int index=0;
  highest = lowest = P[0].Balance;
  for (int j=0; j<N;j++){
    if (P[j].Balance<lowest){
      lowest=P[j].Balance;
    }
    if (P[j].Balance>highest){
      highest=P[j].Balance;
      index=j;
    }
  }
  cout<<"\nThe customer with the largest balance is "<<P[index].Name<<".\n\n";
}
//the deposit function
void deposit(string custName, PERSON a[], int N, fstream &inData){
  cout<<custName<<", how much would you like to deposit? ";
  float depositAmount=0;
  cin>>depositAmount;
  cin.ignore();
  for (int i=0; i<N; i++){
    if (strcmp(a[i].Name, custName.c_str())==0){
      a[i].Balance += depositAmount;
      cout<<"Now your new balance is "<<a[i].Balance<<".\n";
    }
  }
}
//the newCopy function
void newCopy(fstream &inData, PERSON a[], int N){
  inData<<"\n\n-----------Here are the updated records-----------\n";
  for (int i=0; i<N; i++){
    inData<<a[i].Name<< " "<<a[i].Balance<<"\n";
  }
}