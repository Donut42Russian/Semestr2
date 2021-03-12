#include <iostream>
#include <iomanip>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

int error_checking(); //Проверка количества файлов

int GetN(); //Ввод размерности матрицы

void NewMatr(double**& M, int n, int m);//Создание матрицы
void DelMatr(double**& M, int n, int m);//Удаление матрицы
void PrintMatr(double** M, int n, int m, const char* namematr);//Вывод матрицы 
void PrintVect(double* x, int n, const char* namematr);//Вывод вектора решений
void Mult(double** M1, double** M2, int n1, int m1, int n2, int m2);

bool minor(double**& M, int n, int m, double& Det);//Вычисление текущего минора
void reshuffle(double**& M, int n, int m, int k, double& Det);//Перестановка строк и столбцов 
bool Solve(double**& M, double* x, int n, int m, double& Det);//Решение матрицы методом Гаусса(методом текущего минора?)
double det(double** M, int n, int m);//Нахождение определителя 

void choose(double**& M, int n, int m);//Выбор матрицы для решения
void clone(double**& M, int n, int m, double** M1);//Клонирование матрицы
double check(double** M1, int n, int m, double* x);//Проверка качества решения
bool reverb(double** A, int n, int m, double& Det, double**& rev);//Создание обратной матрицы

using namespace std;

int main() //Меню программы
{
    setlocale(LC_ALL, "Russian");

    int proof = error_checking(); //Проверка внешнего файла
    if (!proof)
    {
        cout << "Данные файла неверны" << endl;
        return 0;
    }

    cout << "Домашняя работа." << endl;

    int score = 0;
    int n;
    double Det = 1;

    cout << "Введите размер матрицы. ";
    n = GetN();

    while (score != 5)//Счетчик на 5, чтобы показать на демонстрации 5 матриц
    {
        int m = n + 1;
        double** A;
        double** A1;
        double** rev;
        double* x = new double[n];

        NewMatr(A, n, m);
        choose(A, n, m);

        NewMatr(A1, n, m);
        clone(A, n, m, A1);

        NewMatr(rev, n, n);
        PrintMatr(A, n, m, "A");

        if (Solve(A, x, n, m, Det))
        {
            PrintVect(x, n, "x");
            cout << "Эпсилон погрешности = " << check(A1, n, m, x) << endl << endl; //эпсилон
        }
        else cout << "Нет решений" << endl;
        cout << "Определитель матрицы = " << Det * det(A, n, m) << endl;
        if (reverb(A1, n, m, Det, rev))
        {
            PrintMatr(rev, n, n, "Обратная матрица:");
            Mult(A1, rev, n, m - 1, n, n);
        }
        else cout << "Нет обратной" << endl;

        DelMatr(A, n, m);//Очистка памяти
        DelMatr(A1, n, m);
        DelMatr(rev, n, n);
        delete[] x;
        x = NULL;

        score += 1;
    }
    return 0; // Конец работы
}

void choose(double**& M, int n, int m)
{
    int k;
    cout << "Выберите тип матрицы для задания: " << endl;
    cout << "1. Матрица, заданная явно" << endl;
    cout << "2. Матрица, заданная случайным образом" << endl;
    cout << "3. Единичная матрица" << endl;
    cout << "4. Нулевая матрица" << endl;
    cout << "5. Матрица Гильберта" << endl;
    cin >> k;

    switch (k)
    {
    case 1:
    {
        fstream A("arr.txt", ios::in);//Матрица из файла
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                A >> M[i][j];
        A.close();
        break;
    }

    case 2:
    {
        double a, b;//Случайная матрица

        srand((unsigned)time(NULL));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                M[i][j] = ((rand() % 101) - 50); //генерация вещественных в промежутке (-50, 51)
            }

        /*srand(time(0));
        a = -10;
        b = 10;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                M[i][j] = a + ((double)rand() / RAND_MAX) * (b - a);
            }*/
        break;
    }

    case 3:
    {
        for (int i = 0; i < n; i++)//Единичная матрица
            for (int j = 0; j < m; j++)
                if (i == j) M[i][j] = 1;
                else M[i][j] = 0;
        break;
    }

    case 4:
    {
        for (int i = 0; i < n; i++)//Вырожденная матрица
            for (int j = 0; j < m; j++)
                M[i][j] = 0;
        break;
    }

    case 5:
    {
        for (int i = 0; i < n; i++)//Матрица Гильберта ("Плохая" матрица)
            for (int j = 0; j < m; j++)
                M[i][j] = 1. / (i + j + 1);
        break;
    }
    }
}

