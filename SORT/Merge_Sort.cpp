
void MergeLists(int *a, int start1, int end1, int start2, int end2) {
    int finalStart = start1;
    int finalEnd = end2;
    int *result = new int[finalEnd - finalStart + 1];
    int c = 1;
    while (start1 <= end1 && start2 <=end2) {
        if (a[start1] < a[start2]) {
            result[c] = a[start1];
            start1++;
        } else {
            result[c] = a[start2];
            start2++;
        }
        c++;
    }
    if (start1 <= end1) {
        for (int i = start1; i <= end1; i++) {
            result[c] = a[i];
            c++;
        }
    } else {
        for (int i = start2;i<=end2;i++) {
            result[c] = a[i];
            c++;
        }
}
    c = 1;
    for (int i = finalStart;i<=finalEnd;i++) {
        a[i] = result[c];
        c++;
    }
}

void MergeSort (int *a, int first, int last) {
    if (first < last) {
        int middle = (first+last)/2;
        MergeSort(a, first, middle);
        MergeSort(a, middle+1, last);
        MergeLists(a, first, middle, middle+1, last);
    }
}
