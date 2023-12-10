#include <iostream>
#include "Ring.h"
using namespace std;

/*
Есть двунаправленный кольцевой список, выполнить
1. Перемещение по списку влево, вправо
2. Добавление/удаление элементов в любом месте списка
3. Поиск элементов по значению
*/

int main()
{
    system("chcp 1251 & cls");
    RingList ringList;

    // Добавление элементов в список
    ringList.AddElement(0, 10);
    ringList.AddElement(1, 20);
    ringList.AddElement(2, 30);
    ringList.AddElement(3, 40);

    ringList.PrintRing(); // Ожидаемый вывод: 10 20 30 40

   
    ringList.MoveRight(); // Перемещение вправо
    ringList.PrintRing(); // Ожидаемый вывод: 20 30 40 10

    ringList.MoveLeft();  // Перемещение влево
    ringList.PrintRing(); // Ожидаемый вывод: 10 20 30 40

    
    ringList.AddElement(2, 25); // Добавление элемента на 2 позицию
    ringList.PrintRing(); // Ожидаемый вывод: 10 20 25 30 40

    ringList.AddElement(0, 70); // Добавление элемента на 12 позицию
    ringList.PrintRing(); // т.к. 12 % 5 == 2, то ожидаемый вывод: 10 20 70 25 30 40
    
    ringList.DeleteElement(0); // Удаление элемента на 1 позиции
    ringList.PrintRing(); // Ожидаемый вывод: 10 70 25 30 40

    // Поиск элемента
    int digit = 70;
    int pos = ringList.SearchElement(digit);
    if (pos != -1)
        cout << "Элемент " << digit << " найден на позиции: " << pos << endl;
    else
        cout << "Элемент " << digit << " не найден." << endl;
    
    return 0;
}