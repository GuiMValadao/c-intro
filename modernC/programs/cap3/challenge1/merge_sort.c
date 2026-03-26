#include <stdio.h>
#include <stdlib.h>

double *sort(int argc, double argv[]);

int main(void)
{
    const int size_array = 9;
    double values_array[] = {5, 2, 3, 7, 1, 9, 10, 23, 12};
    double* sorted_array = sort(size_array, values_array);
    int checker = 0;
    for (int i = 1; i < size_array; i ++)
    {
        printf("%f\t", sorted_array[i-1]);
        if (sorted_array[i] < sorted_array[i-1])
        {
            printf("Not sorted");
           //break;
        }
        if (i == size_array - 1)
        {
            printf("Sorted successfully");
        }
    }
    free(sorted_array);
    return 0;
}


double *sort(int argc, double argv[])
{   
    printf("In sort\n");
    double *result = (double*)malloc((argc) * sizeof(double));
    if (result == NULL) {
        printf("Error when allocating result");
        return NULL;
    }
    
    // base case (number of values = 1)
    if (argc == 1) {
        printf("Returning\n");
        return argv;
    }

    // divide array in left and right
    double *left = (double*)malloc((argc / 2) * sizeof(double));
    if (left == NULL) {
        printf("Error when allocating memory\n");
        return NULL;
    }
    double *right = (double*)malloc((argc / 2) * sizeof(double));
    if (right == NULL) {
        printf("Error when allocating memory\n");
        return NULL;
    }
    printf("Dividing the array\n");
    for (int i = 0; i < argc; i ++)
    {
        if (i < argc / 2)
            left[i] = argv[i];
        else
            right[i - argc / 2] = argv[i];
    }

    // call sort recursively on left side and right side
    double *sorted_left = sort(argc/2, left);
    double *sorted_right = sort(argc/2, right);
     
    // check if left is smaller, if not, merge to the right of the left side
    int j = 0, k = 0, l = 0;

    int size_left = sizeof(sorted_left);
    int size_right = sizeof(sorted_right);

    while (j <= size_left && k <= size_right) {
        if (j == size_left && k == size_right)
            break;

        if (j == size_left && k < size_right) {
            result[l] = sorted_right[k];
            k ++;
        } else if (k == size_right && j < size_left) {
            result[l] = sorted_left[j];
            j ++;
        }

        if (sorted_left[j] < sorted_right[k]) {    
            result[l] = left[j];
            j ++;
        }
        else {
            result[l] = right[k];
            k ++;
        }
        l ++;
    }

    free(left);
    free(right);
    printf("Returning\n");
    return result;
}