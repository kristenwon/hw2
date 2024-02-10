#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addToCart(std::string username, int index, std::vector<Product*>& hits);
    void viewCart(std::string username) const;
    void buyCart(std::string username);
private:
    std::set<Product*> products;
    std::set<User*> users;
    std::map<std::string, std::set<Product*> > keyMap;
    std::map<std::string, std::vector<Product*> > cart;
};