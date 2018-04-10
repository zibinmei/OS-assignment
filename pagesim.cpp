#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>
#include <algorithm>

using namespace std;
const int FRAME_SIZE = 4;

vector<int> userInput();
bool inFrame(int, vector<int>);
void optimal(vector<int>);
void lru(vector<int>);
void clockA(vector<int>);


int main (){
    vector<int> input = userInput();
    cout << "Optimal: " << endl;
    optimal(input);
    cout << "LRU: " <<endl;
    lru(input);
    cout << "Clock: "<<endl;
    clockA(input);
    return 0;
}



vector<int> userInput() {
    vector<int> vec;
    string userString;

    getline (cin, userString);
    istringstream iss(userString);
    do {
        try{
            string word;
            iss >> word;
            int x = stoi(word);
            vec.push_back(x);
           }
           catch(exception& e){

           }
       }while(iss);

    return vec;
}

bool inFrame(int x, vector<int> frame){
    for (int i= 0; i < frame.size(); i ++){
        if (frame[i] == x){
            return true;
        }
    }
    return false;
}

void optimal(vector<int> input){
    vector<int> frame;
    int pageFault =0;
    //for every thing in input
    for (int i = 0; i <input.size(); i++ ){
        int x = input[i];
        //if the input is not in frame do change
        if (inFrame(x, frame) == false){
            if (frame.size() < FRAME_SIZE){
                frame.push_back(x);
                pageFault ++;
                continue;
            }

            //look for changable index
            vector<int> changable;
            //look into the future
            for (int j = i+1; j < input.size(); j++){
                if (changable.size() == FRAME_SIZE){
                    break;
                }

                //use to single out the least use page
                for (int k = 0; k < frame.size(); k++){
                    if (input[j] == frame[k]){
                        if (find(changable.begin(),changable.end(),k) != changable.end() == false){
                            changable.push_back(k);
                            break;
                        }
                    }
                }
            }

            //found the one page that need to kick cout

            int cIndex ;
            if (changable.size() == FRAME_SIZE)
                cIndex = changable.back();
            else{
                for (int i = 0 ; i < FRAME_SIZE; i++){
                    if (find(changable.begin(),changable.end(),i) != changable.end() == false){
                        cIndex = i;
                        break;
                    }
                }
            }
            frame[cIndex] = x;
            pageFault ++;
        }


    }
    //print out
    cout << "\t - frames: ";
    for (int k = 0; k < frame.size(); k++){
        cout << frame[k] << " ";
    }
    cout << endl;
    cout << "\t - page faults: " << pageFault << endl;
}


void lru(vector<int> input){
    vector<int> frame;
    int pageFault =0;
    //for every thing in input
    for (int i = 0; i <input.size(); i++ ){
        int x = input[i];
        //if the input is not in frame do change
        if (inFrame(x, frame) == false){
            if (frame.size() < FRAME_SIZE){
                frame.push_back(x);
                pageFault ++;
                continue;
            }
            frame.erase(frame.begin() );
            frame.push_back(x);
            pageFault++;

        }
        //this x is in frame so take it out put it to the back
        else{
            int indexTO;
            for (int k = 0; k < frame.size();k++){
                if (frame[k] == x){
                    indexTO = k;
                    break;
                }
            }
            frame.erase(frame.begin() + indexTO);
            frame.push_back(x);


        }
    }
    //print out
    cout << "\t - frames: ";
    for (int k = 0; k < frame.size(); k++){
        cout << frame[k] << " ";
    }
    cout << endl;
    cout << "\t - page faults: " << pageFault << endl;
}

void clockA(vector<int> input){
    vector<int> frame;
    int refBit[FRAME_SIZE];
    int refPtr = 0;

    int pageFault =0;
    //for every thing in input
    for (int i = 0; i <input.size(); i++ ){
        int x = input[i];
        if (refPtr == FRAME_SIZE)
            refPtr =0;
        if (inFrame(x, frame) == false){
            if (frame.size() < FRAME_SIZE){
                frame.push_back(x);
                refBit[refPtr] = 1;
                refPtr++;
                pageFault ++;
                continue;
            }
            bool flag = true;
            while (flag){
                if (refPtr == FRAME_SIZE)
                    refPtr =0;
                //if the ref bit is 0 set the frame
                if (refBit[refPtr] == 0){
                    frame[refPtr] =x;
                    refBit[refPtr] =1;
                    refPtr++;
                    pageFault++;
                    flag = false;
                }
                else{
                    refBit[refPtr] =0;
                    refPtr ++;
                }
            }
        }
        //if is in frame set itsref bit to 1
        else{
            int setIndex;
            for (int i = 0 ; i < frame.size(); i++){
                if (frame[i] == x){
                    setIndex =i;
                    break;
                }
            }
            refBit[setIndex] =1;
        }


    }

    //print out
    cout << "\t - frames: ";
    for (int k = 0; k < frame.size(); k++){
        cout << frame[k] << " ";
    }
    cout << endl;
    cout << "\t - page faults: " << pageFault << endl;
}
