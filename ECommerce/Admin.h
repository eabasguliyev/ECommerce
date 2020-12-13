#pragma once
#include "Database.h"
#include <locale> //tolower
#include <ios>
namespace AdminSide {


	enum Control {
		ShowProducts = 1, AddProduct, DeleteProduct, UpdateProduct, Logout
	};

	class DatabaseController {
	private:
		 DatabaseSide::Database _database;
	public:
		DatabaseController(const DatabaseSide::Database& db)// injection
		{
			this->_database = db;
		}

		bool toContinue(const std::string & message)
		{
			std::string resp;
			std::cout << "\n" << message;

			std::cin >> resp;

			std::locale loc;
			if (std::tolower(resp.front(), loc) == 'y')
				return true;

			return false;
		}

		DatabaseSide::ProductItem& getNewItem()
		{
			DatabaseSide::Product product;
			size_t quantity;
			std::cin >> product; 

			std::cout << "Product quantity: ";

			std::cin >> quantity;
			DatabaseSide::ProductItem item(product, quantity);

			return item;
		}

		void control()
		{
			while (1)
			{
				system("CLS");
				std::cout << "[1] Show All Products\n";
				std::cout << "[2] Add Product\n";
				std::cout << "[3] Delete Product\n";
				std::cout << "[4] Update Product\n";
				std::cout << "[5] Logout\n";

				std::cout << "Select: ";

				size_t selected = 0;

				std::cin >> selected;

				switch (selected)
				{
				case ShowProducts:
				{

					this->_database.showAllProducts(true); std::cin.ignore();
					std::cin.get();
				}
				break;
				case AdminSide::AddProduct:
				{
					while (1)
					{
						system("CLS");
						std::cout << "Add New Product\n\n";

						this->_database.addProduct(&getNewItem());

						std::cout << "Product added!" << std::endl;

						if (!toContinue(std::string("Do you want to continue? y/n ")))
							break;
					}
				}
					break;
				case AdminSide::DeleteProduct:
				{
					while (1)
					{
						system("CLS");
						size_t product_id = 0;

						this->_database.showAllProducts(false);

						std::cout << "Delete product\n\n";

						std::cout << "Product id: ";
						
						std::cin >> product_id;

						this->_database.deleteProductByID(product_id);

						std::cout << "Product deleted\n";
						if (!toContinue(std::string("Do you want to continue? y/n ")))
							break;
					}
				}
				break;
				case AdminSide::UpdateProduct:
				{
					while (1)
					{
						system("CLS");
						size_t product_id = 0;

						this->_database.showAllProducts(false);

						std::cout << "Update Product\n\n";

						std::cout << "Product id: ";

						std::cin >> product_id;

						this->_database.updateProductByID(product_id, &getNewItem());

						std::cout << "Product updates!" << std::endl;

						if (!toContinue(std::string("Do you want to continue? y/n ")))
							break;
					}
				}
					break;
				case AdminSide::Logout:
				{
					return;
				}
				break;
				default:
					break;
				}
			}
		}
	};
	void menu() {
		DatabaseSide::Database db;
		DatabaseController controller(db);

		controller.control();
	}
}