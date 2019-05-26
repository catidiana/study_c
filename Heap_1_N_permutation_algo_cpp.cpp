#include <iostream>
//define array lenth
# define N 4
using namespace std;

void swap (int *array, int i, int j)
{
    int s=array[i];
    array[i]=array[j];
    array[j]=s;
}

int main()
{
    int A[N]; //array to permutate
    int c[N]; //array to encode stack
    //I put numbers 1.... N to this array but you can put any numbers
    for (int i=0;i<N;i++) {
        A[i]=i+1;
        c[i]=0;
        cout << A[i] << "\t";
    }
    cout << endl;
    int i=0;
    while(i<N)
    {
        if(c[i]<i)
        {
            if(i%2==0)
            {swap(A, 0, i);}
            else {
                swap(A, c[i], i);
            }
            for (int i=0;i<N;i++) {
                cout << A[i] << "\t";
            }
            cout << endl;
            c[i]+=1;
            i=0;
        }
        else {
            c[i]=0;
            i+=1;
        }
    }

    return 0;
}
