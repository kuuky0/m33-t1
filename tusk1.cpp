#include <iostream>
#include <map>
#include <exception>
#include <boost/asio.hpp>

using namespace std;

class VoidCatalog : public exception {
public:
	const char* what() const noexcept override
	{
		return "Our catalog is void";
	}
};

void add(map<string, int>& a, map<string, int>& b,string c,int d)
{
	vector<string> saves;
	int count = 0;
	for (auto it = a.begin();it != a.end();it++)
	{
		if (c == it->first)
		{
			saves.push_back(it->first);
			count++;
		}
	}
	if (count == 0 ) throw std::invalid_argument("incorrect articul");

	for (int i = 0; i < saves.size(); i++)
	{
		if ( a[saves[i]] == d )
		{
			a[saves[i]] = 0;
			b.insert({ saves[i],d });
			a.erase(saves[i]);
		}
		else if (a[saves[i]] < d)
		{
			throw std::invalid_argument("Not enough product in catalog");
		}
		else
		{
			a[saves[i]] -= d;
			b.insert({ saves[i],d });
		}
	}
}

void remove(map<string, int>& a, map<string, int>& b, string c, int d)
{
	if (b.empty()) throw std::invalid_argument("basket empty");
	vector<string> saves;
	int count = 0;
	for (auto it : b)
	{
		if (c == it.first)
		{
			saves.push_back(it.first);
			count++;
		}
	}
	if (count == 0) throw std::invalid_argument("basket have no that articul");

	for (int i = 0; i < saves.size(); i++)
	{
		if (b[saves[i]] == d)
		{
			int c = b[saves[i]];
			b[saves[i]] = 0;
			b.erase(saves[i]);
			a.insert({ saves[i],c });
		}
		else if (b[saves[i]] < d)
		{
			throw std::invalid_argument("Not enough product in basket");
		}
		else
		{
			b[saves[i]] -= d;
			a.insert({ saves[i],d });
		}
	}
}

int main()
{
	map<string, int> catalog;
	map<string, int> basket;
	int size;
	cout << "Input how much product in your shop: ";
	cin >> size;

	for (int i = 0; i < size; i++)
	{
		string articul;
		int count;
		cout << "Input articul and count of item: ";
		cin >> articul >> count;
		catalog.insert({ articul,count });
	}

	string a;
	cout << "Do you want to see our Item List (yes or no)?";
	cin >> a;
	if (a == "yes")
	{
		for (auto it : catalog)
		{
			cout << "articul: " << it.first << "||" << "count: " << it.second << endl;
		}
	}

	bool input = true;
	while (input)
	{
		try
		{
			if (catalog.size() == 0) throw VoidCatalog();
			int command;
			cout << "Input command( add - 0, remove - 1 ): ";
			cin >> command;
			if (command == 0)
			{
				string c;
				int g;
				cout << "Input articul and count of product: ";
				cin >> c >> g;

				try {
					add(catalog, basket, c, g);
				}
				catch (const invalid_argument& x)
				{
					cerr << "Error: " << x.what() << "\n";
				}

				string a;
				cout << "Do you want to see current Item List (yes or no)?";
				cin >> a;
				if (a == "yes")
				{
					for (auto it : catalog)
					{
						cout << "articul: " << it.first << "||" << "count: " << it.second << endl;
					}
				}
			}
			else if (command == 1)
			{
				string c;
				int g;
				cout << "Input articul and count of product: ";
				cin >> c >> g;

				try {
					remove(catalog, basket, c, g);
				}
				catch (const invalid_argument& x)
				{
					cerr << "Error: " << x.what() << "\n";
				}

				string a;
				cout << "Do you want to see current Item List (yes or no)?";
				cin >> a;
				if (a == "yes")
				{
					for (auto it : catalog)
					{
						cout << "articul: " << it.first << "||" << "count: " << it.second << endl;
					}
				}
			}
			else
			{
				cout << "Incorrect command,try again" << endl;

			}
		}
		catch (const VoidCatalog& x)
		{
			cerr << x.what() << endl;
			input = !input;
		}
	}
}
