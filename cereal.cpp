#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Cereal{
  enum {MAX_CHAR_LEN=100};
  char Name[MAX_CHAR_LEN];
  double calories;
  double protien;
  double fat;
  double sodium;
  double fiber;
  double carbs;
  double sugar;
  double serving;
  bool valid;
  Cereal();
};

Cereal::Cereal(){
  for(int i = 0; i < MAX_CHAR_LEN; i++){
    Name[i] = '\0';
  }
  calories = 0;
  protien = 0;
  fat = 0;
  sodium = 0;
  fiber = 0;
  carbs = 0;
  sugar = 0;
  serving = 0;
  valid = false;
}

const int MAX_CEREAL=500;
Cereal readCereal(ifstream &inFile){
    Cereal cereals; 
    inFile.get(cereals.Name, Cereal::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> cereals.calories;
    inFile.ignore(100,';');
    inFile >> cereals.protien;
    inFile.ignore(100,';');
    inFile >> cereals.fat;
    inFile.ignore(100,';');
    inFile >> cereals.sodium;
    inFile.ignore(100,';');
    inFile >> cereals.fiber;
    inFile.ignore(100,';');
    inFile >> cereals.carbs;
    inFile.ignore(100,';');
    inFile >> cereals.sugar;
    inFile.ignore(100,';');
    inFile >> cereals.serving;
    inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
    cereals.valid = !inFile.eof();
    return cereals;
}

int readCereals(Cereal cereals[]) {
    ifstream cerealFile("cereal.txt");
    int numCereal = 0;
    while(cerealFile.peek() != EOF && numCereal < MAX_CEREAL) {
        cereals[numCereal] = readCereal(cerealFile);
        numCereal++;
    }
    return numCereal;
}

int print(ostream &out, Cereal cereals[], int indexCereal) {
  //char charTemp[100];
  //setCharArray(charTemp);
  //if(cereals[indexCereal].valid == false){
  //  return 0;
  //}
  //cout << "Index " << indexCereal << ": ";
  int temp = 0;
  while(cereals[indexCereal].Name[temp] != '\0') {
    out << cereals[indexCereal].Name[temp];
    //charTemp[temp] += cereals[indexCereal].Name[temp];
    temp++;
  }
  //charTemp += ';';
  //charTemp += ';' + cereals[indexCereal].calories + ';' + cereals[indexCereal].protien + ';' + cereals[indexCereal].fat + ';' + cereals[indexCereal].sodium + ';' + cereals[indexCereal].fiber + ';' + cereals[indexCereal].carbs + ';' + cereals[indexCereal].sugar + ';' + cereals[indexCereal].serving;
  
  out << ";" << cereals[indexCereal].calories << ";" << cereals[indexCereal].protien << ";" << cereals[indexCereal].fat << ";" << cereals[indexCereal].sodium << ";" << cereals[indexCereal].fiber << ";" << cereals[indexCereal].carbs << ";" << cereals[indexCereal].sugar << ";" << cereals[indexCereal].serving << ";";
  
  //return charTemp;
  return 0;
}

void printArrayToScreen(Cereal temp[], int numCereal) {
  for (int index = 0; index < numCereal; index++) {
        cout << "Index " << index << ": ";
        print(cout, temp, index);
        cout << endl;
    }
}

void printArrayIndexToScreen(Cereal temp[], int numCereal) {
  print(cout, temp, numCereal);
}

void printArrayToFile(const char fileName[], Cereal examples[], int numExamples) {
    ofstream outFile(fileName);
    for (int index = 0; index < numExamples; index++) {
        print(outFile, examples, index);
        outFile << endl;
    }
}

int readCharArray(const char prompt[], char Name[]){
  char temp[100];
  int index = 0;
  do{
    cout << prompt;
    cin >> temp;
    while(temp[index] != '\0'){
      index++;
    }
  }
  while(index > 100);
  strcpy(Name, temp);
  return 0;
}

int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
      cin.clear();
      cin.ignore(1000,'\n');
      cout << "Invalid Data!" << endl;
      cout << prompt;
      cin >> temp;
    }
    return temp;
}

double readDouble(const char prompt[]){
    double temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

void addNewEntry(Cereal cereals[], int arrtemp){
  char name[100];
  cin.ignore(100,'\n');
  readCharArray("Name: ", name);
  strcpy(cereals[arrtemp].Name, name);
  cereals[arrtemp].calories = readDouble("Calories: ");
  cereals[arrtemp].protien = readDouble("Protien: ");
  cereals[arrtemp].fat = readDouble("Fat: ");
  cereals[arrtemp].sodium = readDouble("Sodium: ");
  cereals[arrtemp].fiber = readDouble("Fiber: ");
  cereals[arrtemp].carbs = readDouble("Carbs: ");
  cereals[arrtemp].sugar = readDouble("Sugar: ");
  cereals[arrtemp].serving = readDouble("Serving: ");
}

void removeEntry(Cereal cereals[], int arrtemp, int pos){
  for(int index = 0; index < 100; index++){
    cereals[pos].Name[index] = '\0';
  }
  cereals[pos].calories = '\0';
  cereals[pos].protien = '\0';
  cereals[pos].fat = '\0';
  cereals[pos].sodium = '\0';
  cereals[pos].fiber = '\0';
  cereals[pos].carbs = '\0';
  cereals[pos].sugar = '\0';
  cereals[pos].serving = '\0';
  
  for(int count = pos; count < arrtemp; count++){
    cereals[count] = cereals[count+1];
  }
}

int setCharArray(char temp[]){
  for (int index = 0; index < MAX_CEREAL; index++) {
        temp[index] = '\0';
    }
    return 0;
}

int main(){
  Cereal cereals[MAX_CEREAL];
  int arrtemp = readCereals(cereals);
  int input;

while (true){
  input = readInt("1.Reload database from the file\n2.Print Cereal\n3.Add new entry\n4.Remove entry\n5.Print all Cereals\n6.Save database to the file\n7.Quit\n\nEnter a Number: ");

  if(input == 1){
    arrtemp = readCereals(cereals);
    cout << endl;
  }
  if(input == 2){
    cout << endl;
    printArrayIndexToScreen(cereals, readInt("Enter an Index: "));
    cout << endl << endl;
  }
  if(input == 3){
    addNewEntry(cereals, arrtemp);
    arrtemp++;
    cout << endl;
  }
  if(input == 4){
    removeEntry(cereals, arrtemp, readInt("Enter an Index: "));
    arrtemp--;
    cout << endl;
  }
  if(input == 5){
    printArrayToScreen(cereals, arrtemp);
    cout << endl;
  }
  if(input == 6){
    printArrayToFile("cereal.txt", cereals, arrtemp);
    cout << endl;
  }
  if(input == 7){
    return 0;
  }
}
  
  return 0;
}