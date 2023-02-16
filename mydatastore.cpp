#include "mydatastore.h"

using namespace std;

MyDataStore::~MyDataStore() 
{ 
	for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
		delete *it;
	}
	for (std::vector<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
		delete *it;
	}
}

    /**
     * Adds a product to the data store
     */
void MyDataStore::addProduct(Product* p) {
	productList.push_back(p);
}

    /**
     * Adds a user to the data store
     */
void MyDataStore::addUser(User* u) {
	userList.push_back(u);
}

void MyDataStore::updateCart(std::string& username, Product*& hitProduct) {
	User* currUser;
	bool isUser = false;
	for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
		if ((*it)->getName() == username) {
			isUser = true;
			currUser = (*it);
			break;
		}
	}
	if (isUser == false) {
		cout << "Invalid request" << endl;
		return;
	}
	map<User*, std::vector<Product*>>::iterator it = usersAndCarts.find(currUser);
	if (it != usersAndCarts.end()) {
		(it->second).push_back(hitProduct);
	}
	else {
		usersAndCarts[currUser].push_back(hitProduct);
	}
}

void MyDataStore::viewCart(std::string& username) {
	User* currUser;
	bool isUser = false;
	for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
		if ((*it)->getName() == username) {
			isUser = true;
			currUser = (*it);
			break;
		}
	}
	if (isUser == false) {
		cout << "Invalid username" << endl;
		return;
	}
	std::vector<Product*> userCart;
	map<User*, std::vector<Product*>>::iterator it = usersAndCarts.find(currUser);
	if (it != usersAndCarts.end()) {
		userCart = it->second;
	}
	for (unsigned int i = 0; i < userCart.size(); i++) {
		cout << "Item " << i+1 << endl;
		cout << userCart[i]->displayString() << endl;
	}
}

void MyDataStore::buyCart(std::string& username) {
	User* currUser;
	bool isUser = false;
	for (std::vector<User*>::iterator it = userList.begin(); it != userList.end(); ++it) {
		if ((*it)->getName() == username) {
			isUser = true;
			currUser = (*it);
			break;
		}
	}
	if (isUser == false) {
		cout << "Invalid username" << endl;
		return;
	}
	std::vector<Product*> userCart;
	map<User*, std::vector<Product*>>::iterator it = usersAndCarts.find(currUser);
	if (it != usersAndCarts.end()) {
		userCart = it->second;
	}
	for (unsigned int i = 0; i < userCart.size(); i++) {
		if ((userCart[i]->getQty() > 0) && (currUser->getBalance() >= userCart[i]->getPrice())) {
			userCart[i]->subtractQty(1);
			currUser->deductAmount(userCart[i]->getPrice());
			userCart.erase(userCart.begin()+i);
		}
	}

}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
 The vector<String> argument in the search function is the list of search 
 words the user typed in to look for a specific product. As you iterate through 
 that set of terms, you should be finding a set of products that match that keyword 
 and for every iteration you should be merging the sets of products to narrow down 
 how many products match all the keywords.     
		 */

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::set<std::string> searchedTerms;
	std::set<std::string> productKeywords;
	std::vector<Product*> matchingProducts;
	for (unsigned int i = 0; i < terms.size(); i++) {
		searchedTerms.insert(terms[i]);
	}
	if (type == 0) {
		for (std::vector<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
			productKeywords = (*it)->keywords(); 
			std::set<std::string> matchingWords = setIntersection(searchedTerms, productKeywords);
			if (matchingWords.size() == searchedTerms.size()) {
				matchingProducts.push_back(*it);
			}
		}
		return matchingProducts;
	}
	else if (type == 1) {
		for (std::vector<Product*>::iterator it = productList.begin(); it != productList.end(); ++it) {
			productKeywords = (*it)->keywords();
			std:set<std::string> matchingWords = setIntersection(searchedTerms, productKeywords);
			if (matchingWords.size() > 0) {
				matchingProducts.push_back(*it);
			}
		}
	}
	return matchingProducts;
}

/**
	* Reproduce the database file from the current Products and User values
	*/
void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << endl;
	for (unsigned int i = 0; i < productList.size(); i++) {
		productList[i]->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for (unsigned int i = 0; i < userList.size(); i++) {
		userList[i]->dump(ofile);
	}
	ofile << "</users>" << endl;
}