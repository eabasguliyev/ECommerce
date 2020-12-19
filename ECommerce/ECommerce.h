#pragma once
#include "Client.h"
#include "Admin.h"
#include "Exception.h"

namespace ECommerce
{
	void start()
	{
		DatabaseSide::Database db;
		AdminSide::AdminDatabaseController admin_controller(&db);
		ClientSide::ClientDatabaseController client_controller(&db);

		admin_controller.defaultSetting();

		while (1)
		{
			system("CLS");
			std::cout << "[1] Guest\n";
			std::cout << "[2] Admin\n";
			std::cout << "[3] Master Admin\n";
			std::cout << "[4] Exit\n";

			size_t selected;

			std::cout << "Select: ";

			std::cin >> selected;

			if (selected == 1)
			{
				system("CLS");
				std::string fullname;

				std::cout << "Fullname: ";
				std::cin.ignore();

				std::cin >> fullname;

				if (client_controller.login(fullname))
				{
					client_controller.sentNotf(fullname, std::string("Logged in"));
				}
				else
				{
					client_controller.registerClient(fullname);
					client_controller.sentNotf(fullname, std::string("Guest account created"));
				}

				ClientSide::menu(client_controller, fullname);
			}
			else if (selected <= 3)
			{
				while (1)
				{
					system("CLS");
					std::string username, password;
					std::cin.ignore(255, '\n');
					std::cout << "Username: ";

					std::getline(std::cin, username);

					std::cout << "Password: ";

					std::getline(std::cin, password);

					if (selected == 2)
					{
						if (admin_controller.login(username, password))
						{
							AdminSide::menu(admin_controller);
							break;
						}
					}
					else
					{
						if (admin_controller.login(username, password, true))
						{
							AdminSide::masterMenu(admin_controller);
							break;
						}
					}
				}
			}
			else if (selected == 4)
				return;
		}
	}
}