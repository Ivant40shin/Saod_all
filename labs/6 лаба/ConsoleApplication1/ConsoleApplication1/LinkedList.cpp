#include "LinkedList.h"

LinkedList::LinkedList() 
{
    head = nullptr;
}

LinkedList::~LinkedList() 
{
    clear();
}

void LinkedList::addElement(int data) 
{
    if (head == nullptr) 
    {
        head = new Node();
        head->data = data;
    }
    else 
    {
        Node* current = head;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = new Node();
        current->next->data = data;
    }
}

void LinkedList::mergeLists(LinkedList& list) {
    if (head == nullptr) 
    {
        head = list.head;
    }
    else 
    {
        Node* current = head;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = list.head;
    }
    list.head = nullptr;
}

void LinkedList::clear() 
{
    while (head != nullptr) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::reverse() 
{
    Node* previous = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) 
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    head = previous;
}

void LinkedList::removeLastElement() 
{
    if (head == nullptr) 
    {
        return;
    }

    if (head->next == nullptr) 
    {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;
    while (current->next->next != nullptr) 
    {
        current = current->next;
    }

    delete current->next;
    current->next = nullptr;
}

void LinkedList::removeNthElement(int n) 
{
    if (head == nullptr || n <= 0) 
    {
        return;
    }

    if (n == 1) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    int count = 1;

    while (current != nullptr && count < n - 1) 
    {
        current = current->next;
        count++;
    }

    if (current == nullptr || current->next == nullptr) 
    {
        return;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    delete temp;
}

LinkedList LinkedList::mergeSortedLists(LinkedList& list1, LinkedList& list2) 
{
    LinkedList mergedList;

    Node* current1 = list1.head;
    Node* current2 = list2.head;

    while (current1 != nullptr && current2 != nullptr) 
    {
        if (current1->data <= current2->data) 
        {
            mergedList.addElement(current1->data);
            current1 = current1->next;
        }
        else 
        {
            mergedList.addElement(current2->data);
            current2 = current2->next;
        }
    }

    while (current1 != nullptr) 
    {
        mergedList.addElement(current1->data);
        current1 = current1->next;
    }

    while (current2 != nullptr) 
    {
        mergedList.addElement(current2->data);
        current2 = current2->next;
    }

    return mergedList;
}

void LinkedList::printList() 
{
    Node* current = head;
    while (current != nullptr) 
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}