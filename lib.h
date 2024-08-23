#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
#define ll long long

// Utility function to check if the time limit has been exceeded
bool checkTimeLimit(std::chrono::steady_clock::time_point start, double t) {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    return elapsed_seconds.count() >= t;
}

void MysterySort1(ll *a, ll n, double t) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    bool swapped;
    for (ll i = 0; i < n - 1; i++) {
        swapped = false;
        for (ll j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
            if (checkTimeLimit(start, t)) return;
        }
        if (!swapped)
            break;
    }
}

ll partition(ll *a, ll low, ll high) {
    ll pivot = a[high];
    ll i = low - 1;
    for (ll j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(ll *a, ll low, ll high, std::chrono::steady_clock::time_point start, double t) {
    if (low < high) {
        if (checkTimeLimit(start, t)) return;
        ll pi = partition(a, low, high);
        quickSort(a, low, pi - 1, start, t);
        quickSort(a, pi + 1, high, start, t);
    }
}

void MysterySort2(ll *a, ll n, double t) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    quickSort(a, 0, n - 1, start, t);
}

void merge(ll *a, ll left, ll mid, ll right, std::chrono::steady_clock::time_point start, double t) {
    ll n1 = mid - left + 1;
    ll n2 = right - mid;

    ll *L = new ll[n1];
    ll *R = new ll[n2];

    for (ll i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (ll j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    ll i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (checkTimeLimit(start, t)) {
            delete[] L;
            delete[] R;
            return;
        }
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        if (checkTimeLimit(start, t)) {
            delete[] L;
            delete[] R;
            return;
        }
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        if (checkTimeLimit(start, t)) {
            delete[] L;
            delete[] R;
            return;
        }
        a[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(ll *a, ll left, ll right, std::chrono::steady_clock::time_point start, double t) {
    if (left < right) {
        if (checkTimeLimit(start, t)) return;
        ll mid = left + (right - left) / 2;
        mergeSort(a, left, mid, start, t);
        mergeSort(a, mid + 1, right, start, t);
        merge(a, left, mid, right, start, t);
    }
}

void MysterySort3(ll *a, ll n, double t) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    mergeSort(a, 0, n - 1, start, t);
}

void MysterySort4(ll *a, ll n, double t){
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for (ll i = 0; i < n - 1; i++) {
        ll minIndex = i;
        for (ll j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
            if (checkTimeLimit(start, t)) return;
        }
        if (minIndex != i) {
            swap(a[i], a[minIndex]);
        }
    }
}

void MysterySort5(ll *a, ll n, double t) {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for (ll i = 1; i < n; i++) {
        ll key = a[i];
        ll j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            if (checkTimeLimit(start, t)) return;
        }
        a[j + 1] = key;
    }
}

#endif

