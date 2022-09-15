// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordHelp(std::string in, std::string floating, const std::set<std::string>& dict, size_t num, std::set<std::string>& possibleWords);


std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> possibleWords;

    wordHelp(in, floating, dict, 0, possibleWords);

    return possibleWords;
}

void wordHelp(std::string in, std::string floating, const std::set<std::string>& dict, size_t num, std::set<std::string>& possibleWords){
    int chooser = 0;
    int dashAmt = 0;
    if(num == in.size()){ 
        if(floating.empty())
        chooser = 1;
    }
    //base case, check if words are in dictionary
    switch (chooser)
    {
    case 1:
        if(dict.find(in) != dict.end()){
            possibleWords.insert(in);
        }
        return; 
        break;
    }
    if(in[num] == '-'){
        chooser = 1;
    }
    else{
        chooser = 2;
    }
    //if the symbol is not a dash move forward one index
    switch (chooser)
    {
    case 2:
        wordHelp(in, floating, dict, num + 1, possibleWords);
        return;
        break;
    }

    //find amount of dashes in word
    for(size_t i = 0; i < in.size(); i++){
        if(in[i] == '-'){
            dashAmt++;
        }
    }
    string tempFloat = floating; 

    if(dashAmt > (int)tempFloat.size()){
        chooser = 3;
    }
    else if(dashAmt == (int)tempFloat.size()){
        chooser = 4;
    } 

    string temp;
    int chooser2;

    //see if the dash amount is greater than or equal to the amount of floating characters, do different things based on that
    switch (chooser)
    {
    case 3:
        // if more dashes than floating, test letters a-z to create list of possible words
        for(char i = 'a'; i<= 'z'; i++){
            if((int)tempFloat.find(i) == -1){
                chooser2 = 1;
            }
            else{
                chooser2 = 0;
            }
            switch (chooser2)
            {
            case 0:
                in[num] = i;
                temp = tempFloat;
                temp.erase(tempFloat.find(i), 1);
                wordHelp(in, temp, dict, num + 1, possibleWords);
                break;
            
            case 1:
                in[num] = i;
                wordHelp(in, tempFloat, dict, num + 1, possibleWords);
                break;
            }
        }
        break;
    case 4:
        //if same amount of dashes as floating, try floating characters in dash slots
        for(size_t i = 0; i < tempFloat.size(); i++){
            in[num] = tempFloat[i];
            temp = tempFloat;
            temp.erase(i, 1);
            wordHelp(in, temp, dict, num + 1, possibleWords);
        }
    }
}
    
    



