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

void MyDataStore::addUser(User* u)
{
  // std::make_pair(convToLower(u->getName()), )
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

void MyDataStore::addToCart(string username, int index, std::vector<Product*>& hits)
{
  if(index >= 1 && index <= hits.size()){
      set<User*>::iterator it;
      bool isUser = false;
      // if user is in the users set
      for(it = users.begin(); it != users.end(); ++it){
          if(convToLower((*it)->getName()) == convToLower(username)){
              isUser = true;
          }
      }
      // if the user is in the users set
      if(isUser){
        // if the user doesn't have a cart already
        if(cart.find(convToLower(username)) == cart.end()){ 
          // make one
          vector<Product*> newCart;
          // add a key,value pair to the cart map
          cart.insert(std::make_pair(convToLower(username), newCart));
        }
        
        // push the product into user's cart
        map<string, vector<Product*> >::iterator usercart = cart.find(convToLower(username));
        (usercart->second).push_back(hits[index-1]);
      }
      else {
          cout << "Invalid request" << endl;
      }
  }
  else {
    cout << "Invalid request" << endl;
  }
}

void MyDataStore::viewCart(string username) const
{
  set<User*>::iterator it;
  bool isUser = false;
  for(it = users.begin(); it != users.end(); ++it){
    if(convToLower((*it)->getName()) == convToLower(username)){
      isUser = true;
    }
  }
  // if username is valid
  if(isUser){
    map<string, vector<Product*> >::const_iterator usercart = cart.find(convToLower(username));
    // if the cart isn't empty
    if(!(usercart->second.empty())){
      for(size_t i=1; i <= usercart->second.size(); i++){
        cout << "Item " << i << endl;
        cout << (usercart->second[i-1])->displayString();
      }
    }
  }
  else {
    cout << "Invalid username" << endl;
  }
}

void MyDataStore::buyCart(string username)
{
  set<User*>::iterator it;
  bool isUser = false;
  for(it = users.begin(); it != users.end(); ++it){
    if(convToLower((*it)->getName()) == convToLower(username)){
      isUser = true;
    }
  }
  // if username is valid
  if(isUser){
    // iterator to user's cart 
    set<User*>::iterator us = users.begin();
    while((*us)->getName() != convToLower(username)){
      ++us;
    }
    vector<Product*> tempProdVec;
    vector<Product*>& currProdVec= (cart.find(username))->second;
    vector<Product*>::iterator it;
    for(it = currProdVec.begin(); it != currProdVec.end(); ++it){
      // if the item cannot be bought
      if((*it)->getQty() <= 0 || (*it)->getPrice() > (*us)->getBalance()){
        tempProdVec.push_back(*it);
      }
      // item can be bought, update stuff
      else {
        (*it)->subtractQty(1);
        (*us)->deductAmount((*it)->getPrice());
      }
    }
    currProdVec = tempProdVec;

    // temp is now the real deal
    cart.insert(std::make_pair(username, tempProdVec));
    
  }
else {
  cout << "Invalid username" << endl;
}
}