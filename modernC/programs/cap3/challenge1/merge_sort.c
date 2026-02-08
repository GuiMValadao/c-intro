int sort(int argc, char* argv[]);

int main(void)
{
    const int size_array = 9;
    double values_array[] = {5, 2, 3, 7, 1, 9, 10, 23, 12};
    sort(size_array, values_array);
    int checker = 0;
    for (int i = 1; i < size_array; i ++)
    {
        if (values_array[i] < values_array[i-1])
        {
            printf("Not sorted");
            break;
        }
        if (i == size_array - 1)
        {
            printf("Sorted successfully");
        }
        
    }
    return 0;
}


int sort(int argc, double argv[])
{
    double result[sizeof(argv)];
    // base case (number of values = 1)
    if (argc == 1)
    {
        result = argv;
        return result;
    }
    // divide array in left and right
    double left[sizeof(argv)/2];
    double right[sizeof(argv)/2];
    for (int i = 0; i < argc; i ++)
    {
        if (i < argc / 2)
        {
            left[i] = argv[i];
        }
        else
        {
            right[i] = argv[i];
        }
    }
    // call sort recursively on left side and right side
    sort(argc/2, left);
    sort(argc/2, right);
     
    // check if left is smaller, if not, merge to the right of the left side
    int j = 0, k = 0, l = 0;
    while (j < sizeof(left) && k < sizeof(right))
    {
        if (left[j] < right[])
        {
            argv = 
        }
    }
    // else check if the right is smaller. If it is, merge to the right of the right side
    // merge left and right side
}