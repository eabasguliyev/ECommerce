#pragma once
#include "Database.h"
namespace AdminSide {
	class DatabaseController {
	private:
		DatabaseSide::Database _database;
	public:
		DatabaseController(const DatabaseSide::Database& db)// injection
		{
			this->_database = db;
		}

		static void control()
		{

		}
	};
	void menu() {
		DatabaseController::control();
	}
}