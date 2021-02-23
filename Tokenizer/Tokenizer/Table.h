/*
2)	ѕодмножество €зыка —++ включает:
Х	данные типа int; 
Х	инструкции описани€ переменных;
Х	операторы присваивани€, while любой вложенности и в любой последовательности;
Х	операции  +, Ц , < =, >= , < , >.
*/

/*1)	разработать структуру посто€нных таблиц дл€ хранени€  алфавита €зыка, 
зарезервированных слов, знаков операций, разделителей и пр.;
реализовать дл€ посто€нных таблиц алгоритм поиска элемента в упор€доченной таблице;
*/
#pragma once
#include <vector>
#include <tuple>
#include <ostream>
#include <string>
#include <algorithm>
using namespace std;

template<typename T>
class VariableTable
{
private:
   // »дентификатор, тип, присвоено ли значение и значение
   vector<tuple<string, string, bool, T>>* table;
public:
   string TNAME = "int";
   int (*comparator)(tuple<string, string, bool, T> left, tuple<string, string, bool, T> right) =
      [](tuple<string, string, bool, T> left, tuple<string, string, bool, T> right)
   {
      string l = get<0>(left);
      string r = get<0>(right);

      if (l < r)
         return 1;
      else if (l > r)
         return -1;
      else
         return 0;
   };

   // √енерирует таблицу из файла

   VariableTable(istream& in)
   {
      throw exception("Not released");
   }

   // —оздать пустую таблицу

   VariableTable()
   {
      table = new vector<tuple<string, string, bool, T>>();
   }

   bool add_element(string name, T value)
   {
      if (!is_in_table(name))
      {
         // »щем позицию в отсортированном массиве
         auto elem = make_tuple(name, TNAME, true, value);
         int i;
         for (i = 0; i < table->size() && comparator(elem, table->at(i)) != 1; i++);
         table->insert(table->begin() + i, elem);

         return true;
      }
      else
         return false;
   }

   bool add_element(string name)
   {
      if (!is_in_table(name))
      {
         // »щем позицию в отсортированном массиве
         int i;
         auto elem = make_tuple(name, TNAME, false, 0);
         for (i = 0; i < table->size() && comparator(elem, table->at(i)) != 1; i++);
         table->insert(table->begin() + i, make_tuple(name, TNAME, false, 0));
         return true;
      }
      else
         return false;
   }

   bool add_element(tuple<string, string, bool, T> elem)
   {
      if (!is_in_table(elem))
      {
         // »щем позицию в отсортированном массиве
         int i;
         for (i = 0; i < table->size() && comparator(elem, table->at(i)) != 1; i++);
         table->insert(table->begin() + i, elem);
         return true;
      }
      else
         return false;
   }

   bool is_in_table(tuple<string, string, bool, T> elem)
   {
      return binary_search(table->begin(), table->end(), elem, comparator);
   }

   bool is_in_table(string elem)
   {
      return binary_search(table->begin(), table->end(), make_tuple(elem, TNAME, false, 0), comparator);
   }

   bool remove_element(string elem)
   {
      auto iter = lower_bound(table->begin(), table->end(), make_tuple(elem, TNAME, false, 0), comparator);
      if (iter == table->end())
         return false;
      else
         table->erase(iter, iter);
      return true;
   }

   int get_index(string elem)
   {
      auto iter = lower_bound(table->begin(), table->end(), make_tuple(elem, TNAME, false, 0));
      if (iter == table->end())
         return -1;
      else
         return *(iter);
   }

   tuple<string, string, bool, T>& get_elem(string elem)
   {
      auto iter = lower_bound(table->begin(), table->end(), make_tuple(elem, TNAME, false, 0));
      if (iter == table->end())
         throw invalid_argument("Such element does not exist");
      else
         return table->at(*(iter));
   }

   tuple<string, string, bool, T>& get_elem(int index)
   {
      if (index < table->size())
         return table->at(index);
      else
         throw invalid_argument("Index out of range");
   }

   void display(ostream& out)
   {
      for (int i = 0; i < table->size(); i++)
         out << get<0>(table->at(i)) << " ";
      out << endl;
   }

   ~VariableTable()
   {
      table->clear();
   }
};

class KeyTable
{
   /*
   2)	ѕодмножество €зыка —++ включает:
   Х	данные типа int;
   Х	инструкции описани€ переменных;
   Х	операторы присваивани€, while любой вложенности и в любой последовательности;
   Х	операции  +, Ц , < =, >= , < , >.
   */
private:
   vector<string>* values;
public:
   KeyTable();
   void display(ostream& out);
   bool is_in_table(string keyName);
   int get_index(string keyName);
   string get_elem(int index);
   ~KeyTable();
};