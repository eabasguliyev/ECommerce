#pragma once
#include "Admin.h"
#include <locale>
namespace ClientSide {
	enum GuestControl
	{
		BUY = 1, MOREINFO, LOGOUT
	};

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

	void menu(AdminSide::DatabaseController & controller) {
		
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
					if (toContinue(std::string("Are you sure to buy with " + std::to_string(quantity) + " amounts? y/n")))
						controller.buyProduct(id, quantity);
				}
				else
					std::cout << "There are not enough products in stock\n";
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