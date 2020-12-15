#pragma once
#include "Admin.h"
#include <locale>
namespace ClientSide {
	enum GuestControl
	{
		BUY = 1, MOREINFO, LOGOUT
	};

	class ClientDatabaseController : public DatabaseSide::DatabaseController
	{
	public:
		ClientDatabaseController(const DatabaseSide::Database* db) :DatabaseController(db) {}
		bool checkProductQuantity(const size_t& id, const size_t& quantity)
		{
			DatabaseSide::ProductItem* item = _database->getProductItem(id);

			if (quantity > item->getQuantity())
			{
				return false;
			}
			return true;
		}
		void buyProduct(const size_t& id, const size_t& quantity)
		{
			DatabaseSide::ProductItem* item = _database->getProductItem(id);

			item->setQuantity(item->getQuantity() - quantity);
		}
		bool login(const std::string& fullname)
		{
			DatabaseSide::Client* client = this->_database->getGuest(fullname);

			if (client != NULL)
			{
				client->setConnectedDate();
				return true;
			}
			return false;
		}
		bool registerClient(const std::string& fullname)
		{
			DatabaseSide::Client guest(0, fullname);
			this->_database->addGuest(&guest);
			return true;
		}
		void sentNotf(const std::string & fullname, const std::string & text)
		{
			DatabaseSide::Notification notf(0, fullname, text);
			this->_database->addNotf(&notf);
		}
	};

	void menu(ClientDatabaseController & controller, const std::string &fullname) {
		
		while (1)
		{
			system("CLS");
			std::cout << "Products!" << std::endl;

			controller.showAllProducts();


			std::cout << "[1] Buy\n";
			std::cout << "[2] More detail\n";
			std::cout << "[3] Logout\n";

			short selected;

			std::cout << "Select: ";

			std::cin >> selected;

			switch (selected)
			{
			case ClientSide::BUY:
			{
				system("CLS");
				size_t id;
				size_t quantity;
				std::cout << "Product id: ";

				std::cin >> id;

				std::cout << "Quantity: ";

				std::cin >> quantity;


				if (controller.checkProductQuantity(id, quantity)) {
					if (controller.toContinue(std::string("Are you sure to buy with " + std::to_string(quantity) + " amounts? y/n")))
					{
						controller.buyProduct(id, quantity);
						controller.sentNotf(fullname, std::string("This product was purchased -> id [ " +
							std::to_string(id) + " ]"));
					}
					else
					{
						controller.sentNotf(fullname, std::string("Cancelled checkout for this product -> id [ " +
							std::to_string(id) + " ]"));
					}
				}
				else
				{
					std::cout << "There are not enough products in stock\n";
					std::cin.ignore();
					std::cin.get();
					controller.sentNotf(fullname, std::string("Tried to buy this product -> id[ " + 
						std::to_string(id) + " ].\n But there are not enough products in stock."));
				}
			}
			break;
			case ClientSide::MOREINFO:
			{
				system("CLS");

				size_t id;

				std::cout << "Product id: ";

				std::cin >> id;

				DatabaseSide::Product* product = controller.getProduct(id);

				std::cout << *product;
				controller.sentNotf(fullname, std::string("Interested in this product -> id [ " +
					std::to_string(id) + " ]"));
				std::cout << "Press enter to continue!";
				std::cin.ignore();
				std::cin.get();
			}
			break;
			case ClientSide::LOGOUT:
			{
				return;
			}
			break;
			default:
				break;
			}
		}
		
	}
}