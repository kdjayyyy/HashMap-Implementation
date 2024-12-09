#ifndef MYMAP_HPP
#define MYMAP_HPP

#include "MapNode.hpp"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>
#include <memory>


template <typename KeyType, typename ValueType, typename HashFunction = std::hash<KeyType>>
class MyMap
{
private:
   MapNode<KeyType, ValueType> **buckets;
   int numBuckets;
   int count;
   HashFunction hashFunction;

   int hash(const KeyType &key) const;

   void rehash();

public:
   MyMap();
   ~MyMap();

   int size() const;
   ValueType getValue(const KeyType &key) const;
   void insert(const KeyType &key, const ValueType &value);
   void remove(const KeyType &key);
   double getLoadFactor() const;
};


// Constructor
template <typename KeyType, typename ValueType, typename HashFunction>
MyMap<KeyType, ValueType, HashFunction>::MyMap()
    : numBuckets(5), count(0)
{
   buckets = new MapNode<KeyType, ValueType> *[numBuckets];
   for (int i = 0; i < numBuckets; i++)
   {
      buckets[i] = nullptr;
   }
}


// Destructor
template <typename KeyType, typename ValueType, typename HashFunction>
MyMap<KeyType, ValueType, HashFunction>::~MyMap()
{
   for (int i = 0; i < numBuckets; i++)
   {
      MapNode<KeyType, ValueType> *head = buckets[i];
      while (head != nullptr)
      {
         MapNode<KeyType, ValueType> *next = head->getNext();
         delete head;
         head = next;
      }
   }
   delete[] buckets;
}


// Default hash function using std::hash
template <typename KeyType, typename ValueType, typename HashFunction>
int MyMap<KeyType, ValueType, HashFunction>::hash(const KeyType &key) const
{
   return hashFunction(key) % numBuckets;
}


// Rehash function to resize the buckets when load factor exceeds threshold
template <typename KeyType, typename ValueType, typename HashFunction>
void MyMap<KeyType, ValueType, HashFunction>::rehash()
{
   MapNode<KeyType, ValueType> **oldBuckets = buckets;
   int oldNumBuckets = numBuckets;

   numBuckets *= 2;
   buckets = new MapNode<KeyType, ValueType> *[numBuckets];
   for (int i = 0; i < numBuckets; i++)
   {
      buckets[i] = nullptr;
   }
   count = 0;

   for (int i = 0; i < oldNumBuckets; i++)
   {
      MapNode<KeyType, ValueType> *head = oldBuckets[i];
      while (head != nullptr)
      {
         insert(head->getKey(), head->getValue());
         MapNode<KeyType, ValueType> *next = head->getNext();
         delete head;
         head = next;
      }
   }
   delete[] oldBuckets;
}


// Insert or update key-value pair
template <typename KeyType, typename ValueType, typename HashFunction>
void MyMap<KeyType, ValueType, HashFunction>::insert(const KeyType &key, const ValueType &value)
{
   int bucketIndex = hash(key);
   MapNode<KeyType, ValueType> *head = buckets[bucketIndex];

   while (head != nullptr)
   {
      if (head->getKey() == key)
      {
         head->setValue(value);
         return;
      }
      head = head->getNext();
   }

   MapNode<KeyType, ValueType> *newNode = new MapNode<KeyType, ValueType>(key, value);
   newNode->setNext(buckets[bucketIndex]);
   buckets[bucketIndex] = newNode;
   count++;

   if (getLoadFactor() > 0.7)
   {
      rehash();
   }
}


// Remove key-value pair
template <typename KeyType, typename ValueType, typename HashFunction>
void MyMap<KeyType, ValueType, HashFunction>::remove(const KeyType &key)
{
   int bucketIndex = hash(key);
   MapNode<KeyType, ValueType> *head = buckets[bucketIndex];
   MapNode<KeyType, ValueType> *prev = nullptr;

   while (head != nullptr && head->getKey() != key)
   {
      prev = head;
      head = head->getNext();
   }

   if (head == nullptr)
   {
      throw std::runtime_error("Key not found");
   }

   if (prev == nullptr)
   {
      buckets[bucketIndex] = head->getNext();
   }
   else
   {
      prev->setNext(head->getNext());
   }
   delete head;
   count--;
}


// Get current load factor
template <typename KeyType, typename ValueType, typename HashFunction>
double MyMap<KeyType, ValueType, HashFunction>::getLoadFactor() const
{
   return (1.0 * count) / numBuckets;
}


// Get size of the map
template <typename KeyType, typename ValueType, typename HashFunction>
int MyMap<KeyType, ValueType, HashFunction>::size() const
{
   return count;
}


// Get value by key
template <typename KeyType, typename ValueType, typename HashFunction>
ValueType MyMap<KeyType, ValueType, HashFunction>::getValue(const KeyType &key) const
{
   int bucketIndex = hash(key);
   MapNode<KeyType, ValueType> *head = buckets[bucketIndex];
   while (head != nullptr)
   {
      if (head->getKey() == key)
      {
         return head->getValue();
      }
      head = head->getNext();
   }
   return ValueType(); // Default constructed value if key not found
}


#endif // MYMAP_HPP

