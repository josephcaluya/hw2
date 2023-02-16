#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"

class Clothing : public Product {
	public:
    Clothing(std::string category, std::string name, double price, int qty, std::string brand, std::string size);
		~Clothing();
    virtual std::set<std::string> keywords() const;	
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
  private:
    std::string brand_;
    std::string size_;
};


#endif