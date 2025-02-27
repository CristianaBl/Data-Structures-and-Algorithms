#include <stdexcept>
#include "IndexedList.h"
#include "ListIterator.h"
//tetha(1)
IndexedList::IndexedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}
//best,worst,average case: tetha(1)
int IndexedList::size() const {
	return length;
}

//best,worst,average case: tetha(1)
bool IndexedList::isEmpty() const {
	return length == 0;
}
//best:tetha(1),worst:tetha(n),average:tetha(n)
TElem IndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= length)
        throw std::out_of_range("Invalid position");

    DLLNode* current;
    if (pos < length / 2) {
        current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int i = length - 1; i > pos; i--) {
            current = current->prev;
        }
    }
    return current->data;
}
//best:tetha(1),worst:tetha(n),average:tetha(n)
TElem IndexedList::setElement(int pos, TElem e) {
    if (pos < 0 || pos >= length)
        throw std::out_of_range("Invalid position");

    DLLNode* current = head;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    TElem old = current->data;
    current->data = e;
    return old;
}
//best:tetha(1),
void IndexedList::addToEnd(TElem e) {
    DLLNode* newNode = new DLLNode;
    newNode->data = e;
    newNode->next = nullptr;
    newNode->prev = tail;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}
//best:tetha(1), worst:tetha(n), average: tetha(n)
void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > length)
        throw std::out_of_range("Invalid position");

    if (pos == length) {
        addToEnd(e);
        return;
    }

    DLLNode* newNode = new DLLNode{ e, nullptr, nullptr };
    if (pos == 0) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else {
        DLLNode* current = head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }
    length++;
}
//best:tetha(1), worst:tetha(n), average:tetha(n)
TElem IndexedList::remove(int pos) {
    if (pos < 0 || pos >= length) {
        throw std::out_of_range("Invalid position");
    }
    TElem removedValue;
    if (length == 1) {
        removedValue = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
    } else if (pos == 0) {
        removedValue = head->data;
        DLLNode* nextNode = head->next;
        nextNode->prev = nullptr;
        delete head;
        head = nextNode;
    } else if (pos == length - 1) {
        removedValue = tail->data;
        DLLNode* prevNode = tail->prev;
        prevNode->next = nullptr;
        delete tail;
        tail = prevNode;
    } else {
        DLLNode* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }
        removedValue = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
    length--;
    return removedValue;
}
//worst:tetha(n), best:tetha(1), av:tetha(n)
int IndexedList::search(TElem e) const{
    DLLNode* current = head;
    int pos = 0;
    while (current != nullptr) {
        if (current->data == e)
            return pos;
        current = current->next;
        pos++;
    }
    return -1;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}
//worst:tetha(n), best:tetha(1)
IndexedList::~IndexedList() {
    while (head != nullptr) {
        DLLNode* nextNode = head->next;
        delete head;
        head=nextNode;
    }
    tail= nullptr;
    length=0;
}
//tetha(n)
void IndexedList::addAll(const IndexedList& otherList) {
    ListIterator it = otherList.iterator();
    while (it.valid()) {
        TElem element = it.getCurrent();
        addToEnd(element);
        it.next();
        length++;
    }
}