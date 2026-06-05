#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template <typename T>
void randArray(T arr[], int size, int a = 1, int b = 10) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % (b - a + 1) + a;
}

template <typename T>
void printArray(T arr[], int size, int w_cout = 5) {
    for (int i = 0; i < size; i++) {
        cout.width(w_cout);
        cout << arr[i];
    }
    cout << endl;
}

template <typename T>
int indexMaxElement(T arr[], int size) {
    if (size <= 0) return -1;
    T a = arr[0];
    int indexa = 0;
    for (int i = 1; i < size; i++) {
        if (a < arr[i]) {
            a = arr[i];
            indexa = i;
        }
    }
    return indexa;
}

template <typename T>
int indexMinElement(T arr[], int size) {
    if (size <= 0) return -1;
    T a = arr[0];
    int indexa = 0;
    for (int i = 1; i < size; i++) {
        if (a > arr[i]) {
            a = arr[i];
            indexa = i;
        }
    }
    return indexa;
}

template <typename T>
T sumArray(T arr[], int size) {
    T sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

template <typename T>
int search(T arr[], const int size, T key) {
    for (int i = 0; i < size; i++)
        if (key == arr[i]) return i;
    return -1;
}

template <typename T>
void addItemBack(T*& arr, int& size, T value) {
    T* tmp = new T[size + 1];
    for (int i = 0; i < size; i++)
        tmp[i] = arr[i];
    tmp[size] = value;
    if (arr != nullptr) delete[] arr;
    arr = tmp;
    size++;
}

template <typename T>
void addItemFront(T*& arr, int& size, T value) {
    T* tmp = new T[size + 1];
    for (int i = 0; i < size; i++)
        tmp[i + 1] = arr[i];
    tmp[0] = value;
    if (arr != nullptr) delete[] arr;
    arr = tmp;
    size++;
}

template <typename T>
void addItemPos(T*& arr, int& size, int pos, T value) {
    T* tmp = new T[++size];
    for (int i = 0; i < size; i++) {
        if (i < pos) tmp[i] = arr[i];
        else if (i == pos) tmp[i] = value;
        else tmp[i] = arr[i - 1];
    }
    if (arr != nullptr) delete[] arr;
    arr = tmp;
}

template <typename T>
void removeItemAt(T*& arr, int& size, int index) {
    if (index < 0 || index >= size) return;
    T* tmp = new T[size - 1];
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) tmp[j++] = arr[i];
    }
    delete[] arr;
    arr = tmp;
    size--;
}

// Виправлена сигнатура – компаратор приймає const посилання
template <typename T>
void mySort(T* arr, int size, bool (*cmp)(const T&, const T&)) {
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (cmp(arr[i], arr[j])) {
                T tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
}

template <typename T>
int myCountIf(T* arr, int size, bool (*func)(T)) {
    int cnt = 0;
    for (int i = 0; i < size; i++)
        if (func(arr[i])) cnt++;
    return cnt;
}

template <typename T>
void myRemoveIf(T*& arr, int& size, bool (*func)(T)) {
    int cnt = myCountIf(arr, size, func);
    if (cnt == 0) return;
    T* tmp = new T[size - cnt];
    for (int i = 0, j = 0; i < size; i++) {
        if (!func(arr[i]))
            tmp[j++] = arr[i];
    }
    delete[] arr;
    arr = tmp;
    size -= cnt;
}

template <typename T>
void smoothArray(T arr[], int size) {
    T last = arr[size - 1];
    for (int i = size - 2; i >= 0; i--)
        arr[i] = (arr[i] + arr[i + 1]) / 2;
    arr[size - 1] = last;
}

template <typename T>
double averageMoreM(T arr[], const int size, T m) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] > m) {
            sum += arr[i];
            count++;
        }
    return count ? sum / count : 0;
}

void solveEquation(double a, double b) {
    if (a != 0) cout << "x = " << -b / a << endl;
    else if (b != 0) cout << "No solutions" << endl;
    else cout << "Infinite solutions" << endl;
}

void solveEquation(double a, double b, double c) {
    if (a == 0) {
        solveEquation(b, c);
        return;
    }
    double d = b * b - 4 * a * c;
    if (d > 0) {
        double x1 = (-b + sqrt(d)) / (2 * a);
        double x2 = (-b - sqrt(d)) / (2 * a);
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    }
    else if (d == 0)
        cout << "x = " << -b / (2 * a) << endl;
    else
        cout << "No real roots" << endl;
}