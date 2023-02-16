#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include "user.h"
#include <map>
#include <vector>

class MyDataStore : public DataStore {
	public:
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

		void updateCart(std::string& username, Product*& hitProduct);
		void viewCart(std::string& username);
		void buyCart(std::string& username);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);
	private:
		std::map<User*, std::vector<Product*>> usersAndCarts;
		std::vector<Product*> productList;
		std::vector<User*> userList;
	
};

#endif