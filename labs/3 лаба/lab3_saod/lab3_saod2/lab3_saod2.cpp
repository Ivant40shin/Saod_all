#include <iostream>
using namespace std;

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

void InsertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

bool NextPermutation(int* arr, int size)
{
    for (int i = size - 2; i >= 0; i--)
    {
        if (arr[i] < arr[i + 1])
        {
            for (int j = size - 1; j > i; j--)
            {
                if (arr[j] > arr[i])
                {
                    swap(arr[i], arr[j]);
                    reverse(arr + i + 1, arr + size);
                    return true;
                }
            }
        }
    }
    return false;
}

void SortAllSet(int arr[][3], int m, int n)
{
    for (int i = 0; i < m; i++)
        InsertionSort(arr[i], n);

    for (int i = 0; i < m - 1; i++)
    {
        while (true) {
            if (!NextPermutation(arr[i + 1], n)) {
                cout << "Нельзя сформировать последовательность\n";
                return;
            }
            if (Сoncatenate(arr[i], n) < Сoncatenate(arr[i + 1], n))
                break;
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

    SortAllSet(arr, m, n);
    cout << "\n\n";

    return 0;
}