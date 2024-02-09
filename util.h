#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    // make set to return
    typename std::set<T> intSet;
    // iterate thru set 1
    for(typename std::set<T>::iterator it=s1.begin(); it != s1.end(); ++it){
        // if current item in set 1 is also in set 2 add it to the temp set
        if(s2.find(*it) != s2.end()){
            intSet.insert(*it);
        }
    }
    return intSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // make temp set a copy of s1
    typename std::set<T> unionSet = s1;
    // iterate thru set 2
    for(typename std::set<T>::iterator it=s2.begin(); it != s2.end(); ++it){
        // if the current item in set 2 does not exist in unionSet add it
        if(unionSet.find(*it) == unionSet.end()){
            unionSet.insert(*it);
        }
    }
    return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
