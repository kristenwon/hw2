#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"
#include "util.h"

class Clothing : public Product {
    public:
        Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
        virtual ~Clothing();
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
        std::string getSize() const;
        std::string getBrand() const;

    private:
        std::string size_;
        std::string brand_;
};