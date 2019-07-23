void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


void quicksort (int *array, int left, int right)
{
    int base_pos = left;;

    for (int i= left+1;i<=right;i++)
    {
        if (array[i]<array[base_pos])
        {
            swap (array[i], array[base_pos]);
            swap(array[i], array[base_pos+1]);
            base_pos= base_pos+1;
        }
    }
    if (base_pos-left>1)
    {quicksort(array, left, base_pos-1);}
    if (right-base_pos>1)
    {quicksort(array, base_pos+1, right);}

}

