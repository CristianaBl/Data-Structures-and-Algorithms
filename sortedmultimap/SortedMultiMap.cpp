#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;
//b,a,w:theta(n);
SortedMultiMap::SortedMultiMap(Relation r) {
    m=10000;
    list_cap=8000;
    length=0;
    elements= new Node*[m];
    for(int i=0; i<m; i++){
        elements[i] = new Node();
        elements[i]->values=new TValue[list_cap];
        for(int j = 0; j < list_cap; ++j){
            elements[i]->values[j] = NULL_TVALUE;
        }
        elements[i]->list_length = 0;
        elements[i]->next= nullptr;
        elements[i]->key=NULL_TKEY;
    }
    relation=r;
}
//best: theta(1), average: theta(n),worst: theta(n)
void SortedMultiMap::add(TKey c, TValue v) {
    if (length >= m * 0.75) {
        resizeUp();
    }
    int h= hashf(c);
    Node* it=elements[h];
    while(it!= nullptr && c!=it->key)
        it=it->next;
    if(it!= nullptr){
        it->values[it->list_length++]=v;
        length++;
    }else
    {
        Node* prev= nullptr;
        Node* current= elements[h];
        while(current!= nullptr && relation(current->key,c)){
            prev=current;
            current=current->next;
        }
        Node* nod= new Node ;
        nod->key=c;
        nod->list_length=0;
        nod->values=new TValue [list_cap];
        nod->next= nullptr;
        nod->values[nod->list_length++]=v;

        if(prev == nullptr) {
            nod->next = current;
            elements[h] = nod;

        }
        else if(current == nullptr){
            prev->next=nod;
        }
        else {
            prev->next=nod;
            nod->next=current;
        }
        length++;
    }

}
//best: theta(1), a,w:theta(n^2)
vector<TValue> SortedMultiMap::search(TKey c) const {
    int h = hashf(c);
    vector<TValue> v;
    Node* it= elements[h];
    while (it!= nullptr  && c!=it->key)
    {
        it=it->next;

    }
    if(it== nullptr)
        return v;
    else
    {
        for(auto i=0; i < it->list_length; i++)
        {
            v.push_back(it->values[i]);
        }
        return v;
    }


}
//best:theta(1), a,w: theta(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    int h = hashf(c);
    Node* current = elements[h];
    Node* prev = nullptr;

    while (current != nullptr && current->key != c) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    bool found = false;
    int i;
    for (i = 0; i < current->list_length; ++i) {
        if (current->values[i] == v) {
            found = true;
            break;
        }
    }

    if (!found) {
        return false;
    }

    for (int j = i; j < current->list_length - 1; ++j) {
        current->values[j] = current->values[j + 1];
    }
    current->list_length--;
    length--;

    if (current->list_length == 0) {
        if (prev == nullptr) {

            elements[h] = current->next;
        } else {
            prev->next = current->next;
        }
        delete[] current->values;
        delete current;
    }


    return true;
}

//theta(1)
int SortedMultiMap::size() const {
    return length;
}
//theta(1)
bool SortedMultiMap::isEmpty() const {
    if (length==0)
        return true;
    else
        return false;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

void SortedMultiMap::resizeUp() {
    int newM = m * 2;
    Node** newElements = new Node*[newM];
    for (int i = 0; i < newM; i++) {
        newElements[i] = nullptr;
    }
    for (int i = 0; i < m; i++) {
        Node* current = elements[i];
        while (current != nullptr) {
            Node* next = current->next;
            int newHash = current->key % newM;
            current->next = newElements[newHash];
            newElements[newHash] = current;
            current = next;
        }
    }

    delete[] elements;

    elements = newElements;
    m = newM;
}

//theta(n^2)
SortedMultiMap::~SortedMultiMap() {

    for(int i = 0; i < m; i++) {
        Node* current = elements[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete[] current->values;
            delete current;
            current = next;
        }
    }
    delete[] elements;

}//modif in iterator el curent