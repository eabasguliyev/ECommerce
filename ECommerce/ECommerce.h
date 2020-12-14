#pragma once
#include "Client.h"
#include "Admin.h"

namespace ECommerce
{
	void start()
	{
		DatabaseSide::Database db;
		AdminSide::DatabaseController controller(db);

		while (1)
		{
			system("CLS");
			std::cout << "[1] Guest\n";
			std::cout << "[2] Admin\n";
			std::cout << "[3] Master Admin\n";
			std::cout << "[4] Exist\n";

			size_t selected;

			std::cout << "Select: ";

			std::cin >> selected;

			if (selected == 1)
				ClientSide::menu(controller);
			else if (selected == 2)
				AdminSide::menu(controller);
			else if (selected == 3)
			{
				AdminSide::DatabaseMasterController master(db);
				AdminSide::masterMenu(master);
			}
			else if (selected == 4)
				return;
		}
	}
}