#include<bits/stdc++.h>
using namespace std;

/* HASHMAP IMPLEMENTATION USING SEPARATE HASHING */

// each cell of the bucket is a LL
// the node of the LLs in the buckets array
template<class T>
class MapNode {
public:
    string key;
    T value;
    MapNode *next;
    MapNode(string key, T value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }
    ~MapNode() {
        delete next;
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
            hashcode += key[i] * power;
            power *= p;
            hashcode %= numBuckets;
            power %= numBuckets;
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
                string key = head->key;
                V value = head->value;
                insert(key, value);
                head = head->next;
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
            if(head->key == key) {
                return head->value;
            }
            head = head->next;
        }
        return 0;
    }

    void insert(string key, V value) {
        // if the key doesn't exist, then insert at the head
        // if it exists, overwrite
        int bucketIndex = hash(key);
        MapNode<V> *head = buckets[bucketIndex];

        while(head != NULL) {
            if(head->key == key) {
                head->value = value;
                return;
            }
            head = head->next;
        }

        // if the end has been reached and the existing key hasn't been found
        MapNode<V> *newNode = new MapNode<V>(key, value);
        newNode->next = buckets[bucketIndex];
        buckets[bucketIndex] = newNode;
        ++count; // count only when a new node has been inserted 
        double loadFactor = (1.0 * count) / numBuckets;
        // now check if there is a need to rehash
        if(loadFactor > 0.7) {
            rehash();
        }
    }

    // remove and return the value
    void remove(string key) {
        int bucketIndex = hash(key);
        MapNode<V> *head = buckets[bucketIndex];
        MapNode<V> *prev = NULL;

        // while(head != NULL) {
        //     if(head->key == key) {
        //         if(prev == NULL) {
        //         // if the first node has to be removed
        //             buckets[bucketIndex] = head->next;
        //         }
        //         else {
        //             prev->next = head->next;
        //         }
        //         V value = head->value; // delete node, return value
        //         head->next = NULL;
        //         delete head;
        //         --count; // decrease count as one of the nodes has been deleted
        //     }
        //     prev = head;
        //     head = head->next;
        // }
        
    }

    double getLoadFactor() {
        return (1.0 * count) / numBuckets;
    }
};

int main() {
    // inserting some int values
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
        cout << key << " " << mp.getValue(key) << endl;
    }
    cout << endl;
    mp.remove("abc4");
    mp.remove("abc2");
    for(int i=0 ; i<10 ; i++) {
        char c = i + '0';
        string key = "abc";
        key += c;
        cout << key << " " << mp.getValue(key) << endl;
    }
    cout << endl << endl;

    // inserting some string values
    MyMap<string> mps;
    for(int i=0 ; i<9 ; i++) {
        string val = "stu";
        char c = i + 1 + '0';
        val += c;
        string key = "abc";
        char s = i + '0';
        key += s;
        mps.insert(key, val);
    }
    cout << mps.size() << endl;
    for(int i=0 ; i<9 ; i++) {
        string key = "abc";
        char s = i + '0';
        key += s;
        cout <<  key << " " << mps.getValue(key) << endl;
    }
    cout << endl;
    mps.remove("abc0");
    mps.remove("abc7");
    // for(int i=0 ; i<10 ; i++) {
    //     string key = "abc";
    //     char s = i + '0';
    //     key += s;
    //     cout <<  key << " " << mps.getValue(key) << endl;
    // }
    cout << mps.getValue("abc7");
    return 0;
}