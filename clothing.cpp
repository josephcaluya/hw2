#include "clothing.h"
#include "util.h"
#include <sstream>

using namespace std;

Clothing::Clothing(std::string category, std::string name, double price, int qty, std::string brand, std::string size) :
	Product(category, name, price, qty)
{
	brand_ = brand;
	size_ = size;
}

Clothing::~Clothing()
{

}


std::set<std::string> Clothing::keywords() const {
	std::set<string> clothingName = parseStringToWords(name_);
	std::set<string> clothingBrand = parseStringToWords(brand_);
	std::set<string> clothingSet = setUnion(clothingName, clothingBrand);
	return clothingSet;
}

std::string Clothing::displayString() const {
	stringstream ss;
	ss << price_;
	string itemprice;
	ss >> itemprice;
	string clothingString = name_ + "\nSize: " + size_ + " Brand: " + brand_ +
				 "\n" + itemprice + " " + std::to_string(qty_) + " left.";
	return clothingString;
}

void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_
	<< "\n" << brand_ << endl;
}