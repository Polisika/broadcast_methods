#include "Table.h"


KeyTable::KeyTable()
{
   values = new vector<string>({ "int", "=", ";", "while", "+", "-",
                                             "<", "<=", ">=", ">", "main", "(", ")", "{", "}" });
   sort(values->begin(), values->end());
   values->shrink_to_fit();
}

int KeyTable::get_index(string keyName)
{
   auto iter = lower_bound(values->begin(), values->end(), keyName);
   if (iter == values->end())
      throw invalid_argument("Such key does not exist.");
   return distance(values->begin(), iter);
}

string KeyTable::get_elem(int index)
{
   return values->at(index);
}

bool KeyTable::is_in_table(string keyName)
{
   return binary_search(values->begin(), values->end(), keyName);
}

void KeyTable::display(ostream& out)
{
   for (int i = 0; i < values->size(); i++)
      out << values->at(i) << " ";
   out << endl;
}

KeyTable::~KeyTable()
{
   values->clear();
}
