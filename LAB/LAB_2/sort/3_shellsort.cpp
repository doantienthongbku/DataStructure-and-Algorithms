#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

public:
    // TODO: Write your code here
    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total){
        int temp = *(start + segment_idx);

        int j;            
        for (j = segment_idx; j >= cur_segment_total && *(start + j - cur_segment_total) > temp; j -= cur_segment_total)
            *(start + j) = *(start + j - cur_segment_total);
        
        *(start + j) = temp;
    }

    static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
        int n = end - start;
        for (int idx_gap = num_phases - 1; idx_gap >= 0; idx_gap--) {
            int gap = num_segment_list[idx_gap];
            for (int i = gap; i < n; i += 1)
                sortSegment(start, end, i, gap);
            
            cout << gap << " segments: ";
            printArray(start, end);
        }
    }
};


int main() {
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = { 10, 9, 8 , 7 , 6, 5, 4, 3, 2, 1 };

    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);

    return 0;
}