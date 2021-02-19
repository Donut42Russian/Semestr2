#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

int error_checking(); //Проверка количества файлов

void fillarr(double* arr, int n); // Основные действия с массивом
void printarr(double* arr, int n);
double* createarr(int n);
void reassign(double*& arr, int& n, int k, double number);
void del(double*& arr, int& n, int k);
void printarr(double* arr, int n);

double choose(); // Выбор рандомного ввода числа или с экрана

void task1_2_3(double*& arr, int& n); // Задания
void task4_5_6(double*& arr, int& n);
void task7(double*& arr, int& n);
void task8(double*& arr, int& n);

using namespace std;

int main() //Меню программы
{
    setlocale(LC_ALL, "Russian");

    int n = error_checking(); //Проверка внешнего файла
    if (!n)
    {
        cout << "Данные файла неверны" << endl;
        return 0;
    }

    cout << "Начальный массив:" << endl;
    double* arr = createarr(n); //Создание, наполнение и вывод массива
    fillarr(arr, n);
    printarr(arr, n);

    int choice; //Меню выбора
    cout << "Домашняя работа." << endl;
    do
    {
        cout << endl;
        cout << "Выберите задание из предложенного списка:" << endl;
        cout << "1. Задания 1, 2, 3. Добавить элемент в конец массива. Добавить элемент в начало массивa. Добавить элемент на k - ую позицию в массиве; " << endl;
        cout << "2. Заданиея 1, 2, 3. Удалить элемент в конце массива. Удалить элемент в начале массивa. Удалить элемент на k - ой позиции в массиве;" << endl;
        cout << "3. Задание 7. Добавить элемент массива после первого встреченного элемента с заданным значением, если такого значения нет, то выдать предупреждающее сообщение; " << endl;
        cout << "4. Задание 8. Удалить все элементы массива с заданным значением, если такого значения нет, то выдать предупреждающее сообщение;" << endl;
        cout << "0. Завершение программы" << endl;

        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            task1_2_3(arr, n);
            break;
        case 2:
            task4_5_6(arr, n);
            break;
        case 3:
            task7(arr, n);
            break;
        case 4:
            task8(arr, n);
            break;
        case 0:
            cout << "Работа завершена";
            break;
        default:
            cout << "Неправильно введен номер задания. Попробуйте снова..." << endl;
            break;
        }

    } while (choice != 0);
    delete[] arr;
}
void task1_2_3(double*& arr, int& n)
{
    double number;
    number = choose();

    unsigned int k;
    cout << "Введите номер позиции для вставки: "; 
    cin >> k;
    reassign(arr, n, k, number);
    printarr(arr, n);
}


void task4_5_6(double*& arr, int& n)
{
    unsigned int k;
    cout << "Введите номер позиции для удаления: "; 
    cin >> k;
    del(arr, n, k);
    printarr(arr, n);
}


void task7(double*& arr, int& n)
{
    double x, number;
    cout << "Введите элемент, после котороего вы хотите добавить элемент: "; cin >> x;
    number = choose();

    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            k = i + 1;
            break;
        }
    }
    if (k > 0)
    {
        double* buff = new double[n + 1];
        for (int i = 0; i < k; i++)
        {
            buff[i] = arr[i];
        }
        n++;
        buff[k] = number;
        for (int i = k + 1; i < n; i++)
        {
            buff[i] = arr[i - 1];
        }
        delete[] arr;
        arr = buff;
    }
    else cout << "Элемент не найден." << endl;
    printarr(arr, n);
}

void task8(double*& arr, int& n)
{
    double x;
    cout << "Введите номер для удаления: " << endl;
    cin >> x;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            k++;
        }
    }
    if (k > 0)
    {
        k = 0;
        double* buff = new double[n - k];
        for (int i = 0; i < n; i++)
        {
            if (arr[i] == x)
            {
                k++;
            }
            else buff[i - k] = arr[i];
        }
        n -= k;
        delete[] arr;
        arr = buff;
    }
    else cout << "Элемент не найден." << endl;
    printarr(arr, n);
}

double choose()
{
    int m = 1;
    double a = -10, b = 10;
    double number;
    cout << "Какое число использовать?" << endl;
    cout << "1 -- Случайное" << endl;
    cout << "2 -- Ввести с экрана" << endl;
    cin >> m;
    switch (m)
    {
        case 1:
        {
            srand((unsigned)time(NULL));
            number = ((double)rand() / RAND_MAX)+ ((rand() % 101) - 50); //генерация вещественных в промежутке (-50, 51)
            m = 0;
            break;
        }
        case 2:
        {
            cout << "Введите число: ";
            cin >> number;
            m = 0;
            break;
        }
        default:
        {
            cout << "Ошибка, попробуйте снова." << endl;
            break;
        }
    }
    return number;
}

void fillarr(double* arr, int n)
{
    fstream A("arr.txt", ios::in);
    for (int i = 0; i < n; i++)
    {
        A >> arr[i];
    }
    A.close();
}

double* createarr(int n)
{
    double* arr = new double[n];
    return arr;
}

void reassign(double*& arr, int& n, int k, double number)
{
    k--;
    if (k >= 0 && k <= n)
    {
        double* buff = new double[n + 1];
        for (int i = 0; i < k; i++)
            buff[i] = arr[i];
        buff[k] = number;
        n++;
        for (int i = k + 1; i < n; i++)
            buff[i] = arr[i - 1];
        delete[] arr;
        arr = buff;
    }
    else cout << "error";
}

void del(double*& arr, int& n, int k)
{
    k--;
    if (k >= 0 && k <= n)
    {
        double* buff = new double[n - 1];
        for (int i = 0; i < k; i++)
            buff[i] = arr[i];
        n--;
        for (int i = k; i < n; i++)
            buff[i] = arr[i + 1];
        delete[] arr;
        arr = buff;
    }
    else cout << "error";
}

void printarr(double* arr, int n) //Вывод массива
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int error_checking()
{
    double a;
    int k = 0;
    fstream A("arr.txt", ios::in);
    while (A >> a)
    {
        k++;
    }
    A.close();
    return k;
}