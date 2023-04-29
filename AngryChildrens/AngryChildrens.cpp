// AngryChildrens.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include<algorithm>
#include<functional>
#include<fstream>
#include<vector>
#include <set>
#include <queue>
#include<map>
#include <chrono>
#include <thread>

using namespace std;


string ltrim(const string&);
string rtrim(const string&);
void longer(int[], int, int);
void merger(int[], int, int, int);
long long angryChildren(int k, vector<int> packets);
long angrier(int x, int num, int k, int n, int* array);
int* sortPackets(vector<int>);

long angrier(int x, int num, int k, int n, int* array)
{
    if (num == k || x == n)
    {
        if (num == k)
        {
            return 0;
        }
        else {
            return LONG_MAX;
        }
    }

    long A = (2 * num - k + 1) * array[x];
    long C = angrier(x + 1, num + 1, k, n, array);
    if (C != LONG_MAX)
    {
        A += C;
    }
    else {
        A = LONG_MAX;
    }
    long B = angrier(x + 1, num, k, n, array);
    if (A == LONG_MAX && B == LONG_MAX)
    {
        return LONG_MAX;
    }
    else {
        //cout << A << " " << B << " K " << num << endl;
        return A < B ? A : B;
    }

}

long long angryChildren(int k, vector<int> packets) {

    int* answer = sortPackets(packets);
    //cout << "Sorting comepleted " << endl;
    long long** combinations = new long long* [packets.size() - k + 1];
    for (int i = 0; i < packets.size() - k + 1; ++i)
    {
        //cout << " before memory allocation in index: " << i << endl;
        combinations[i] = new long long[k + 1];
        for (int j = 0; j < k + 1; j++)
        {
            combinations[i][j] = 0;
        }
    }

    for (int i = 0; i < packets.size() - k + 1; i++)
    {
        combinations[i][k] = 0;
    }

    for (int i = 0; i < k; i++)
    {
        combinations[packets.size() - k][i] = LLONG_MAX;
    }



    for (long long i = packets.size() + k - 1; i >= 0; i--)
    {
        for (long long j = k - 1; j >= 0; j--)
        {
            long long A = (2 * j - k + 1) * answer[i];
            long long C = combinations[i + 1][j + 1];
            long long B = combinations[i + 1][j];

            if (C != LLONG_MAX)
            {
                A += C;
            }
            else {
                A = LLONG_MAX;
            }

            if (A == LLONG_MAX && B == LLONG_MAX)
            {
                combinations[i][j] = LLONG_MAX;
            }
            else {

                combinations[i][j] = A < B ? A : B;
            }
        }
    }
    long long ans = combinations[0][0];

    for (int i = 0; i <= packets.size(); ++i)
    {
        delete[] combinations[i];
    }

    delete[] combinations;
    return ans;
}

int* sortPackets(vector<int>packets)
{

    int* array = new int[packets.size()];
    int i = 0;
    for (auto x = packets.begin(); x != packets.end(); ++x)
    {
        array[i] = *x;
        ++i;
    }

    longer(array, 0, packets.size() - 1);
    return array;
}

// 10 -> 0-4, 5-9 -> 0-4 -> 0-1, 2- 4 -> 0,1|| 0-1, 2
void longer(int arr[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = start + ((end - start) / 2);
    longer(arr, start, mid);
    longer(arr, mid + 1, end);
    merger(arr, start, mid, end);
}

void merger(int arr[], int start, int mid, int end)
{
    int* leftarr_copy = new int[(mid - start) + 1];
    int* rightarr_copy = new int[end - mid];
    int right = 0;
    int left = 0;

    for (int x = start; x <= mid; x++) {
        leftarr_copy[left] = arr[x];
        //cout << leftarr_copy[left] << " ";
        left++;
    }
    //cout << "left : " << left << endl;

    for (int x = mid + 1; x <= end; x++) {
        rightarr_copy[right] = arr[x];
        //cout << rightarr_copy[right] << " ";
        right++;
    }
    //cout << "right : " << right << endl;

    //cout << endl;

    int right_ptr = 0;
    int left_ptr = 0;
    int x = start;
    while (right_ptr < right && left_ptr < left) {
        if (rightarr_copy[right_ptr] < leftarr_copy[left_ptr]) {
            arr[x] = rightarr_copy[right_ptr];
            right_ptr++;
        }
        else {
            arr[x] = leftarr_copy[left_ptr];
            left_ptr++;
        }
        x++;
    }
    if (left_ptr == left) {
        while (right_ptr < right) {
            arr[x] = rightarr_copy[right_ptr];
            x++;
            right_ptr++;
        }
    }
    else {
        while (left_ptr < left) {
            arr[x] = leftarr_copy[left_ptr];
            x++;
            left_ptr++;
        }
    }

    delete[] leftarr_copy;
    delete[] rightarr_copy;
    return;
}

int main()
{
    string n_temp;

    fstream textfile("Tester.txt", ios::in | ios::out);
    if (textfile.is_open())
    {
        getline(textfile, n_temp);
        int n = stoi(ltrim(rtrim(n_temp)));
        string k_temp;
        getline(textfile, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));
        vector<int> packets(n);
        //cout << "etst" << endl;
        for (int i = 0; i < n; i++) {
            string packets_item_temp;
            getline(textfile, packets_item_temp);

            int packets_item = stoi(ltrim(rtrim(packets_item_temp)));

            packets[i] = packets_item;
        }
        cout << LONG_MAX << endl;
        long long result = angryChildren(k, packets);
        cout << result << endl;
    }


    textfile.close();

    return 0;

}

string ltrim(const string& str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string& str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
