#include <iostream>
using namespace std;

/*
11. Придумать несколько алгоритмов и сравнить их порядок
сложности в лучшем, среднем и худшем случаях для решения
следующей задачи.
Даны m наборов, каждый из которых состоит из n чисел. В
каждом наборе можно переставлять цифры произвольным образом,
получая при этом некоторое число. Необходимо проверить, можно
ли сформировать из этих наборов возрастающую
последовательность чисел.
Комментарий 1: для улучшения быстродействия необходимо
подумать в сторону различных вариантов отсечения.
Комментарий 2: так же стоит заметить, что перебирать все
комбинации не обязательно, достаточно на каждом этапе
формировать минимальное из возможных чисел, превосходящее
предыдущее в последовательности

Пример входных данных Результат
{8,1} {8,2} {5,6} {4,7} 18 28 56 74
{9,3,8} {1,3,2} {3,7,2} Сформировать последовательность нельзя

*/

void swap(int* x, int* y) 
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void BubbleSort(int arr[], int length)
{
    for (int i = 0; i < length; i++)
        for (int j = 0; j < length - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

int Сoncatenate(int arr[], int n) 
{
    int result = 0;
    for (int i = 0; i < n; i++) 
    {
        int temp = arr[i];
        while (temp > 0) 
        {
            result *= 10;
            temp /= 10;
        }
        result += arr[i];
    }
    return result;
}

void FillArrayInSet(int arr[], int n, int result) 
{
    for (int i = n - 1; i >= 0; i--) 
    {
        arr[i] = result % 10;
        result /= 10;
    }
}

void Permute(int* arr, int l, int r, int minNum, int* minGreaterNum) 
{
    if (l == r) 
    {
        int number = 0;
        for (int i = 0; i <= r; i++) 
        {
            number = number * 10 + arr[i];
        }
        if (number > minNum && (number < *minGreaterNum || *minGreaterNum == -1)) 
        {
            *minGreaterNum = number;
        }
    }
    else 
    {
        for (int i = l; i <= r; i++) 
        {
            swap(&arr[l], &arr[i]);
            Permute(arr, l + 1, r, minNum, minGreaterNum);
            swap(&arr[l], &arr[i]);
        }
    }
}

int FindMinGreaterNum(int* arr, int size, int minNum) 
{
    int minGreaterNum = -1;
    Permute(arr, 0, size - 1, minNum, &minGreaterNum);
    return minGreaterNum;
}

void PrintArray(int arr[][3], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf_s(" %d", arr[i][j]);
        }
        printf_s("  ");
    }
}

void SortAllSet(int arr[][3], int m, int n) 
{
    for (int i = 0; i < m - 1; i++)
    {
        if (Сoncatenate(arr[i], n) > Сoncatenate(arr[i + 1], n))
        {
            int temp = FindMinGreaterNum(arr[i + 1], n, Сoncatenate(arr[i], n));
            if (temp == -1)
            {
                printf_s("Нельзя сформировать последовательность\n");
                return;
            }
            else
            {
                FillArrayInSet(arr[i+1], n, temp);
            }
        }
    }
    PrintArray(arr, m, n);
}

int main()
{
    system("chcp 1251 & cls");

    const int m = 4, n = 3;

    int arr[m][n] = { {1,3,8},{2,3,2},{1,7,2},{4,7,3} };
    //int arr[m][n] = { {9,3,8},{1,3,2},{3,7,2},{6,3,2} };
    
    PrintArray(arr, m, n);
    cout << "\n";

    for (int i = 0; i < m; i++)
        BubbleSort(arr[i], n);

    SortAllSet(arr, m, n);
    cout << "\n\n";
    return 0;
}

/*
Сложность алгоритма зависит от нескольких функций в коде.

BubbleSort: Это стандартный алгоритм сортировки пузырьком, который имеет 
квадратичную сложность во всех трех случаях: лучшем, среднем и худшем. 
Таким образом, сложность этого алгоритма составляет O(n^2).

Permute: Эта функция генерирует все возможные перестановки массива. 
В худшем случае количество перестановок массива из n элементов равно n!. 
Таким образом, сложность этого алгоритма составляет O(n!).

FindMinGreaterNum: Эта функция вызывает функцию permute, поэтому ее 
сложность также составляет O(n!).

sortAllSet: Эта функция вызывает функции BubbleSort и findMinGreaterNum 
для каждого подмассива в двумерном массиве. Поэтому в худшем случае сложность 
этой функции составляет O(m * (n^2 + n!)), где m - количество подмассивов, 
а n - размер каждого подмассива.

Таким образом, в худшем и среднем случае сложность всего алгоритма будет определяться 
как O(m * (n^2 + n!)). В лучшем: O(m * (n^2)), если все элементы уже будут стоять в 
порядке возрастания.
*/
