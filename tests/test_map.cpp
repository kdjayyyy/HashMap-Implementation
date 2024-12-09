#include "../src/MyMap.hpp"
#include <iostream>
#include <cassert>

// Test for int key type
void testIntKey()
{
   MyMap<int, int> map;
   map.insert(1, 100);
   map.insert(2, 200);
   assert(map.getValue(1) == 100);
   assert(map.getValue(2) == 200);
   // std::cout << map.getValue(2) << std::endl;
   std::cout << "Int key tests passed!" << std::endl;
}

// Test for double key type
void testDoubleKey()
{
   MyMap<double, int> map;
   map.insert(1.1, 100);
   map.insert(2.2, 200);
   assert(map.getValue(1.1) == 100);
   assert(map.getValue(2.2) == 200);
   // std::cout << map.getValue(2.2) << std::endl;
   std::cout << "Double key tests passed!" << std::endl;
}

// Test for char key type
void testCharKey()
{
   MyMap<char, int> map;
   map.insert('a', 100);
   map.insert('b', 200);
   assert(map.getValue('a') == 100);
   assert(map.getValue('b') == 200);
   // std::cout << map.getValue('b') << std::endl;
   std::cout << "Char key tests passed!" << std::endl;
}

// Test for string key type
void testStringKey()
{
   MyMap<std::string, int> map;
   map.insert("Alice", 100);
   map.insert("Bob", 200);
   assert(map.getValue("Alice") == 100);
   assert(map.getValue("Bob") == 200);
   // std::cout << map.getValue("Bob") << std::endl;
   std::cout << "String key tests passed!" << std::endl;
}

// Test for pointer key type
void testPointerKey()
{
   MyMap<int *, int> map;
   int a = 10, b = 20;
   map.insert(&a, 100);
   map.insert(&b, 200);
   assert(map.getValue(&a) == 100);
   assert(map.getValue(&b) == 200);
   // std::cout << map.getValue(&b) << std::endl;
   std::cout << "Pointer key tests passed!" << std::endl;
}

// Custom function implemented for the demonstration of the code in the readme file
void demoFunction()
{
   MyMap<int, std::string> map;

   // Insert key-value pairs
   map.insert(1, "One");
   map.insert(2, "Two");

   // Retrieve value by key
   std::cout << "Key 1: " << map.getValue(1) << std::endl;

   // Remove key-value pair
   map.remove(1);

   // Get size
   std::cout << "Size: " << map.size() << std::endl;
}

int main()
{
   testIntKey();
   testDoubleKey();
   testCharKey();
   testStringKey();
   testPointerKey();

   // demoFunction();

   return 0;
}
