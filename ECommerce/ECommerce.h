#pragma once
#include "Client.h"
#include "Admin.h"

namespace ECommerce
{
	void start()
	{
		ClientSide::menu();
		AdminSide::menu();
	}
}