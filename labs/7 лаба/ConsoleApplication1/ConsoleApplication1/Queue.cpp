#include "queue.h"
#include <iostream>

Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() 
{
    while (!isEmpty()) 
    {
        dequeue();
    }
}

bool Queue::isEmpty() const 
{
    return front == nullptr;
}

void Queue::enqueue(int value) 
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty()) 
    {
        front = newNode;
        rear = newNode;
    }
    else 
    {
        rear->next = newNode;
        rear = newNode;
    }
}

void Queue::enqueueFront(int value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        newNode->next = front;
        front = newNode;
    }
}

void Queue::dequeue() 
{
    if (isEmpty()) 
    {
        return;
    }

    Node* temp = front;
    front = front->next;
    delete temp;

    if (front == nullptr) 
    {
        rear = nullptr;
    }
}

int Queue::getFront() const 
{
    return front->data;
}

int Queue::getRear() const 
{
    return rear->data;
}

void Queue::print() const 
{
    if (isEmpty()) 
    {
        std::cout << "Queue is empty.";
        return;
    }

    Node* current = front;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
}