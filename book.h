#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h"

class Book : public Product {
	public:
		Book(std::string category, std::string name, double price, int qty, std::string author, std::string isbn);
		~Book();
    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
	private:
		std::string author_;
		std::string isbn_;
};

#endif