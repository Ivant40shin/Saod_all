#pragma once
#include <iostream>



class LinkedList 
{
private:
    struct Node 
    {
        int data = 0;
        Node* next = nullptr;
    };

    Node* head = nullptr;

public:
    LinkedList();
    ~LinkedList();

    void addElement(int data);
    void mergeLists(LinkedList &list);
    void clear();
    void reverse();
    void removeLastElement();
    void removeNthElement(int n);
    LinkedList mergeSortedLists(LinkedList &list1, LinkedList &list2);
    void printList(); 
};