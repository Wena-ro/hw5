#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& input,
    std::string& curr,
    size_t index,
    const std::string& fLeft,
    const std::set<std::string>& dict, 
    std::set<std::string>& result, 
    size_t slotLeft);




// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::cout << "Input file: " << in << endl << "Floating num: " << floating << endl;

    std::set<std::string> result;

    std::string curr = in;

    size_t slotLeft = 0;
    for(size_t i = 0; i < in.size(); i++){
        if(in[i] == '-'){
            slotLeft++;
        }
    }

    wordleHelper(in, curr, 0, floating, dict, result, slotLeft);

    return result;

}

// Define any helper functions here

void wordleHelper(
    const std::string& input,
    std::string& curr,
    size_t index,
    const std::string& fLeft,
    const std::set<std::string>& dict, 
    std::set<std::string>& result, 
    size_t slotLeft)
{
    

    // Cut branch if the rest of slot is not enough for floating
    if(fLeft.size() > slotLeft){
      return;
    }  

    // Base case, if all letters are checked
    // Check if floating is empty
    // If empty, check if word is valid
    // If valid, put it into result and return
    if(index == input.size()){
        if(fLeft.empty()){
            if(dict.count(curr)){
                result.insert(curr);

            }
        }
        return;
    }

    // Check if current character is '-'
    // If not, continue into recurrsion

    if(input[index] != '-'){
        char currChar = input[index];
        curr[index] = currChar;

        wordleHelper(input, curr, index+1, fLeft, dict, result, slotLeft);
    }


    // If current character is '-'
    // Check if the rest of slot was only enough to input floating characters
    // If yes, only use the floating characters for recurrsion
    else{
        size_t floatLeft = fLeft.size();

        if(slotLeft == floatLeft){
            
            for(size_t i = 0; i < fLeft.size(); i++){
                char c = fLeft[i];
                curr[index] = c;

                std::string fNext = fLeft;
                fNext.erase(i,1);

                wordleHelper(input, curr, index+1, fNext, dict, result, slotLeft-1);
            }
            return;
        }
    // If slot is more than floating character, implement from a to z
    // If current input is floating, delete floating
    // Pass rest to recurrsion

        for(char c = 'a'; c <= 'z'; c++){
            curr[index] = c;

            std::string fNext = fLeft;

            size_t pos = fNext.find(c);
            if(pos != std::string::npos){
                fNext.erase(pos,1);
            }

            wordleHelper(input, curr, index+1, fNext, dict, result, slotLeft-1);
        }
    }
}