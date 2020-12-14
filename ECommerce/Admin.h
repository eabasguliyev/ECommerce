#pragma once
#include "Database.h"
#include <locale> //tolower
#include <ios>
namespace AdminSide {

	enum Control {
		ShowProducts = 1, AddProduct, DeleteProduct, UpdateProduct, Back
	};

	enum AdminControl
	{
		ShowAdmins = 1, AddAdmin, DeleteAdmin, UpdateAdmin	
	};
	enum GuestControl
	{
		ShowGuests = 1, AddGuest, DeleteGuest, UpdateGuest
	};

	enum MainMenu
	{
		ProductOptions = 1, AdminOptions, GuestOptions, Logout
	};

	class DatabaseController {
	protected:
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

		DatabaseSide::ProductItem *getNewItem()
		{
			DatabaseSide::Product product;
			size_t quantity;
			std::cin >> product; 

			std::cout << "Product quantity: ";

			std::cin >> quantity;
			DatabaseSide::ProductItem* item = new DatabaseSide::ProductItem(product, quantity);

			return item;
		}

		size_t getProductIndexByID()
		{
			int item_index = 0;
			while (1)
			{
				int product_id;
				std::cout << "Product id: ";

				std::cin >> product_id;

				item_index = this->_database.getProductIndexById(product_id);

				if (item_index != -1)
					return item_index;
				std::cout << "There is no product for this id! Try again!\n\n";
			}
		}

		size_t getAdminIndexByID()
		{
			int index = 0;
			while (1)
			{
				int admin_id;
				std::cout << "Admin id: ";

				std::cin >> admin_id;

				index = this->_database.getAdminIndexById(admin_id);

				if (index != -1)
					return index;
				std::cout << "There is no admin for this id! Try again!\n\n";
			}
		}

		size_t getGuestIndexByID()
		{
			int index = 0;
			while (1)
			{
				int guest_id;
				std::cout << "Guest id: ";

				std::cin >> guest_id;

				index = this->_database.getGuestIndexById(guest_id);

				if (index != -1)
					return index;
				std::cout << "There is no guest for this id! Try again!\n\n";
			}
		}

		DatabaseSide::Admin* getNewAdmin()
		{
			DatabaseSide::Admin* admin;

			std::cin >> *admin;

			return admin;
		}
		
		DatabaseSide::Client* getNewGuest()
		{
			DatabaseSide::Client* guest;

			std::cin >> *guest;
			return guest;
		}

		void productControl()
		{
			while (1)
			{
				system("CLS");
				std::cout << "[1] Show All Products\n";
				std::cout << "[2] Add Product\n";
				std::cout << "[3] Delete Product\n";
				std::cout << "[4] Update Product\n";
				std::cout << "[5] Back\n";

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

						this->_database.addProduct(getNewItem());

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

						this->_database.deleteProductByID(getProductIndexByID());

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

						this->_database.showAllProducts(false);

						std::cout << "Update Product\n\n";

						this->_database.updateProductByID(getProductIndexByID(), getNewItem());

						std::cout << "Product updates!" << std::endl;

						if (!toContinue(std::string("Do you want to continue? y/n ")))
							break;
					}
				}
					break;
				case 5:
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

	class DatabaseMasterController: public DatabaseController
	{
	public:
		DatabaseMasterController(const DatabaseSide::Database& db) :DatabaseController(db) {}
		void adminControl() {
			system("CLS");
			std::cout << "[1] Show All Admins\n";
			std::cout << "[2] Add Admin\n";
			std::cout << "[3] Delete Admin\n";
			std::cout << "[4] Update Admin\n";
			std::cout << "[5] Back\n";

			std::cout << "Select: ";

			size_t selected = 0;

			std::cin >> selected;

			switch (selected)
			{
			case AdminSide::ShowAdmins:
			{
				this->_database.showAllAdmins(); std::cin.ignore();
				std::cin.get();
			}
				break;
			case AdminSide::AddAdmin:
			{
				while (1)
				{
					system("CLS");
					std::cout << "Add New Admin\n\n";

					this->_database.addAdmin(getNewAdmin());

					std::cout << "Admin added!" << std::endl;

					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::DeleteAdmin:
			{
				while (1)
				{
					system("CLS");
					size_t product_id = 0;

					this->_database.showAllAdmins();

					std::cout << "Delete admin\n\n";

					this->_database.deleteAdminByID(getAdminIndexByID());

					std::cout << "Admin deleted\n";
					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::UpdateAdmin:
			{
				while (1)
				{
					system("CLS");

					this->_database.showAllAdmins();

					std::cout << "Update Admin\n\n";

					this->_database.updateAdminByID(getAdminIndexByID(), getNewAdmin());

					std::cout << "Admin updated!" << std::endl;

					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::Back:
			{
				return;
			}
				break;
			default:
				break;
			}
		}

		void guestControl()
		{
			system("CLS");
			std::cout << "[1] Show All Guests\n";
			std::cout << "[2] Add Guest\n";
			std::cout << "[3] Delete Guest\n";
			std::cout << "[4] Update Guest\n";
			std::cout << "[5] Back\n";

			std::cout << "Select: ";

			size_t selected = 0;

			std::cin >> selected;

			switch (selected)
			{
			case AdminSide::ShowGuests:
			{
				this->_database.showAllGuests(); std::cin.ignore();
				std::cin.get();
			}
				break;
			case AdminSide::AddGuest:
			{
				while (1)
				{
					system("CLS");
					std::cout << "Add New Guest\n\n";

					this->_database.addGuest(getNewGuest());

					std::cout << "Guest added!" << std::endl;

					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::DeleteGuest:
			{
				while (1)
				{
					system("CLS");
					size_t product_id = 0;

					this->_database.showAllGuests();

					std::cout << "Delete guest\n\n";

					this->_database.deleteGuestByID(getGuestIndexByID());

					std::cout << "Admin deleted\n";
					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::UpdateGuest:
			{
				while (1)
				{
					system("CLS");

					this->_database.showAllGuests();

					std::cout << "Update Guest\n\n";

					this->_database.updateGuestByID(getGuestIndexByID(), getNewGuest());

					std::cout << "Guest updated!" << std::endl;

					if (!toContinue(std::string("Do you want to continue? y/n ")))
						break;
				}
			}
				break;
			case AdminSide::Back:
			{
				return;
			}
				break;
			default:
				break;
			}
				
		}
		
	};

	void menu() {
		DatabaseSide::Database db;
		DatabaseController controller(db);

		controller.productControl();
	}

	void masterMenu()
	{
		DatabaseSide::Database db;
		DatabaseMasterController controller(db);

		system("CLS");
		std::cout << "Master options!";

		std::cout << "[1] Admin Control\n";
		std::cout << "[2] Guest Control\n";
		std::cout << "[3] Product Control\n";
		std::cout << "[4] Exit\n";

		std::cout << "Select: ";

		size_t selected = 0;

		std::cin >> selected;
		switch (true)
		{
		case AdminSide::ProductOptions:
		{
			controller.productControl();
		}
		break;
		case AdminSide::AdminOptions:
		{
			controller.adminControl();
		}
		break;
		case AdminSide::GuestOptions:
		{
			controller.guestControl();
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