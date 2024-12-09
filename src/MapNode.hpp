#ifndef MAPNODE_H
#define MAPNODE_H

#include <string>

template <typename KeyType, typename ValueType>
class MapNode
{
private:
   KeyType key;
   ValueType value;
   MapNode *next;

public:
   // Constructor
   MapNode(const KeyType &key, const ValueType &value)
       : key(key), value(value), next(nullptr) {}

   // Destructor
   ~MapNode() = default;

   // Getters
   KeyType getKey() const { return key; }
   ValueType getValue() const { return value; }
   MapNode *getNext() const { return next; }

   // Setters
   void setValue(const ValueType &value) { this->value = value; }
   void setNext(MapNode *next) { this->next = next; }
};

#endif // MAPNODE_H
