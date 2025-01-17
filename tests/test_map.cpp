#include "../src/MyMap.hpp"
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <random>
#include <cassert>
#include <iomanip>

// Utility function to measure execution time
template <typename Func>
double measureTime(Func func)
{
   auto start = std::chrono::high_resolution_clock::now();
   func();
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;
   return duration.count();
}

void performanceTest()
{
   const int NUM_OPERATIONS = 100000;

   // Generating random numnbers for consistent testing
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(1, NUM_OPERATIONS * 10);

   std::vector<int> keys(NUM_OPERATIONS);
   for (int i = 0; i < NUM_OPERATIONS; i++)
   {
      keys[i] = dis(gen);
   }

   // Insert performance
   MyMap<int, int> myMap;
   double myMapInsertTime = measureTime([&]()
   {
      for (int i = 0; i < NUM_OPERATIONS; i++) 
      {
         myMap.insert(keys[i], i);
      } 
   });

   std::unordered_map<int, int> map;
   double mapInsertTime = measureTime([&]()
   {
      for (int i = 0; i < NUM_OPERATIONS; i++) 
      {
         map[keys[i]] = i;
      } 
   });

   // Read operation performance
   double myMapLookupTime = measureTime([&]()
   {
      for (int i = 0; i < NUM_OPERATIONS; i++) 
      {  
         myMap.getValue(keys[i]);
      } 
   });

   double mapLookupTime = measureTime([&]()
   {
      for (int i = 0; i < NUM_OPERATIONS; i++) 
      {
         map[keys[i]];
      } 
   });

   // Print results
   std::cout << "\nPerformance Test Results (" << NUM_OPERATIONS << " operations):\n";
   std::cout << "----------------------------------------\n";
   std::cout << "Insert Performance:\n";
   std::cout << "MyMap: " << myMapInsertTime << " ms\n";
   std::cout << "std::unordered_map: " << mapInsertTime << " ms\n";
   std::cout << "----------------------------------------\n";
   std::cout << "Lookup Performance:\n";
   std::cout << "MyMap: " << myMapLookupTime << " ms\n";
   std::cout << "std::unordered_map: " << mapLookupTime << " ms\n";
   std::cout << "----------------------------------------\n";
}

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
   // Running original tests
   // testIntKey();
   // testDoubleKey();
   // testCharKey();
   // testStringKey();
   // testPointerKey();

   // Running performance comparisons
   std::cout << "\nStarting performance tests...\n";
   performanceTest();

   return 0;
}
