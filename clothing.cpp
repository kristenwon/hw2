#include "clothing.h"
#include <sstream>
#include <iomanip>
#include "iostream"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) : Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing() { }

string Clothing::getSize() const
{
    return size_;
}

string Clothing::getBrand() const
{
    return brand_;
}

set<string> Clothing::keywords() const{
    set<string> tempkeywords;
    set<string> nameSet = parseStringToWords(name_);
    set<string> brandSet = parseStringToWords(brand_);
    for(set<string>::iterator it=nameSet.begin(); it != nameSet.end(); ++it) {
        tempkeywords.insert(*it);
    }
    for(set<string>::iterator it=brandSet.begin(); it != brandSet.end(); ++it) {
        tempkeywords.insert(*it);
    }

    return tempkeywords;
}

string Clothing::displayString() const {
    stringstream ss;
    ss << fixed << setprecision(2);
    ss << price_;
    string tempstring = name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.\n";
    
    return tempstring;
}

void Clothing::dump(ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}