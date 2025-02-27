#include "PriorityQueue.h"
#include <stdexcept>
#include <iostream>
using namespace std;

//tetha(n)
PriorityQueue::PriorityQueue(Relation r) {
    capacity = 10000;
    size = 0;
    head = -1;
    relation = r;
    elements = new Node[capacity];
    for(int i = 0; i < capacity; ++i){
        elements[i].next = i+1;

    }
    elements[capacity-1].next = -1;
    firstEmpty = 0;//idx first empty elem
}

//best,worst, average:theta(1)
void PriorityQueue::push(TElem e, TPriority p) {
    if (size + 1 > capacity) { // dacă adăugarea noului element depășește capacitatea
        ResizeUp(); // redimensionăm capacitatea
    }
    if(head == -1){
        elements[firstEmpty].data.first = e;
        elements[firstEmpty].data.second = p;
        head = firstEmpty;
        firstEmpty = elements[firstEmpty].next;
        elements[head].next=-1;
        size++;
        return;

    }
    if(relation(p, elements[head].data.second)){
        elements[firstEmpty].data.first = e;
        elements[firstEmpty].data.second = p;
        int urm = elements[firstEmpty].next;
        elements[firstEmpty].next = head;
        head = firstEmpty;
        firstEmpty = urm;
        size++;
        return;
    }


    //la mijloc
    int prev = -1, current = head;
    while(current != -1 && relation(elements[current].data.second, p)){
        prev = current;
        current = elements[current].next;
    }
    if(current != -1){
        elements[firstEmpty].data.first = e;
        elements[firstEmpty].data.second = p;
        elements[prev].next = firstEmpty;
        int urm = elements[firstEmpty].next;
        elements[firstEmpty].next = current;
        firstEmpty = urm;
        size++;
    }else{
        //la sfarsit
        elements[firstEmpty].data.first = e;
        elements[firstEmpty].data.second = p;
        elements[prev].next = firstEmpty;
        int urm = elements[firstEmpty].next;
        elements[firstEmpty].next = -1;
        firstEmpty = urm;
        size++;
    }

}
//best,worst,average:theta(1)
//throws exception if the queue is empty
Element PriorityQueue::top() const {
    if(head == -1)
        throw std::logic_error("Queue is empty.");
    return elements[head].data;
}

//best:Theta(1), worst: Theta(n), avrage: O(n)
Element PriorityQueue::pop() {
    if (head == -1) {
        throw std::logic_error("Queue is empty.");
    }

    Element removedElement = elements[head].data;
    int prev = head;
    head = elements[head].next;
    elements[prev].next = firstEmpty;
    firstEmpty = prev;
    size--;

    return removedElement;
}

void PriorityQueue::ResizeUp() {
    int newCapacity = capacity * 2;
    Node* newElements = new Node[newCapacity];

    for (int i = 0; i < capacity; ++i) {
        newElements[i] = elements[i];
    }
    for (int i = capacity; i < newCapacity; ++i) { // Fixed loop condition
        newElements[i].next = i + 1;
    }
    newElements[newCapacity - 1].next = -1;

    head = 0;
    firstEmpty = capacity;

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

void PriorityQueue::ResizeDown() {
    int newCapacity = capacity / 2;
    Node* newElements = new Node[newCapacity];

    for (int i = 0; i < capacity; ++i) { // Fixed loop condition
        newElements[i] = elements[i];
    }

    head = 0;
    firstEmpty = capacity;

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

bool PriorityQueue::isEmpty() const {
    return head == -1;
}


PriorityQueue::~PriorityQueue() {
    delete[] elements;
};
