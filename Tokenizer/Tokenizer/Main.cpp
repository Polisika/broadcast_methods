#include "Table.h"
#include <iostream>

void testKeyTable()
{
   KeyTable* table = new KeyTable();
   table->display(cout);
   cout << "Get element 2: " << table->get_elem(2) << endl;
   cout << table->get_index("int") << " index for \'int\'" << endl;
   cout << "int in table? " << (table->is_in_table("int") ? "yes" : "no") << endl;
   cout << "What about \'double\'? " << (table->is_in_table("double") ? "yes" : "no") << endl;
   table->~KeyTable();
}

void testVariableTable()
{
    VariableTable<int>* table = new VariableTable<int>();
    table->display(cout);
    cout << "Add myVariable with value: 2" << endl;
    table->add_element("myVariable", 2);
    table->display(cout);
    cout << "Get 0 index: " << get<0>(table->get_elem(0)) << endl;
    try {
        cout << "Get 10 index: ";
        get<0>(table->get_elem(10));
    }
    catch (invalid_argument e)
    {
        cout << e.what() << endl << endl;
    }
    cout << "myVariable in table? " << (table->is_in_table("myVariable") ? "yes" : "no") << endl;
    cout << "Try override myVariable with value 4: " << (table->add_element("myVariable", 4) ? "success" : "failed") << endl;
    cout << "myVariable value: " << get<3>(table->get_elem("myVariable")) << endl;
    cout << "Try add some elements: " << endl;
    table->add_element("abc", 3);
    table->add_element("zsd", 5);
    table->add_element("bbc", 5);
    table->add_element("wgds", 9);
    table->display(cout);
    cout << "Set myVariable to 10: " << (table->set_elem("myVariable", 10) ? "Success" : "Failed") << endl;
    cout << "myVariable value: " << get<3>(table->get_elem("myVariable")) << endl;
    cout << "Try remove from table: " << (table->remove_element("myVariable") ? "Success" : "Failed") << endl;
    table->display(cout);
    table->~VariableTable();
}

int main()
{
    cout << "Test KeyTable:" << endl;
    testKeyTable();
    cout << "________________________________________________" << endl;
    cout << "Test VariableTable" << endl;
    testVariableTable();
}