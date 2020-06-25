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

void output(int a[][N], void (*pfunc)(int[N][N])) //Вывод на экран и в файл элементов матрицы А
{
    int i, j;
    FILE* fp;
    pfunc(a);
    cout << "Матрица А:\n";
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
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
        fclose(fp);
    }
    else cout << "Ошибка открытия. \n";
}

int main()
{
    setlocale(LC_CTYPE, "");
    int a[N][N], x[N], y, v, p;
    void (*pfunc)(int[N][N]);
    y = p = 0;
    do
    {
        cout << "Инициализация матрицы:\n1 - с клавиатуры\n2 - из файла\nВаш выбор: ";
        cin >> v;
    } while (v != 1 && v != 2);
    if (v == 1) pfunc = &init;// Присваивание указателю адреса одной из функций 
    else pfunc = &init_f;
    output(a,pfunc);
    _getch();
}