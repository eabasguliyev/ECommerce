#pragma once
#include <iostream>
#include "Time.h"

namespace DatabaseSide {
	class Base
	{
		size_t id;

	public:
		Base(const size_t& id)
		{
			setID(id);
		}
		void setID(const size_t& id)
		{
			this->id = id;
		}
		size_t getID() const { return this->id; }

		virtual void show() = 0;
		virtual ~Base() = 0 {}
	};

	class Admin : public Base {
		std::string username;
		std::string password;

	public:

		Admin(const size_t& id, const std::string& username, const std::string& password): Base(id)
		{
			setUsername(username);
			setPassword(password);
		}

		void setUsername(const std::string& username)
		{
			this->username = username;
		}

		std::string getUsername() const { return this->username; }

		void setPassword(const std::string& password)
		{
			this->password = password;
		}

		std::string getPassword() const { return this->password; }

		void show() override
		{
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Username: " << getUsername() << std::endl;
			std::cout << "Password: " << getPassword() << std::endl;
		}
	};

	class Client : public Base {
		std::string fullname;
		std::string connected_date;

	public:
		Client(const size_t& id, const std::string& fullname) : Base(id)
		{
			setFullName(fullname);
			setConnectedDate();
		}

		void setFullName(const std::string& fullname)
		{
			this->fullname = fullname;
		}

		std::string getFullName() const { return this->fullname; }

		void setConnectedDate()
		{
			this->connected_date = Time::getDate();
		}
		
		std::string getConnectedDate() const { return this->connected_date; }

		void show() override
		{
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Fullname: " << getFullName() << std::endl;
			std::cout << "Last connected date: " << getConnectedDate() << std::endl;
		}
	};

	class Product : public Base
	{
		std::string name;
		std::string description;
		std::string added_date;
		double price;
		double discount;
		double tax;

	public:
		Product(const size_t& id, const std::string& name, const std::string& description,
			const double& price, const double& discount, const double& tax) : Base(id)
		{
			setName(name);
			setDescription(description);
			setPrice(price);
			setDiscount(discount);
			setTax(tax);
			setID(id);
			setAddedDate();
		}

		void setName(const std::string& name)
		{
			this->name = name;
		}

		std::string getName() const { return this->name; }

		void setDescription(const std::string& description)
		{
			this->description = description;
		}

		std::string getDescription() const { return this->description; }

		void setAddedDate()
		{
			this->added_date = Time::getDate();
		}

		std::string getAddeDate() const { return this->added_date; }

		void setPrice(const double& price)
		{
			this->price = price;
		}

		double getPrice() const { return this->price; }

		void setDiscount(const double& discount)
		{
			this->discount = discount;
		}

		double getDiscount() const { return this->discount; }

		void setTax(const double& tax)
		{
			this->tax = tax;
		}

		double getTax() const { return this->tax; }

		double getDiscountedPrice() const
		{
			return this->price - ((this->price * this->discount) / 100.0);
		}
	};

	class ProductItem
	{
		Product* product;
		size_t quantity;

	public:
		ProductItem(Product*& product, const size_t& quantity)
		{
			setProduct(product);
			setQuantity(quantity);
		}

		void setQuantity(const size_t& quantity)
		{
			this->quantity = quantity;
		}

		size_t getQuantity()const { return this->quantity; }

		void setProduct(Product*& product)
		{
			this->product = product;
		}

		Product* getProduct() const { return this->product; }
	};

	template <typename T>
	class DataSet
	{
		T** items;
		size_t count;
	public:
		void add(const T* item);
		void deleteById(const size_t& id);
		T* getItem(const size_t& id);
		void updateById(const size_t& id);
	};

	class Database {
		DataSet<Product> products;
		DataSet<Admin> admins;
		DataSet<Client> guests;

		std::string name;
		std::string connected_date;
	};
}