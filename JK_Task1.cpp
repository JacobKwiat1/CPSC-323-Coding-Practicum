/* Design and implement a Lexical Analyzer (DFA) that accepts strings over ∑ = {0,1} that contain "1011".
• Valid Strings: 001011, 10110, 1110111
• Invalid Strings: 101, 0000, 1001*/

#include <iostream>
#include <array>
#include <vector>
#include <sstream>
#include <queue>
#include <string>
class LexicalState {
    LexicalState* next[2];
    bool valid = false;
public: 
    //constructors
    LexicalState() {
        next[0] = nullptr;
        next[1] = nullptr;
    }
    LexicalState(std::array<LexicalState*, 2> state, bool valid) {
        changeNext(state);
        this->valid = valid;
    }
    LexicalState(std::array<LexicalState*, 2> state) {
        changeNext(state);
    }
    
    //modifiers
    void changeNext(std::array<LexicalState*, 2> state) {
        next[0] = state[0];
        next[1] = state[1];
    }
    void changeValid() {
        valid = !valid;
    }
    //accessors
    LexicalState* getNext(int input) { 
        return next[input];
    }
    bool isValid() {
        return valid;
    }

    //methods
    bool analyze(std::vector<int> input) { //set up for analysis, should only be called from starting state
        LexicalState* current = this;
        for(int i=0;i<input.size();++i) {
            current = current->getNext(input[i]);
        }
        return current->isValid();
    }
};

int main() {
    //creating states
    LexicalState A, B, C, D, E;
    B.changeNext({&C, &B});
    C.changeNext({&A, &D});
    A.changeNext({&A, &B});
    D.changeNext({&A, &E});
    E.changeNext({&E, &E});
    E.changeValid();

    //take input
    std::cout << "enter string of '1's and '0's (separated by spaces): ";
    std::string input;
    std::getline(std::cin, input);
    std::istringstream stream(input);
    std::vector<int> arr;
    int num;
    //put input into vector for analysis
    for (char c : input) {
            arr.push_back(c - '0'); 
    }

    //analyze and output
    if(A.analyze(arr)) {
        std::cout << "ACCEPTED";
    } else {
        std::cout << "REJECTED";
    }
}