#include<iostream>
#include <stdio.h>
#include <conio.h>   
#include <locale.h>
#define N 5
using namespace std;

void init(int a[N][N])    //Инициализация матрицы A с клавиатуры
{
    int i, j;
    cout << "Введите элементы матрицы А: \n";
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "]= ";
            cin >> a[i][j];
        }

}

void init_f(int a[N][N]) //Инициализация матрицы A из файла
{
    int i, j;
    FILE* fp;
    fopen_s(&fp, "in.txt", "r");
    if (fp)
    {
        for (i = 0;i < N;i++)
            for (j = 0;j < N;j++)
                fscanf_s(fp, "%d", &a[i][j]);
        fclose(fp);
    }
    else cout << "Ошибка открытия файла. \n";
}

int* mas_x(int(*a)[N], int* x,  //Заполнение массива X
    void (*pfunc)(int[N][N]))
{
    int i, k, md, dd;
    pfunc(a);//Вызов через указатель одной из двух функций ввода элементов a
    k = 4;
    md = 4;
    dd = 0;
    while (k > -1)
    {
        if (a[k][md] > a[k][dd]) //сравнение элементов главной и побочной диагонали
        {
            x[k] = 1;
        }
        else x[k] = -1;
        k = k - 1;
        md--;
        dd++;
    }
    return x;
}

int elem_y(int y, const int a[][N], int i) //Поиск величины Y
{
    if (i < N)
    {
        y = elem_y(y, a, i + 1);//Рекурсивная функция
        if (a[i][0] % 2 != 0)
        {
            y = y + 1;
        }
        return y;
    }
    else
    {
        y = 0;
        return y;
    }
}

void output(const int  y, const int x[], const int a[][N]) //Вывод на экран и в файл элементов матрицы А
{
    int i, j;
    FILE* fp;
    cout << "Матрица А:\n";
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    cout << "Массив Х:\n";
    for (i = 0;i < N;i++)
        cout << x[i] << " ";
    cout << "\n";
    if (y != 0)
    {
        cout << "Величина Y: " << y;
    }
    else
        cout << "Нет нечётных элементов в первом столбце матрицы.";
    fopen_s(&fp, "out.txt", "w");
    if (fp)
    {
        fprintf(fp, "Матрица А:\n");
        for (i = 0;i < N;i++)
        {
            for (j = 0;j < N;j++)
                fprintf(fp, "%5d", a[i][j]);
            fprintf(fp, "\n");
        }
        fprintf(fp, "Маccив X:\n");
        for (i = 0;i < N;i++)
            fprintf(fp, "%5d", x[i]);
        fprintf(fp, "\n");
        if (y != 0)
        {
            fprintf(fp, "Величина Y:");
            fprintf(fp, "%3d", y);
        }
        else
            fprintf(fp, "Нет нечётных элементов в первом столбце матрицы.");
        fclose(fp);
    }
    else cout << "Ошибка открытия. \n";
}

int main()
{
    setlocale(LC_CTYPE, "");
    int a[N][N], x[N], y, v;
    void (*pfunc)(int[N][N]);
    y = 0;
    do
    {
        cout << "Инициализация матрицы:\n1 - с клавиатуры\n2 - из файла\nВаш выбор: ";
        cin >> v;
    } while (v != 1 && v != 2);
    if (v == 1) pfunc = &init;// Присваивание указателю адреса одной из функций 
    else pfunc = &init_f;
    output(elem_y(y, a, 0), mas_x(a, x, pfunc), a);
    _getch();
}