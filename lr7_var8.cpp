#include<iostream>
#include <stdio.h>
#include <conio.h>   
#include <locale.h>
#define N 5
using namespace std;

void init(int a[N][N])    //������������� ������� A � ����������
{
    int i, j;
    cout << "������� �������� ������� �: \n";
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "]= ";
            cin >> a[i][j];
        }

}

void init_f(int a[N][N]) //������������� ������� A �� �����
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
    else cout << "������ �������� �����. \n";
}

int* mas_x(int(*a)[N], int* x,  //���������� ������� X
    void (*pfunc)(int[N][N]))
{
    int i, k, md, dd;
    pfunc(a);//����� ����� ��������� ����� �� ���� ������� ����� ��������� a
    k = 4;
    md = 4;
    dd = 0;
    while (k > -1)
    {
        if (a[k][md] > a[k][dd]) //��������� ��������� ������� � �������� ���������
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

void output(const int x[], const int a[][N]) //����� �� ����� � � ���� ��������� ������� �
{
    int i, j;
    FILE* fp;
    cout << "������� �:\n";
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    cout << "������ �:\n";
    for (i = 0;i < N;i++)
        cout << x[i] << " ";
    cout << "\n";
    fopen_s(&fp, "out.txt", "w");
    if (fp)
    {
        fprintf(fp, "������� �:\n");
        for (i = 0;i < N;i++)
        {
            for (j = 0;j < N;j++)
                fprintf(fp, "%5d", a[i][j]);
            fprintf(fp, "\n");
        }
        fprintf(fp, "��cc�� X:\n");
        for (i = 0;i < N;i++)
            fprintf(fp, "%5d", x[i]);
        fprintf(fp, "\n");
        fclose(fp);
    }
    else cout << "������ ��������. \n";
}

int main()
{
    setlocale(LC_CTYPE, "");
    int a[N][N], x[N], y, v, p;
    void (*pfunc)(int[N][N]);
    y = p = 0;
    do
    {
        cout << "������������� �������:\n1 - � ����������\n2 - �� �����\n��� �����: ";
        cin >> v;
    } while (v != 1 && v != 2);
    if (v == 1) pfunc = &init;// ������������ ��������� ������ ����� �� ������� 
    else pfunc = &init_f;
    output(mas_x(a, x, pfunc), a);
    _getch();
}