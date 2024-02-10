#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <fstream>

using namespace std;

MyDataStore::MyDataStore() { }
MyDataStore::~MyDataStore() {
    // deallocate all the products made in product_parser
    set<Product*>::iterator it;
    for(it = products.begin(); it != products.end(); ++it){
        delete *it;
    }
    set<User*>::iterator uit;
    for(uit = users.begin(); uit != users.end(); ++uit){
        delete *uit;
    }
}

void MyDataStore::addProduct(Product* p)
{
    set<string> keyWords = p->keywords();
    // set of keywords in the product that was passed in
    set<string> keyWords = p->keywords();

    // iterate through the set of keywords in the product
    for(it = keyWords.begin(); it != keyWords.end(); ++it){
        // the set of products it is a keyword of
        set<Product*> matchProducts;
        // if the keyword isn't already in the map
        if(keyMap.find(*it) == keyMap.end()){
            // add the product to the set of products
            matchProducts.insert(p);
            // insert the pair to the map
            keyMap.insert(std::make_pair(*it, matchProducts));
        }
        // if the keyword is already in the map
        else {
            map<string, set<Product*> >::iterator existPair = keyMap.find(*it);
            // add the product to the product set
            existPair->second.insert(p);
        }
    }
    products.insert(p);
}

void MyDataStore::addUser(User* u)
{
    users.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    set<string> termSet(terms.begin(), terms.end());
    vector<Product*> prodVec;
    // if there is one search term
    if(termSet.size() == 1){
        set<string>::iterator it = termSet.begin();
        set<Product*> keyProdSet = keyMap.find(*it)->second;
        set<Product*>::iterator prod;
        for(prod = keyProdSet.begin(); prod != keyProdSet.end(); ++prod){
            prodVec.push_back(*prod);
        }
    }
    // AND search
    else if(type == 0){
        set<Product*> megaProd;
        set<string>::iterator it;
        // make a big union of all the products
        for(it = termSet.begin(); it != termSet.end(); ++it){
            set<Product*> keyProdSet = keyMap.find(*it)->second;
            megaProd = setUnion(megaProd, keyProdSet);
        }
        set<string>::iterator it2;
        // get subsets of the union (reduces)
        for(it2 = termSet.begin(); it2 != termSet.end(); ++it2){
            set<Product*> keyProdSet = keyMap.find(*it2)->second;
            megaProd = setIntersection(megaProd, keyProdSet);
        }
        set<Product*>::iterator prod;
        for(prod = megaProd.begin(); prod != megaProd.end(); ++prod){
            prodVec.push_back(*prod);
        }
    }
    // OR search
    else if(type == 1){
        set<Product*> megaProd;
        set<string>::iterator it;
        for(it = termSet.begin(); it != termSet.end(); ++it){
            set<Product*> keyProdSet = keyMap.find(*it)->second;
            megaProd = setUnion(megaProd, keyProdSet);
        }
        set<Product*>::iterator prod;
        for(prod = megaProd.begin(); prod != megaProd.end(); ++prod){
            prodVec.push_back(*prod);
        }
    }

    prevSearch.clear();
    for(int i=0; i < prodVec.size(); i++){
        prevSearch.push_back(prodVec[i]);
    }

    return prodVec;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    set<Product*>::iterator it;
    for(it = products.begin(); it != products.end(); ++it){
        (**it).dump(ofile);
    }
    ofile << "</products>" << endl;
    set<User*>:: iterator uit;
    ofile << "<users>" << endl;
    for(uit = users.begin(); uit != users.end(); ++uit){
        (**uit).dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addProduct(Product* p)
{
    set<string> keyWords = p->keywords();

    for (set<string>::iterator it = keyWords.begin(); it != keyWords.end(); ++it) {
        const string& keyword = *it;
        
        map<string, set<Product*> >::iterator mapIt = keyMap.find(keyword);
        // if the keyword is not in the map
        if (mapIt == keyMap.end()) {
            set<Product*> productSet;
            productSet.insert(p);
            keyMap[keyword] = productSet;
        } else {
            // if it is add it to set
            mapIt->second.insert(p);
        }
    }

    products.insert(p);
}

void MyDataStore::viewCart(string username) const
{
    map<string, vector<Product*> >::const_iterator usercart = cart.find(username);
    // invalid username
    if(usercart == cart.end()){
        cout << "Invalid username" << endl;
    }
    else {
        if(!(usercart->second.empty())){
            for(int i=0; i < usercart->second.size(); i++){
            cout << i << endl;
            cout << usercart->second[i]->displayString();
            }
        }
    }
}

void MyDataStore::buyCart(string username)
{
    map<string, vector<Product*> >::iterator usercart = cart.find(username);
    if(usercart == cart.end()){
        cout << "Invalid username" << endl;
    }
    else {
        if(!usercart->second.empty()){
            set<User*>::iterator us;
            double cost = 0;
            vector<vector<Product*>::iterator> temp;
            vector<Product*>::iterator idx;
            for(vector<Product*>::iterator it = usercart->second.begin(); it != usercart->second.end();){
                if((*it)->getQty() > 0 && cost >= (*it)->getPrice()){
                    cout << "got Here" << endl;
                    (*it)->subtractQty(1);
                    cost += (*it)->getPrice();

                    temp.push_back(idx);
                }
                else {
                    it++;
                    idx++;
                }
                idx++;
            }
            for(int i=0; i < temp.size(); i++){
                (usercart->second).erase(temp[i]);
            }
            for(us = users.begin(); us != users.end(); ++us){
                if((*us)->getName() == username){
                    (*us)->deductAmount(cost);
                }
            }
        }
    }
}