#include <iostream>
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
    for (int i = 0; i <= n1_size; i++) data[i] = d1[i];
    for (int i = 0; i <= n2; i++) data[i + n1_size] = d2[i];
    for (int i = 0; i <= n3; i++) data[i + n1_size + n2] = d3[i];
    for (int i = 0; i <= n4; i++) data[i + n1_size + n2 + n3] = d4[i];
    for (int i = 0; i <= n5; i++) data[i + n1_size + n2 + n3 + n4] = d5[i];
}

void PrintBinaryFile(char* data, int n)
{
    fstream f_out("data.dat", ios::app | ios::binary);
    f_out.write((char*)&n, sizeof(int));
    f_out.write(data, n);
    f_out.close();
}

int main()
{
    char* data;
    int n = 0;
    flower A[3] =
    {
      {"Donut", 4.5, 1, true},
      {"Dendy", 8.3, 2, false},
      {"Pudge", 6.6, 3, true}
    };
    for (int i = 0; i < 3; i++)
    {
        GetSeria(data, n, A[i]);
        PrintBinaryFile(data, n);
        delete[] data;
    }
}
