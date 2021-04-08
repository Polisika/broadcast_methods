#pragma once
#include <vector>
#include <tuple>
#include <ostream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

enum TableType { OPERATIONS, DELIMETERS, KEYWORDS };

template<typename T>
class VariableTable
{
private:
	// Идентификатор, тип, присвоено ли значение и значение
	vector<tuple<string, string, bool, T>>* table;
    const string TNAMEdef = "int";
    const string TNAMEwithoutValue = "NULL";
public:

	// Генерирует таблицу из файла
	VariableTable(istream& in)
	{
		throw exception("Not released");
	}

	// Создать пустую таблицу
	VariableTable()
	{
		table = new vector<tuple<string, string, bool, T>>();
	}

	int add_element(string name, T value)
	{
        int index;
		if ((index = get_index(name)) == -1)
		{
            table->push_back(make_tuple(name, TNAMEdef, true, value));
			return table->size() - 1;
		}
		else
			return index;
	}

	int add_element(string name)
	{
        int index;
		if ((index = get_index(name)) == -1)
		{
            table->push_back(make_tuple(name, TNAMEwithoutValue, false, 0));
            return table->size() - 1;
		}
		else
			return index;
	}

	int add_element(tuple<string, string, bool, T> elem)
	{
        int index;
        if ((index = get_index(get<0>(elem))) == -1)
        {
            table->push_back(elem);
            return table->size() - 1;
        }
        else
            return index;
	}

	int get_index(string elem)
	{
        for (int i = 0; i < table->size(); i++)
            if (get<0>(table->at(i)) == elem)
                return i;
        return -1;
	}

	tuple<string, string, bool, T>& get_elem(string elem)
	{
		auto iter = lower_bound(table->begin(), table->end(), make_tuple(elem, TNAMEdef, false, 0));
		if (iter == table->end())
			throw invalid_argument("Such element does not exist");
		else
			return *iter;
	}

	tuple<string, string, bool, T>& get_elem(int index)
	{
		if (index < table->size())
			return table->at(index);
		else
			throw invalid_argument("Index out of range");
	}

	int set_elem(string name, T value)
	{
		int index = get_index(name);
		table->at(index) = make_tuple(name, TNAMEdef, true, value);
		return true;
	}

    int set_type(string name, string type)
    {
        int index = get_index(name);
        table->at(index) = make_tuple(name, type, get<2>(table->at(index)), get<3>(table->at(index)));
        return index;
    }

	void display(ostream& out)
	{
		out << setfill(' ');
		out << setw(15) << "Name" <<
			setw(7) << "Type" <<
			setw(10) << "Init-ed?" <<
			setw(15) << "Value" << endl;
		for (int i = 0; i < table->size(); i++)
		{
			auto e = table->at(i);
			out << setw(15) << get<0>(e) <<
				setw(7) << get<1>(e) <<
				setw(10) << (get<2>(e) ? "Yes" : "No") <<
				setw(15) << get<3>(e) << endl;
		}
		out << endl;
	}

	~VariableTable()
	{
		table->clear();
	}
};

class KeyTable
{
public:
	vector<string>* values;

    TableType type;
	KeyTable(TableType type);
	void display(ostream& out);
	bool is_in_table(string keyName);
	int get_index(string keyName);
	string get_elem(int index);
	~KeyTable();
};