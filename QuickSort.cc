#include <iostream>

using namespace std;

const int MAX = 6;

template <typename T> void Swap(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

template <typename T> void QuickSort(T *const array, const int &start, const int &end)
{
    if(start == end) return;

    int pivot = array[start];
    int i = start, k = end;

    while(true)
    {
        while(i <= end && array[i] < pivot) ++i;
        while(k >= start && array[k] > pivot) --k;

        if (i < k)
        {
            std::cout << "i:" << i << " k:" << k << endl;

            Swap(array[i], array[k]);
            ++i; --k;
        }
        else
            break;
    }

    if(i == k) ++i;

    QuickSort(array, start, i - 1);
    QuickSort(array, i, end);
}

int main()
{
    int array[MAX] = {7, 4, 2, 8, 0, 5,};

    int start = 0, end = MAX - 1;

    QuickSort(array, start, end);

    for(auto i : array) cout << i << " ";

    return 0;
}