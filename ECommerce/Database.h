#pragma once
#include <iostream>
#include "Time.h"

namespace DatabaseSide {
	size_t generateHash(const std::string& data)
	{
		std::hash<std::string > hash;
		return hash(data);
	}

	class Base
	{
		size_t id;

	public:
		Base() : id(0) {}
		Base(const size_t& id)
		{
			setID(id);
		}
		void setID(const size_t& id)
		{
			this->id = id;
		}
		size_t getID() const { return this->id; }
		virtual ~Base() = 0 {}
	};

	class Admin : public Base {
		std::string username;
		std::string password;
		bool master;
	public:
		Admin() :username(""), password("") {}
		Admin(const size_t& id, const std::string& username, const std::string& password) : Base(id)
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
			this->password = std::to_string(generateHash(password));
		}

		std::string getPassword() const { return this->password; }

		void show() const
		{
			std::cout << "########################################" << std::endl;
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Username: " << getUsername() << std::endl;
			std::cout << "Password: " << getPassword() << std::endl;
		}

		friend std::ostream& operator << (std::ostream& out, const Admin& admin);
		friend std::istream& operator >> (std::istream& in, Admin& admin);
	};

	std::ostream& operator << (std::ostream& out, const Admin& admin)
	{
		admin.show();
		return out;
	}
	std::istream& operator >> (std::istream& in, Admin& admin)
	{
		std::string username, password;

		std::cout << "Username: ";

		//std::cin.ignore();
		std::getline(in, username);

		std::cout << "Password: ";

		std::getline(in, password);
		return in;
	}

	class Client : public Base {
		std::string fullname;
		std::string connected_date;

	public:
		Client() :fullname(""), connected_date("") {}
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

		void show() const
		{
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Fullname: " << getFullName() << std::endl;
			std::cout << "Last connected date: " << getConnectedDate() << std::endl;
		}

		friend std::ostream& operator << (std::ostream& out, const Client& client);
		friend std::istream& operator >> (std::istream& in, Client& client);
	};
	
	std::ostream& operator << (std::ostream& out, const Client& client)
	{
		client.show();
		return out;
	}
	std::istream& operator >> (std::istream& in, Client& client)
	{
		std::string fullname;

		std::cout << "Fullname: ";

		//in.ignore();
		std::getline(in, fullname);
		return in;
	}


	class Product : public Base
	{
		std::string name;
		std::string description;
		std::string added_date;
		double price;
		double discount;
		double tax;

	public:
		Product() : name(""), description(""), price(0.0), discount(0.0), tax(0.0)
		{
			setAddedDate();
		}

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

		friend std::ostream& operator << (std::ostream& out, const Product& product);
		friend std::istream& operator >> (std::istream& in, const Product& product);
		void shortInfo() const
		{
			std::cout << "########################################" << std::endl;
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Name: " << getName() << std::endl;
			std::cout << "Added date: " << getAddeDate() << std::endl;
			std::cout << "Price: " << getPrice() << std::endl;
		}

		void detail() const
		{
			std::cout << "########################################" << std::endl;
			std::cout << "ID: " << getID() << std::endl;
			std::cout << "Name: " << getName() << std::endl;
			std::cout << "Added date: " << getAddeDate() << std::endl;
			std::cout << "Description: " << getDescription() << std::endl;
			std::cout << "Price: " << getPrice() << std::endl;
			std::cout << "Tax: " << getTax() << std::endl;
			std::cout << "Discount: " << getDiscount() << std::endl;

			if (getDiscount())
			{
				std::cout << "Discounted price: " << getDiscountedPrice() << std::endl;
			}
		}

		void input()
		{
			std::string name, description;
			double price, discount, tax;
			std::cout << "Name: ";

			std::cin.ignore();
			std::getline(std::cin, name);

			setName(name);

			std::cout << "Description: ";

			std::getline(std::cin, description);

			setDescription(description);

			std::cout << "Price: ";

			std::cin >> price;

			setPrice(price);

			std::cout << "Tax: ";

			std::cin >> tax;

			setTax(tax);

			std::cout << "Discount: ";

			std::cin >> discount;

			setDiscount(discount);
		}
	};

	std::ostream& operator << (std::ostream& out, const Product& product)
	{
		product.detail();
		return out;
	}
	std::istream& operator >> (std::istream& in, Product& product)
	{
		product.input();
		return in;
	}

	class ProductItem
	{
		Product* product;
		size_t quantity;

	public:
		ProductItem(const Product & product, const size_t& quantity)
		{
			setProduct(product);
			setQuantity(quantity);
		}

		void setQuantity(const size_t& quantity)
		{
			this->quantity = quantity;
		}

		size_t getQuantity()const { return this->quantity; }

		void setProduct(const Product& product)
		{
			this->product = new Product(product);
		}

		Product* getProduct() const { return this->product; }

		size_t getID() const { return this->product->getID(); }
		void setID(const size_t& id)
		{
			this->product->setID(id);
		}

		~ProductItem()
		{
			delete this->product;
			this->product = NULL;
		}
	};

	template <typename T>
	class DataSet
	{
		T** items;
		size_t count;
	public:
		DataSet() :items(NULL), count(0.0) {}
		void add(const size_t id, const T* item)
		{
			size_t new_size = this->count + 1;
			auto new_items = new T * [new_size];

			if (new_items != NULL)
			{
				if (new_size - 1)
				{
					for (size_t i = 0; i < this->count; i++)
					{
						new_items[i] = this->items[i];
					}

					delete[] this->items;
				}

				new_items[new_size - 1] = new T(*item);
				new_items[new_size - 1]->setID(id);
				this->count = new_size;
				this->items = new_items;
			}
		}
		void deleteById(const size_t index)
		{
			auto new_items = new T * [this->count - 1];

			if (new_items != NULL)
			{
				for (size_t i = 0; i < index; i++)
				{
					new_items[i] = this->items[i];
				}

				for (size_t i = index, j = i + 1; i < this->count - 1; i++)
				{
					new_items[i] = this->items[j];
				}

				delete this->items[index];
				delete[] this->items;

				this->items = new_items;
				this->count--;
			}
		}
		T* getItem(const size_t& id) const
		{
			int item_index = getItemIndexById(id);

			if (item_index != -1)
				return this->items[item_index];
			return NULL;
		}
		int getItemIndexById(const size_t& id) const
		{
			for (size_t i = 0; i < this->count; i++)
			{
				if (id == this->items[i]->getID())
					return i;
			}
			return -1;
		}
		void updateById(const size_t index, const T* item)
		{
			size_t id = this->items[index]->getID();
			delete this->items[index];
			this->items[index] = new T(*item);
			this->items[index]->setID(id);
		}

		size_t getItemCount() const { return this->count; }

		T** getItems() const { return this->items; }

		~DataSet()
		{
			for (size_t i = 0; i < this->count; i++)
			{
				delete this->items[i];
			}
			delete[] this->items;
		}
	};

	class Database {
		DataSet<ProductItem> products;
		DataSet<Admin> admins;
		DataSet<Client> guests;

		std::string name;
		std::string created_date;
		std::string last_modified_date;
	
	private:
		void setCreatedDate()
		{
			this->created_date = Time::getDate();
		}

	public:
		static size_t admins_id;
		static size_t guests_id;
		static size_t products_id;


		Database() :name(""), created_date(""), last_modified_date("") {}
		Database(const std::string & name) {
			setName(name);
			setCreatedDate();
		}

		void setName(const std::string& name)
		{
			this->name = name;
		}

		std::string getName() const { return this->name; }

		void setLastModifiedDate(const std::string& date)
		{
			this->last_modified_date = date;
		}

		std::string getLastModifiedDate() const { return this->last_modified_date; }

		std::string getCreatedDate() const { return this->created_date; }

		void addProduct(const ProductItem * product)
		{
			if (product != NULL)
				this->products.add(++products_id, product);
		}

		void deleteProductByID(const size_t& id)
		{
			if (id > 0)
				this->products.deleteById(id);
		}

		void updateProductByID(const size_t& index, const ProductItem* item)
		{
			if (item != NULL)
				this->products.updateById(index, item);
		}

		int getProductIndexById(const size_t &id) const { return this->products.getItemIndexById(id); }
		void showAllProducts(bool fullDetail = false) const 
		{
			ProductItem ** items = this->products.getItems();
			if (items != NULL)
			{
				if (fullDetail)
				{
					for (size_t i = 0, length = this->products.getItemCount(); i < length; i++)
					{
						std::cout << *items[i]->getProduct();
					}
					std::cout << "########################################" << std::endl;
				}
				else
				{
					for (size_t i = 0, length = this->products.getItemCount(); i < length; i++)
					{
						items[i]->getProduct()->shortInfo();
					}
					std::cout << "########################################" << std::endl;
				}
			}
			else
				std::cout << "There is no product!" << std::endl;
		}

		Product* getProduct(const size_t& id) const { return this->products.getItem(id)->getProduct(); }

		ProductItem* getProductItem(const size_t& id) const { return this->products.getItem(id); }
		void addAdmin(const Admin* admin)
		{
			if (admin != NULL)
				this->admins.add(++admins_id, admin);
		}

		void deleteAdminByID(const size_t& id)
		{
			if (id > 0)
				this->admins.deleteById(id);
		}

		void updateAdminByID(const size_t& id, const Admin* admin)
		{
			if (id > 0 && admin != NULL)
				this->admins.updateById(id, admin);
		}
		int getAdminIndexById(const size_t& id) const{ return this->admins.getItemIndexById(id); }
		Admin* getAdmin(const size_t& id) { return this->admins.getItem(id); }

		void showAllAdmins() const
		{
			Admin** admins = this->admins.getItems();

			if (admins != NULL)
			{
				for (size_t i = 0; i < this->admins.getItemCount(); i++)
				{
					std::cout << admins[i];
				}
			}
		}
		void addGuest(const Client* guest)
		{
			if (guest != NULL)
				this->guests.add(++guests_id, guest);
		}

		void deleteGuestByID(const size_t& id)
		{
			if (id > 0)
				this->guests.deleteById(id);
		}

		void updateGuestByID(const size_t& id, const Client* guest)
		{
			if (id > 0 && guest != NULL)
				this->guests.updateById(id, guest);
		}
		void showAllGuests() const
		{
			Client** guests = this->guests.getItems();

			if (guests != NULL)
			{
				for (size_t i = 0; i < this->admins.getItemCount(); i++)
				{
					std::cout << guests[i];
				}
			}
		}
		Client* getGuest(const size_t& id) { return this->guests.getItem(id); }

		int getGuestIndexById(const size_t& id) const { return this->guests.getItemIndexById(id); }
	};

	size_t Database::products_id = NULL;
	size_t Database::admins_id = NULL;
	size_t Database::guests_id = NULL;
}