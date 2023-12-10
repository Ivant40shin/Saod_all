#include <iostream>
#include "queue.h"
using namespace std;
/*
Задачи для выполнения на ЭВМ имеют различные
приоритеты, задаваемые цифрами от 1 до 5 (5–высший приоритет).
Для каждого приоритета образуется отдельная очередь. Приоритет
задач может меняться. При повышении приоритета задание
помещается в конец другой очереди, а при понижении – в начало.
Составить программу, обеспечивающую:
a) выдачу общей очереди;
б) выдачу очереди заданного приоритета;
в) перестройку очередей при изменении приоритета.
*/

class PriorityQueue
{
private:
    Queue priority_[5];

public:

    //добавляет задачу с указанным приоритетом
    void addTask(int priority, int value)
    {
        // Проверка на допустимый диапазон приоритета
        if (priority < 1 || priority > 5)
        {
            cout << "Ошибка: недопустимый приоритет задачи!" << endl;
            return;
        }

        // Добавление задачи в соответствующую очередь с указанным приоритетом
        priority_[priority - 1].enqueue(value);
    }

    //б) выдача очереди заданного приоритета
    void printTasksWithPriority(int priority)
    {
        // Проверка на допустимый диапазон приоритета
        if (priority < 1 || priority > 5)
        {
            cout << "Ошибка: недопустимый приоритет задачи!" << endl;
            return;
        }

        // Вывод очереди заданного приоритета
        priority_[priority - 1].print();
    }

    //удалить выполненную задачу
    void removeCompletedTask(int priority)
    {
        // Проверка на допустимый диапазон приоритета
        if (priority < 1 || priority > 5)
        {
            cout << "Ошибка: недопустимый приоритет задачи!" << endl;
            return;
        }

        // Удаление выполненной задачи из очереди с указанным приоритетом
        priority_[priority - 1].dequeue();

    }

    // в) перестройка очередей при изменении приоритета.  (меняет приоритет задачи)
    void changeTaskPriority(int taskPriority, int newPriority)
    {
        // Проверка на допустимые диапазоны приоритетов
        if (taskPriority < 1 || taskPriority > 5 || newPriority < 1 || newPriority > 5)
        {
            cout << "Ошибка: недопустимый приоритет задачи!" << endl;
            return;
        }

        int task = priority_[taskPriority - 1].getFront();

        if (taskPriority != newPriority)
        priority_[taskPriority - 1].dequeue();

		if (taskPriority < newPriority)
			priority_[newPriority - 1].enqueue(task);  // Добавляем задачу в конец очереди с более высоким приоритетом
		else if (taskPriority > newPriority)
			priority_[newPriority - 1].enqueueFront(task);  // Добавляем задачу в начало очереди с более низким приоритетом
    }

    //a) выдача общей очереди;
    void printAllTasks()
    {
        for (int i = 4; i >= 0; i--)
        {
            if(!priority_[i].isEmpty())
                priority_[i].print();
        }
    }
};


int main()
{
    system("chcp 1251");
    PriorityQueue priorityQueue;

    // Добавляем задачи с различными приоритетами
    priorityQueue.addTask(1, 1);
    priorityQueue.addTask(1, 3);
    priorityQueue.addTask(1, 2);

    priorityQueue.addTask(2, 4);
    priorityQueue.addTask(2, 5);
    priorityQueue.addTask(2, 6);

    priorityQueue.addTask(3, 9);
    priorityQueue.addTask(3, 8);
    priorityQueue.addTask(3, 7);

    //priorityQueue.addTask(4, 10);

    priorityQueue.addTask(5, 11);
    priorityQueue.addTask(5, 12);

    for (int i = 1; i <= 5; i++) 
    {
    cout << "Очередь с приоритетом " << i << ":" << endl;
    priorityQueue.printTasksWithPriority(i);
    cout << endl;
    }

    cout << "Очередь с приоритетом 3 (после удаления выполненной задачи): " << endl;
    priorityQueue.removeCompletedTask(3);
    priorityQueue.printTasksWithPriority(3);
    cout << endl;
    
    cout << "Общая очередь:" << endl;
    priorityQueue.printAllTasks();
    cout << endl;

    cout << "Общая очередь после понижения приоритета текущей задачи из pr3 в pr1:" << endl;
    priorityQueue.changeTaskPriority(3, 1);
    priorityQueue.printAllTasks();
    cout << endl;

    cout << "Общая очередь после повышения приоритета текущей задачи из pr1 в pr5:" << endl;
    priorityQueue.changeTaskPriority(1, 5);
    priorityQueue.printAllTasks();
    cout << endl;

    return 0;
}

/*
Пример приоритетов и очередей
pr1={1,3,2}
pr2={4,5,6}
pr3={8,7}
pr4={}
pr5={11,12}
pr={11,12},{},{8,7},{4,5,6},{1,3,2}

пример понижения приоритета текущей задачи из pr3 в pr1
pr1={8,1,3,2}
pr2={4,5,6}
pr3={7}
pr4={}
pr5={11,12}
pr={11,12},{},{7},{4,5,6},{8,1,3,2}

пример повышения приоритета текущей задачи из pr1 в pr5
pr1={1,3,2}
pr2={4,5,6}
pr3={7}
pr4={}
pr5={11,12,8}
pr={11,12,8},{},{7},{4,5,6},{1,3,2}
*/