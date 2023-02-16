#include <set>
#include <string>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(std::string category, std::string name, double price, int qty, std::string author, std::string isbn) :
	Product(category, name, price, qty) 
{
	author_ = author;
	isbn_ = isbn;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const {
	std::set<string> bookName = parseStringToWords(name_);
	std::set<string> bookAuthor = parseStringToWords(author_);
	std::set<string> bookSet = setUnion(bookName, bookAuthor);
	bookSet.insert(isbn_);
	return bookSet;
}

std::string Book::displayString() const {
	stringstream ss;
	ss << price_;
	string itemprice;
	ss >> itemprice;
	string bookString = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ +
				 "\n" + itemprice + " " + std::to_string(qty_) + " left.";
	return bookString;
}

void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_
	<< "\n" << author_ << endl;
}