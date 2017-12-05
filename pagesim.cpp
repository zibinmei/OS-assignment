#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;


void main (){
    int FRAME_SIZE = 4;


    return;
}



vector<int> userInput() {
    vector<int> vec;
    string userString;

    getline (cin, userString);
    istringstream iss(userString);

    while (iss) {
       string word;
       iss >> word;
       int x = stoi(word);
       vec.push_back(x);
    }

    return vec;
}
