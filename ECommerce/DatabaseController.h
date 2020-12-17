#pragma once
#include <iostream>
#include "Database.h"
#include "Admin.h"

namespace DatabaseController
{
	class DatabaseController {
	protected:
		DatabaseSide::Database* _database;
	private:
		void setDB(const DatabaseSide::Database* db)
		{
			this->_database = const_cast<DatabaseSide::Database*>(db);
		}
	public:
		DatabaseController(const DatabaseSide::Database* db)// injection
		{
			setDB(db);
		}
		DatabaseSide::Product* getProduct(const size_t& id)
		{
			return _database->getProduct(id);
		}
		bool toContinue(const std::string& message)
		{
			std::string resp;
			std::cout << "\n" << message;

			std::cin >> resp;

			std::locale loc;
			if (std::tolower(resp.front(), loc) == 'y')
				return true;

			return false;
		}

		void showAllProducts() const
		{
			_database->showAllProducts();
		}

		//const DatabaseSide::Database& getDB() const { return this->_database;}
	};
}