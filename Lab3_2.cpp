﻿#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct product_group //Описание партий товаров
{
    int volume;
    double price;
};

struct MyQueue //Описание очереди
{
    struct Node
    {
        product_group data;
        Node* next;
    };

    Node* First = NULL;
    int Count = 0;
    double income = 0;

    bool Push(product_group);
    bool Pop(product_group&);
    void Info();
};

bool MyQueue::Push(product_group dt) //Добавить партию
{
    if (!First)
    {
        First = new Node;
        First->next = NULL;
        First->data = dt;
        Count = 1;
    }
    else
    {
        Node* temp;
        temp = First;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new Node;
        temp->next->data = dt;
        temp->next->next = NULL;
        Count++;
    }
    return true;
}

bool MyQueue::Pop(product_group& dt) //Убрать партию 
{
    if (!First) return false;
    Node* temp = First->next;
    dt = First->data;
    delete First;
    First = temp;
    Count--;
    return true;
}

void MyQueue::Info() // Информация о объеме и цене первой партии и кол-ве партий
{
    if (!First) cout << "Склад пуст" << endl;
    else
    {
        cout << endl << "Информация о состоянии склада: " << endl;
        cout << "\tКоличество партий на складе = " << Count << endl;
        cout << "\tОбъем первой партии = " << First->data.volume << endl;
        cout << "\tСтоимость первой партии = " << First->data.price << endl << endl;
    }
}

bool check(MyQueue Q, product_group dt_x) //Проверка на возможность продажи партии
{
    product_group dt;
    MyQueue::Node* a;
    a = Q.First;
    int k = 0;
    while (k != Q.Count && a->data.price <= dt_x.price)
    {
        dt.price = a->data.price;
        dt.volume = a->data.volume;
        if (dt_x.volume <= dt.volume)
        {
            dt_x.volume = 0;
        }
        else
        {
            dt_x.volume -= dt.volume;
        }
        if (dt_x.volume == 0)
        {
            return true;
        }
        else
        {
            if (k < Q.Count)
            {
                k++;
                a = a->next;
            }
            else return false;
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    MyQueue Q;
    product_group dt;
    product_group dt_x;

    int m = 1;
    while (m)
    {
        Q.Info();

        cout << "1. Загрузка новой партии" << endl;
        cout << "2. Продажа партии" << endl;
        cout << "3. Отчет" << endl;
        cout << "0. Закончить рабочую сессию" << endl;
        cin >> m;

        switch (m)
        {
        case 1:
        {
            system("cls");
            cout << "Введите объем партии, а затем стоимость:" << endl;
            cout << "Объем = "; cin >> dt.volume;
            cout << "Стоимость = "; cin >> dt.price;
            Q.Push(dt);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Укажите объем покупки, а затем стоимость:" << endl;
            cout << "Объем = "; cin >> dt_x.volume;
            cout << "Стоимость = "; cin >> dt_x.price;
            dt = Q.First->data;
            if (check(Q, dt_x))
            {
                while (dt_x.volume)
                {
                    if (dt_x.volume <= dt.volume)
                    {
                        Q.income += dt_x.volume * (dt_x.price - dt.price);
                        dt.volume -= dt_x.volume;
                        dt_x.volume = 0;
                        Q.First->data.volume = dt.volume;
                    }
                    else
                    {
                        Q.income += dt.volume * (dt_x.price - dt.price);
                        dt_x.volume -= dt.volume;
                        dt.volume = 0;
                    }
                    if (dt.volume == 0)
                    {
                        Q.Pop(dt);
                        dt = Q.First->data;
                    }
                }
                cout << "Сделка заключена" << endl;
            }
            else cout << "Сделка отменена" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "Количество партий на складе = " << Q.Count << endl;
            cout << "Прибыль с продаж = " << Q.income << endl;
            system("pause");
            system("cls");
            break;
        }
        }
    }
}