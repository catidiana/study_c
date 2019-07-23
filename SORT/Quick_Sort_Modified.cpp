
void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Pivotlist (int *array, int left, int right)
{
    int PivotValue = array[left];
    int lower = left;
    int upper = right + 1;
    do {
        do {
            upper = upper - 1;
    } while (array[upper] > PivotValue);
        do {
            lower = lower + 1;
        } while (array[lower] < PivotValue);
        swap(array[upper], array[lower]);
    } while (lower < upper);
    swap (array[upper], array[lower]);
    swap (array[left], array[upper]);
    return upper;
}

void quicksort (int *array, int left, int right) {
    if (left < right) {
        int pivot = Pivotlist(array, left, right);
        quicksort(array, left, pivot-1);
        quicksort(array, pivot+1, right);
    }
}