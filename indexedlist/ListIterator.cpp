#include "ListIterator.h"
#include "IndexedList.h"
#include <stdexcept>
using namespace std;

ListIterator::ListIterator(const IndexedList& list) : list(list){
    current = list.head;
}

void ListIterator::first(){
    current = list.head;
}

void ListIterator::next(){
    if (!valid()) {
        throw std::out_of_range("Iterator not valid");
    }
    current = current->next;
}

bool ListIterator::valid() const{
    return current != nullptr;
}

TElem ListIterator::getCurrent() const{
    if (!valid())
        throw out_of_range("Iterator is not valid");
    return current->data;
}