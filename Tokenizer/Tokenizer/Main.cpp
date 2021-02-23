#include "Table.h"
#include <iostream>

void testKeyTable()
{
   KeyTable* table = new KeyTable();
   table->display(cout);
   cout << "Get element 2: " << table->get_elem(2) << endl;
   cout << table->get_index("int") << " index for \'int\'" << endl;
   cout << table->is_in_table("int") << " in table?" << endl;
   cout << "What about \'double\'? " << table->is_in_table("double") << endl;
   table->~KeyTable();
}

int main()
{
   VariableTable<int>* table = new VariableTable<int>();
   table->display(cout);
   table->add_element("myVariable", 2);
   table->display(cout);
   cout << "Get 0 index: " << get<0>(table->get_elem(0)) << endl;
   try {
      cout << "Get 10 index: " << get<0>(table->get_elem(10)) << endl;
   }
   catch (invalid_argument e)
   {
      cout << e.what() << endl;
   }
   cout << "myVariable in table? " << table->is_in_table("myVariable") << endl;
   table->add_element("abc", 3);
   table->add_element("zsd", 5);
   table->add_element("bbc", 5);
   table->add_element("wgds", 9);
   cout << "add similar: " << table->add_element("myVariable", 4) << endl;
   cout << get<3>(table->get_elem("myVariable")) << endl;
   table->display(cout);
}