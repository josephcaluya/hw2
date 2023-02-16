#include "movie.h"
#include "util.h"
#include <sstream>

using namespace std;

Movie::Movie(std::string category, std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
}


Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const {
	std::set<string> movieName = parseStringToWords(name_);
	std::set<string> movieGenre = parseStringToWords(genre_);
	std::set<string> movieSet = setUnion(movieName, movieGenre);
	return movieSet;
}

std::string Movie::displayString() const {
	stringstream ss;
	ss << price_;
	string itemprice;
	ss >> itemprice;
	string movieString = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ +
				 "\n" + itemprice + " " + std::to_string(qty_) + " left.";
	return movieString;
}

void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_
	<< "\n" << rating_ << endl;
}