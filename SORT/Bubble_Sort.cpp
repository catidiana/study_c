
void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubble_sort (int *a, int size) {
    int num_of_pairs = size;
    bool swapped_elements = true;
    while (swapped_elements) {
        -- num_of_pairs;
        swapped_elements = false;
        for (int i = 0;i<=num_of_pairs;i++) {
            if(a[i] > a[i+1]) {
                swap(a[i], a[i+1]);
                swapped_elements = true;
            }
        }
    }
}

