#include "book.h"
#include <sstream>
#include <iomanip>
#include "iostream"

using namespace std;

Book::Book(const std::string bookcategory, const std::string bookname, double bookprice, int bookqty, std::string isbn, std::string author) : Product(bookcategory, bookname, bookprice, bookqty){
    isbn_ = isbn;
    author_ = author;
}

Book::~Book(){}

string Book::getIsbn() const
{
    return isbn_;
}

string Book::getAuthor() const
{
    return author_;
}

set<string> Book::keywords() const{
    set<string> tempkeywords;
    set<string> nameSet = parseStringToWords(name_);
    set<string> authorSet = parseStringToWords(author_);
    for(set<string>::iterator it=nameSet.begin(); it != nameSet.end(); ++it) {
        tempkeywords.insert(*it);
    }
    tempkeywords.insert(isbn_);
    for(set<string>::iterator it=authorSet.begin(); it != authorSet.end(); ++it) {
        tempkeywords.insert(*it);
    }

    return tempkeywords;
}

string Book::displayString() const {
    string tempstring = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.\n";
    
    return tempstring;
}

void Book::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}