﻿#include <iostream>
#include <fstream>
using namespace std;

struct magazine {
    int Price=0, pages=0, year=0;
    string name;

    void out();
    bool IsEqual(magazine);
};

struct MyStack
{
  struct Node
  {
    magazine data;
    Node *prev;
  };
  Node *Top = NULL;
  int Count=0;

  bool Push(magazine);
  bool Pop(magazine&);
  void Info();
  void clear(magazine&);
};

void magazine::out(){
    cout<<"Информация о журнале:"
        <<"\tЦена - "<<Price<<endl
        <<"\tКоличество страниц - "<< pages <<endl
        <<"\tНазвание - "<< name <<endl
        <<"\tГод выпуска - "<< year <<endl;
}

bool magazine::IsEqual(magazine a){
    if (a.Price == Price && a.pages == pages && a.name == name && a.year == year) return true;
    return false;
}

bool MyStack::Push(magazine data)
{
  if(!Top)
  {
    Top = new Node;
    Top -> prev = NULL;
    Count = 1;
  }
  else
  {
    Node *temp;
    temp = new Node;
    temp -> prev = Top;
    Top = temp;
    Count++;
  }
  Top -> data = data;
  return true;
}

bool MyStack::Pop(magazine&data)
{
  if(!Top) return false;
  Node *temp = Top -> prev;
  data = Top -> data;
  delete Top;
  Top = temp;
  Count--;
  return true;
}

void MyStack::Info()
{
  if(!Top) cout << "Stack is empty" << endl;
  else
  {
    cout << endl << "Stack info: " << endl;
    cout << "Stack size = " << Count << endl;
    Top->data.out();
  }
}

void MyStack::clear(magazine& k){
  while (Count !=0) Pop(k);
}

void read(MyStack&,string);
void FindCr(MyStack&, magazine);

int main()
{
    setlocale(LC_ALL, "Russian");
    magazine k;
    magazine find;
    MyStack S;
    read(S,"text.txt");
    int choice;


    do{
        cout << "1. Посмотреть информацию о верхнем журнале" << endl;
        cout << "2. Добавить новый журнал" << endl;
        cout << "3. Найти журнал" << endl;
        cout << "4. Очистить корзину с журналами" << endl;
        cout << "0. Выход" << endl;

        cin>>choice;

        switch(choice){
        case 1:{
            system("cls");
            S.Info();
            system("pause");
            system("cls");
            break;
        }

        case 2: {
        system("cls");
        cout << "Введите цену: "; cin >> k.Price;
        cout << "Введите количество страниц: "; cin >> k.pages;
        cout << "Введите название: "; cin >> k.name;
        cout << "Введите год выпуска: "; cin >> k.year;
        S.Push(k);
        system("cls");
        break;
        }

        case 3:{
        system("cls");
        cout << "Введите цену: "; cin >> find.Price;
        cout << "Введите количество страниц: "; cin >> find.pages;
        cout << "Введите название: "; cin >> find.name;
        cout << "Введите год выпуска: "; cin >> find.year;
        FindCr(S,find);
        system("cls");
        break;
        }

        case 4:{
        S.clear(k);
        system("cls");
        }

        case 0: {  
        S.clear(k);
        break;
        }

        }
    }while(choice!=0);
}

void read(MyStack& S,string FileName){
ifstream F(FileName);

if (!F) {
cout << "Ошибка при загрузке базы журналов. Не найден файл" << endl << endl;
return;
}

magazine cr;

while(F>>cr.Price>>cr.pages >>cr.name >>cr.year) S.Push(cr);

F.close();
}

void FindCr(MyStack& S, magazine find){
    magazine cr;
    MyStack second;
    while(S.Count != 0 && !(S.Top->data.IsEqual(find))){
        S.Pop(cr);
        second.Push(cr);
    }
    if(S.Count!=0){
        cout<<"Журнал найден"<<endl;
        S.Pop(cr);
        system("pause");
        system("cls");
    }
    else cout<<"Журнал не найден"<<endl;
    while(second.Pop(cr)) S.Push(cr);
    system("pause");
    system("cls");
}