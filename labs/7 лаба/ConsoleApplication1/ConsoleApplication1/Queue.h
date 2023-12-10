#pragma once

class Queue 
{
private:
    struct Node 
    {
        int data;
        Node* next;
    };

    Node* front;  // Указатель на первый элемент очереди
    Node* rear;   // Указатель на последний элемент очереди

public:
    // Конструктор
    Queue();

    // Деструктор
    ~Queue();

    // Проверяет, является ли очередь пустой
    bool isEmpty() const;

    // Добавляет элемент в конец очереди
    void enqueue(int value);

    // Добавляет элемент в начало очереди
    void enqueueFront(int value);

    // Удаляет первый элемент из очереди
    void dequeue();

    // Возвращает значение первого элемента в очереди
    int getFront() const;

    // Возвращает значение последнего элемента в очереди
    int getRear() const;

    // Печатает содержимое очереди
    void print() const;
};