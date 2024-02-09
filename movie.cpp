#include "movie.h"
#include <sstream>
#include <iomanip>
#include "iostream"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie() { }

string Movie::getGenre() const
{
    return genre_;
}

string Movie::getRating() const
{
    return rating_;
}

set<string> Movie::keywords() const{
    set<string> tempkeywords;
    set<string> nameSet = parseStringToWords(name_);
    set<string> genreSet = parseStringToWords(genre_);
    for(set<string>::iterator it=nameSet.begin(); it != nameSet.end(); ++it) {
        tempkeywords.insert(*it);
    }
    for(set<string>::iterator it=genreSet.begin(); it != genreSet.end(); ++it) {
        tempkeywords.insert(*it);
    }

    return tempkeywords;
}

string Movie::displayString() const {
    string tempstring = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.\n";
    
    return tempstring;
}

void Movie::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}