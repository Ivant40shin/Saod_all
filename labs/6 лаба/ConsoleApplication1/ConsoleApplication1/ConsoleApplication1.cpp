#include "LinkedList.h"

/*
6. Напишите алгоритм и программу следующих операций:
– добавление элемента к концу списка;                                +
– сцепление двух списков;                                            +
– освобождение всех элементов в списке;                              +
– инвертирование списка (первый элемент становится последним и т.д.);+
– удаление последнего элемента из списка;                            -
– удаление n-го элемента из списка;                                  -
– объединение двух упорядоченных списков в один упорядоченный список -
*/

int main() 
{
    LinkedList list1;
    list1.addElement(1);
    list1.addElement(3);
    list1.addElement(5);

    list1.printList();

    // Добавление элемента к концу списка
    list1.addElement(7);
    list1.printList();

    LinkedList list2;
    list2.addElement(2);
    list2.addElement(4);
    list2.addElement(6);

    list2.printList();

    // Сцепление двух списков
    list1.mergeLists(list2);
    list1.printList();

    // Освобождение всех элементов в списке
    list2.clear();
    list2.printList();

    // Инвертирование списка
    list1.reverse();
    list1.printList();

    // Удаление последнего элемента из списка
    list1.removeLastElement();
    list1.printList();

    // Удаление n-го элемента из списка
    list1.removeNthElement(2);
    list1.printList();

    list1.clear();

    list1.addElement(1);
    list1.addElement(3);
    list1.addElement(5);
    list1.addElement(5);
    list1.addElement(5);
    list1.printList();


    // Объединение двух упорядоченных списков в один упорядоченный список
    LinkedList list3;
    list3.addElement(2);
    list3.addElement(2);
    list3.addElement(4);
    list3.addElement(4);
    list3.addElement(6);
    list3.printList();

    LinkedList sortedList = sortedList.mergeSortedLists(list1, list3);
    sortedList.printList();

    return 0;
}