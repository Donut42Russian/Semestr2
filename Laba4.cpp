﻿#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct flower
{
    string name;
    double weight = 0.0;
    int age = 0;
    bool thirst;
    void out();
};

void flower::out()
{
    cout << "Weight: " << weight << endl << " " << "Age: " << age << endl << "Name: " << name << endl << "Thirst?: " << thirst << endl;
}

struct MyQueue
{
    struct Node
    {
        char* data;
        int n;
        Node* next;
    };
    Node* First = NULL;
    int Count = 0;

    bool Push(char*, int n);
    bool Pop(char*&, int& n);
    void Info();
};
bool MyQueue::Push(char* data, int n)
{

    if (!First)
    {
        First = new Node;
        First->next = NULL;
        First->data = new char[n];
        First->n = n;
        for (int i = 0; i < n; i++) (First->data)[i] = data[i];
        Count = 1;
    }
    else
    {
        Node* temp;
        temp = First;
        while (temp->next != NULL) temp = temp->next;
        temp->next = new Node;
        temp->next->data = new char[n];
        temp->next->n = n;
        for (int i = 0; i < n; i++) (temp->next->data)[i] = data[i];
        temp->next->next = NULL;
        Count++;
    }
    return true;
}
bool MyQueue::Pop(char*& data, int& n)
{
    if (!First) return false;
    Node* temp = First->next;
    data = new char[n];
    n = First->n;
    for (int i = 0; i < First->n; i++) data[i] = (First->data)[i];
    delete[](First->data);
    delete First;
    First = temp;
    Count--;
    return true;
}
void MyQueue::Info()
{
    if (!First) cout << "Queue is empty" << endl;
    else
    {
        cout << endl << "Queue info: " << endl;
        cout << "\tQueue size = " << Count << endl;
        //cout << First->data.
    }
}

void GetDeSeria(char*, int, flower&);
void GetSeria(char*&, int&, flower);
bool InputBinaryFile(MyQueue&);

int main()
{
    MyQueue Q;
    char* data;
    int n = 0;
    int m = 1;
    flower A;
    InputBinaryFile(Q);
    while (m)
    {
        Q.Info();
        cout << "1. Add an flower to the queue" << endl;
        cout << "2. Pull out an flower from queue" << endl;
        cout << "3. Clear the queue" << endl;
        cout << "0. Exit" << endl;
        cin >> m;
        switch (m)
        {
        case 1:
        {
            system("cls");
            cout << "Enter flower characteristics:" << endl;
            cout << "Name = "; cin >> A.name;
            cout << "Weight = "; cin >> A.weight;
            cout << "Age = "; cin >> A.age;
            cout << "Thirst?(True=1, False=0) "; cin >> A.thirst;
            GetSeria(data, n, A);
            Q.Push(data, n);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            flower A_x;
            bool metka = false;
            cout << "Enter flower characteristics:" << endl;
            cout << "Name = "; cin >> A_x.name;
            cout << "Weight = "; cin >> A_x.weight;
            cout << "Age = "; cin >> A_x.age;
            cout << "Thitst?(True=1, False=0) "; cin >> A_x.thirst;
            int Y = Q.Count;
            for (int i = 0; i < Y; i++)
            {
                Q.Pop(data, n);
                GetDeSeria(data, n, A);
                delete[] data;
                if (A.name != A_x.name || A.weight != A_x.weight || A.age != A_x.age || A.thirst != A_x.thirst)
                {
                    GetSeria(data, n, A);
                    Q.Push(data, n);
                }
                else
                {
                    metka = true;
                    break;
                }
            }
            if (!metka) cout << "Flower not found" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            while (Q.Count)
            {
                Q.Pop(data, n);
                GetDeSeria(data, n, A);
                delete[] data;

                cout << "Name = " << A.name << endl;
                cout << "Weight = " << A.weight << endl;
                cout << "Age = " << A.age << endl;
                cout << "Thirst?(True=1, False=0) " << A.thirst << endl << endl;;
            }
            system("pause");
            system("cls");
            break;
        }
        }
    }
    while (Q.Count)
    {
        Q.Pop(data, n);
        delete[] data;
    }
}

void GetSeria(char*& data, int& n, flower A)
{
    size_t s1 = A.name.size();
    int n1_size = sizeof(size_t);
    int n2 = s1;
    int n3 = sizeof(double);
    int n4 = sizeof(int);
    int n5 = sizeof(bool);
    n = n1_size + n2 + n3 + n4 + n5;
    data = new char[n];
    char* d1 = reinterpret_cast<char*> (&s1);
    char* d2 = const_cast<char*> (A.name.c_str());
    char* d3 = reinterpret_cast<char*> (&A.weight);
    char* d4 = reinterpret_cast<char*> (&A.age);
    char* d5 = reinterpret_cast<char*> (&A.thirst);
    for (int i = 0; i < n1_size; i++) data[i] = d1[i];
    for (int i = 0; i < n2; i++) data[i + n1_size] = d2[i];
    for (int i = 0; i < n3; i++) data[i + n1_size + n2] = d3[i];
    for (int i = 0; i < n4; i++) data[i + n1_size + n2 + n3] = d4[i];
    for (int i = 0; i < n5; i++) data[i + n1_size + n2 + n3 + n4] = d5[i];
}
void GetDeSeria(char* data, int n, flower& A)
{
    int n1_size, n2, n3, n4, n5;
    n1_size = sizeof(size_t);
    n3 = sizeof(double);
    n4 = sizeof(int);
    n5 = sizeof(bool);
    size_t p = *reinterpret_cast<size_t*> (data);
    n2 = p;
    string s1(data + n1_size, p);
    A.name = s1;
    A.weight = *reinterpret_cast<double*> (data + n1_size + n2);
    A.age = *reinterpret_cast<int*> (data + n1_size + n2 + n3);
    A.thirst = *reinterpret_cast<bool*> (data + n1_size + n2 + n3 + n4);
}
bool InputBinaryFile(MyQueue& Q)
{
    fstream f_in("data.dat", ios::in | ios::binary);
    if (!f_in)
    {
        cout << "No binary file" << endl;
        return false;
    }
    flower A;
    int n = 0;
    while (!f_in.eof())
    {
        if (f_in.read((char*)&n, sizeof(int)))
        {
            char* data = new char[n];
            f_in.read(data, n);
            GetDeSeria(data, n, A);
            delete[] data;
            GetSeria(data, n, A);
            Q.Push(data, n);
        }
    }
    f_in.close();
    return true;
}