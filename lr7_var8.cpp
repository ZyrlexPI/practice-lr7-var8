#include<iostream>
#include <stdio.h>
#include <conio.h>   
#include <locale.h>
#define N 5
using namespace std;

void init(int a[N][N])    //Initializing matrix A from the keyboard
{
    int i, j;
    cout << "Enter the matrix elements A: \n";
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "]= ";
            cin >> a[i][j];
        }

}

void init_f(int a[N][N]) //Initializing matrix A from a file
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
    else cout << "Error opening the file. \n";
}

int* mas_x(int(*a)[N], int* x,  //Filling in the x array
    void (*pfunc)(int[N][N]))
{
    int i, k, md, dd;
    pfunc(a);//Calling one of the two matrix a initialization functions via a pointer
    k = 4;
    md = 4;
    dd = 0;
    while (k > -1)
    {
        if (a[k][md] > a[k][dd]) //A comparison of the elements of the primary and secondary diagonal
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

int elem_y(int y, const int a[][N], int i) //Search for the y value
{
    if (i < N)
    {
        y = elem_y(y, a, i + 1);//Recursive function
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
    cout << "The Matrix A:\n";
    for (i = 0;i < N;i++)
    {
        for (j = 0;j < N;j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    cout << "The Array X:\n";
    for (i = 0;i < N;i++)
        cout << x[i] << " ";
    cout << "\n";
    if (y != 0)
    {
        cout << "The Value Of Y: " << y;
    }
    else
        cout << "There are no odd elements in the first column of the matrix.";
    fopen_s(&fp, "out.txt", "w");
    if (fp)
    {
        fprintf(fp, "The Matrix A:\n");
        for (i = 0;i < N;i++)
        {
            for (j = 0;j < N;j++)
                fprintf(fp, "%5d", a[i][j]);
            fprintf(fp, "\n");
        }
        fprintf(fp, "The Array X:\n");
        for (i = 0;i < N;i++)
            fprintf(fp, "%5d", x[i]);
        fprintf(fp, "\n");
        if (y != 0)
        {
            fprintf(fp, "The Value Of Y:");
            fprintf(fp, "%3d", y);
        }
        else
            fprintf(fp, "There are no odd elements in the first column of the matrix.");
        fclose(fp);
    }
    else cout << "Opening error. \n";
}

int main()
{
    setlocale(LC_CTYPE, "");
    int a[N][N], x[N], y, v;
    void (*pfunc)(int[N][N]);
    y = 0;
    do
    {
        cout << "Initializing the matrix:\n1-from the keyboard\n2 - from the file\nyour choice:";
        cin >> v;
    } while (v != 1 && v != 2);
    if (v == 1) pfunc = &init;//Assigning an address pointer to one of the functions
    else pfunc = &init_f;
    output(elem_y(y, a, 0), mas_x(a, x, pfunc), a);
    _getch();
}