int GetN()
{
    float n;

    do
    {
        cout << "Введите целое число: ";
        cin >> n;
        if (n <= 0 || (n - (int)n))
            cout << "Ошибка, попробуйте снова..." << endl;
    } while (n <= 0 || (n - (int)n));

    return n;
}

void NewMatr(double**& M, int n, int m)
{
    M = new double* [n];

    for (int i = 0; i < n; i++)
        M[i] = new double[m];
}

void DelMatr(double**& M, int n, int m)
{
    for (int i = 0; i < n; i++)
        delete[] M[i];

    delete[] M;
}

void PrintMatr(double** M, int n, int m, const char* namematr)
{
    cout << endl << " " << namematr << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << setw(15) << M[i][j];
        cout << endl;
    }
    cout << endl;
}

void PrintVect(double* x, int n, const char* namematr)
{
    cout << endl << " " << namematr << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << x[i];
        cout << endl;
    }
    cout << endl;
}

void reshuffle(double**& M, int n, int m, int k, double& Det)
{
    for (int i = k + 1; i < n; i++)
    {
        if (M[i][k] != 0)
        {
            double temp;
            for (int i1 = 0; i1 < m; i1++)
            {
                temp = M[k][i1];
                M[k][i1] = M[i][i1];
                M[i][i1] = temp;
            }
            Det *= -1;
            break;
        }
    }
}

bool minor(double**& M, int n, int m, double& Det)
{
    for (int i = 0; i < n; i++)
    {
        if (M[i][i] == 0) reshuffle(M, n, m, i, Det);
        if (M[i][i] == 0) return false;
        for (int i1 = i + 1; i1 < n; i1++)
            for (int i2 = i + 1; i2 < m; i2++)
                M[i1][i2] = M[i][i] * M[i1][i2] - M[i][i2] * M[i1][i];
        for (int j = i + 1; j < n; j++)
        {
            M[j][i] = 0;
        }
    }

    return true;
}

bool Solve(double**& M, double* x, int n, int m, double& Det)
{
    double res = 0;

    if (!minor(M, n, m, Det)) return false;

    for (int i = n - 1; i >= 0; i--)
    {
        res = 0;
        for (int j = i + 1; j <= n - 1; j++)
            res = res - x[j] * M[i][j];
        res += M[i][n];
        x[i] = res / M[i][i];
    }

    return true;
}

double det(double** M, int n, int m)
{
    double det = 1;

    for (int i = 0; i < n; i++)
    {
        if (M[i][i] == 0) return 0;
        det *= M[i][i] / pow(M[i][i], n - 1 - i);
    }

    return det;
}

void clone(double**& M, int n, int m, double** M1)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            M1[i][j] = M[i][j];
}

double check(double** M1, int n, int m, double* x)
{
    long double epsilon = 0;
    double s;

    for (int i = 0; i < n; i++)
    {
        s = 0;
        for (int k = 0; k < m - 1; k++)
            s += M1[i][k] * x[k];
        if (fabs(M1[i][m - 1] - s) > epsilon) 
            epsilon = fabs(M1[i][m - 1] - s);
    }

    return epsilon;
}

bool reverb(double** M, int n, int m, double& Det, double**& rev)
{
    double* x = new double[n];
    bool metka = true;

    for (int i = 0; i < n; i++)
    {
        double** buff;
        NewMatr(buff, n, m);
        clone(M, n, m, buff);
        for (int j = 0; j < n; j++)
        {
            if (i == j) buff[j][m - 1] = 1;
            else buff[j][m - 1] = 0;
        }
        if (!Solve(buff, x, n, m, Det)) metka = false;
        for (int j = 0; j < n; j++)
            rev[j][i] = x[j];
        DelMatr(buff, n, m);
    }

    delete[] x;
    x = NULL;
    return metka;
}

void Mult(double** M1, double** M2, int n1, int m1, int n2, int m2)
{
    double** buff;
    NewMatr(buff, n1, m2);
    double S;
    if (m1 != n2)
    {
        cout << "Ошибка" << endl;
        DelMatr(buff, n1, m2);
    }
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m2; j++)
        {
            S = 0;
            for (int k = 0; k < m1; k++)
                S += M1[i][k] * M2[k][j];
            buff[i][j] = S;
        }
    PrintMatr(buff, n1, m2, "проверка");
    DelMatr(buff, n1, m2);
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