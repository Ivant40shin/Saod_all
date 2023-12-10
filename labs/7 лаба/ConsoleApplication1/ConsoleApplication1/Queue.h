#pragma once

class Queue 
{
private:
    struct Node 
    {
        int data;
        Node* next;
    };

    Node* front;  // ��������� �� ������ ������� �������
    Node* rear;   // ��������� �� ��������� ������� �������

public:
    // �����������
    Queue();

    // ����������
    ~Queue();

    // ���������, �������� �� ������� ������
    bool isEmpty() const;

    // ��������� ������� � ����� �������
    void enqueue(int value);

    // ��������� ������� � ������ �������
    void enqueueFront(int value);

    // ������� ������ ������� �� �������
    void dequeue();

    // ���������� �������� ������� �������� � �������
    int getFront() const;

    // ���������� �������� ���������� �������� � �������
    int getRear() const;

    // �������� ���������� �������
    void print() const;
};