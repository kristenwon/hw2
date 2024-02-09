#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
set<string> parseStringToWords(string rawWords)
{
    // make set to return
    set<string> wordSet;
    string indivWord = "";
    for(size_t i=0; i < rawWords.size(); i++){
        // if the character is alphanumeric
        if(isalnum(rawWords[i])){
            // add the character to the string
            indivWord.push_back(rawWords[i]);
        }
        // if the character is punct or space
        else {
            if(indivWord.size() > 1){
                wordSet.insert(convToLower(indivWord));
            }
            indivWord = "";
        }
    }
    // gets the last keyword
    if(indivWord.size() > 1){
        wordSet.insert(convToLower(indivWord));
    }
    return wordSet;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
