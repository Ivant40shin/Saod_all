#include "LeftistHeap.h"
#include <iostream>

class LeftistHeap
{
private:
    struct Node
    {
        int data;
        int priority;
        Node* left;
        Node* right;


    };



};

/*
#include <iostream>

class PriorityQueue {
private:
    int* array;
    int size;

    void swap(int* a, int* b) {
        int temp = *b;
        *b = *a;
        *a = temp;
    }

    void heapify(int i) {
        if (size == 1) {
            std::cout << "В куче один элемент\n";
        }
        else {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            if (l < size && array[l] > array[largest])
                largest = l;
            if (r < size && array[r] > array[largest])
                largest = r;

            if (largest != i) {
                swap(&array[i], &array[largest]);
                heapify(largest);
            }
        }
    }

public:
    PriorityQueue() {
        array = new int[10];
        size = 0;
    }

    ~PriorityQueue() {
        delete[] array;
    }

    void insert(int newNum) {
        if (size == 0) {
            array[0] = newNum;
            size += 1;
        }
        else {
            array[size] = newNum;
            size += 1;
            for (int i = size / 2 - 1; i >= 0; i--) {
                heapify(i);
            }
        }
    }

    void deleteRoot(int num) {
        int i;
        for (i = 0; i < size; i++) {
            if (num == array[i])
                break;
        }

        swap(&array[i], &array[size - 1]);
        size -= 1;
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void printArray() {
        for (int i = 0; i < size; ++i)
            std::cout << array[i] << " ";
        std::cout << "\n";
    }
};

int main() {
    system("chcp 1251");
    PriorityQueue pq;

    pq.insert(3);
    pq.insert(4);
    pq.insert(9);
    pq.insert(5);
    pq.insert(2);

    std::cout << "Массив max-heap: ";
    pq.printArray();

    pq.deleteRoot(4);

    std::cout << "После удаления элемента: ";
    pq.printArray();

    return 0;
}
*/