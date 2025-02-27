#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>
//best: theta( n^2 ), average: theta( n^3 ), worst:theta( n^3 )
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    elems = new TElem[map.length + 2];
    len = 0;
    index = 0;

    for (int i = 0; i < map.m; ++i) {
        Node* currentKeyMap = map.elements[i];


        while (currentKeyMap != nullptr) {
            int k = 0, j = 0, newIndex = 0;
            TElem* temp = new TElem[len + currentKeyMap->list_length];


            while (k < len || j < currentKeyMap->list_length) {
                if (k < len && (j >= currentKeyMap->list_length || map.relation(elems[k].first, currentKeyMap->key))) {
                    temp[newIndex] = elems[k];
                    k++;
                } else {
                    temp[newIndex] = { currentKeyMap->key, currentKeyMap->values[j] };
                    j++;
                }
                newIndex++;
            }

            delete[] elems;
            elems = temp;
            len = newIndex;

            currentKeyMap = currentKeyMap->next;
        }
    }
}
//best,worst,average:thetaa(1)
void SMMIterator::first() {
    index = 0;
}
//best,worst,average:theta(1)
void SMMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    index++;
}
//best,worst,average:theta(1)
bool SMMIterator::valid() const {
    return index < len;
}
//best,worst,average:theta(1)
TElem SMMIterator::getCurrent() const {
    if (!valid())
        throw std::exception();
    return elems[index];
}
//worst, average, best:theta(n)
void SMMIterator::modifycurrent(TValue* newValues, TKey newKey) {
    if(index>len)
        throw std::exception();

    elems[index].first = newKey;
    Node* currentKeyMap = map.elements[index];
    for (int i = 0; i < currentKeyMap->list_length; ++i) {
        currentKeyMap->values[i] = newValues[i];//trecem noile valori ale cheii
    }
    //interclasarea elem pt a le sorta acum ca s-a schimbat cheia
    while (currentKeyMap != nullptr) {
        int k = 0, j = 0, newIndex = 0;
        TElem* temp = new TElem[len + currentKeyMap->list_length];

        while (k < len || j < currentKeyMap->list_length) {
            if (k < len && (j >= currentKeyMap->list_length || map.relation(elems[k].first, currentKeyMap->key))) {
                temp[newIndex] = elems[k];
                k++;
            } else {
                temp[newIndex] = { currentKeyMap->key, currentKeyMap->values[j] };
                j++;
            }
            newIndex++;
        }

        currentKeyMap = currentKeyMap->next;
    }
}
