#include<bits/stdc++.h>
using namespace std;

/* HASHMAP IMPLEMENTATION USING SEPARATE CHAINING */

// each cell of the bucket is a LL
// the node of the LLs in the buckets array
template<class T>
class MapNode {
private:
    string key;
    T value;
    MapNode *next;
public:
    MapNode(string key, T value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }
    ~MapNode() {
        delete next;
    }
    string getKey() {
        return key;
    }
    T getValue() {
        return value;
    }
    void setValue(T value) {
        MapNode::value = value;
    }
    MapNode *getNext() {
        return next;
    }
    void setNext(MapNode *next) {
        MapNode::next = next;
    }
};

template<class V>
class MyMap {
private:
    MapNode<V> **buckets; // each index is the head of a LL
    int numBuckets;
    int count;

    int hash(string key) {
        int hashcode = 0;
        int power = 1;
        int p = 37;
        for(int i=key.size()-1 ; i>=0 ; i--) {
            hashcode = (hashcode + key[i] * power) % numBuckets;
            power = (power * p) % numBuckets;
        }
        return hashcode % numBuckets;
    }

    void rehash() {
        MapNode<V> **temp = buckets; // backup
        buckets = new MapNode<V> *[2 * numBuckets];
        for(int i=0 ; i<2*numBuckets ; i++) {
            buckets[i] = NULL;
        }
        int oldNumBuckets = numBuckets;
        numBuckets *= 2;
        count = 0;
        for(int i=0 ; i<oldNumBuckets ; i++) {
            MapNode<V> *head = temp[i];
            while(head != NULL) {
                string key = head->getKey();
                V value = head->getValue();
                insert(key, value);
                head = head->getNext();
            }
        }

        // now delete the unneeded temp array
        for(int i=0 ; i<oldNumBuckets ; i++) {
            delete temp[i];
        }
        delete []temp;
    }

public:
    MyMap() {
        // initialise the cells of the buckets as head of the LL
        count = 0;
        numBuckets = 5;
        buckets = new MapNode<V> *[numBuckets];
        for(int i=0 ; i<numBuckets ; i++) {
            buckets[i] = NULL;
        }
    }
    ~MyMap() {
        for(int i=0 ; i<numBuckets ; i++) {
            delete buckets[i]; // first delete each individual LL
        };
        // then the array
        delete []buckets;
    }
    
    int size() {
        return count;
    }

    V getValue(string key) {
        int bucketIndex = hash(key);
        MapNode<V> *head = buckets[bucketIndex];
        while(head != NULL) {
            if(head->getKey() == key) {
                return head->getValue();
            }
            head = head->getNext();
        }
        return 0;
    }

    void insert(string key, V value) {
        // if the key doesn't exist, then insert at the head
        // if it exists, overwrite
        int bucketIndex = hash(key);
        MapNode<V> *head = buckets[bucketIndex];

        while(head != NULL) {
            if(head->getKey() == key) {
                head->setValue(value);
                return;
            }
            head = head->getNext();
        }

        // if the end has been reached and the existing key hasn't been found
        MapNode<V> *newNode = new MapNode<V>(key, value);
        newNode->setNext(buckets[bucketIndex]);
        buckets[bucketIndex] = newNode;
        ++count; // count only when a new node has been inserted 
        double loadFactor = (1.0 * count) / numBuckets;
        // now check if there is a need to rehash
        if(loadFactor > 0.7) {
            rehash();
        }
    }

    void remove(string key) {
        int bucketIndex = hash(key);
        MapNode<V> *head = buckets[bucketIndex];
        MapNode<V> *prev = NULL;
        
        while(head != NULL && head->getKey() != key) {
            prev = head;
            head = head->getNext();
        }

        if(head == NULL) {
            // key not found
            return;
        }
        else {
            if(prev == NULL) {
                // the first node
                buckets[bucketIndex] = head->getNext();
            }
            else {
                prev->setNext(head->getNext());
            }
            --count;
            delete head;
        }
    }

    double getLoadFactor() {
        return (1.0 * count) / numBuckets;
    }
};

int main() {

    // INT VALUES

    MyMap<int> mp;
    for(int i=0 ; i<10 ; i++) {
        char c = '0' + i;
        string key = "abc";
        key += c;
        int value = i + 1;
        mp.insert(key, value);
    }
    cout << mp.size() << endl;
    for(int i=0 ; i<10 ; i++) {
        char c = i + '0';
        string key = "abc";
        key += c;
        cout << key << " - " << mp.getValue(key) << endl;
    }
    cout << endl;
    mp.remove("abc4");
    mp.remove("abc2");
    for(int i=0 ; i<10 ; i++) {
        char c = i + '0';
        string key = "abc";
        key += c;
        cout << key << " - " << mp.getValue(key) << endl;
    }
    cout << endl;



    // STRING VALUES

    MyMap<string> mps;
    mps.insert("abc0", "stu0");
    mps.insert("abc1", "stu1");
    mps.insert("abc2", "stu2");
    mps.insert("abc3", "stu3");
    cout << mps.size() << endl;
    cout << "abc0" << " - " << mps.getValue("abc0") << endl;
    cout << "abc1" << " - " << mps.getValue("abc1") << endl;
    cout << "abc2" << " - " << mps.getValue("abc2") << endl;
    cout << "abc3" << " - " << mps.getValue("abc3") << endl;

    mps.remove("abc3");
    cout << mps.size() << endl;
    cout << endl;



    // DOUBLE VALUES

    MyMap<double> mpd;
    mpd.insert("key1", 3.567);
    mpd.insert("key2", 8.256);
    mpd.insert("key3", 9.314);
    mpd.insert("key4", 8.456); 
    cout << mpd.size() << endl;
    for(int i=1 ; i<=4 ; i++) {
        char c = i + '0';
        string key = "key";
        key += c;
        cout << key << " - " << mpd.getValue(key) << endl;
    }
    mpd.remove("key4");
    cout << mpd.size() << endl;
    cout << "key4" << " - " << mpd.getValue("key4") << endl;
    return 0;
}