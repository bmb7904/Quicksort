/*
 * Three implementations of QuickSort: 
 * 
 *    qsort1: standard recursive version.
 *    qsort2: tail recursion removed.
 *    qsort3: iterative version. 
 *
 * Author: Brett Bernardi
 * Date October 26, 2020
 */

#include <algorithm>
#include <stack>
using namespace std;

/*
 *
 * This function will take an array with lo and high indices. It will choose a pivot
 * element, in this case a[lo], the first element in the array, and partition the array
 * such that all elements less than or equal to the pivot are on the left of the pivot,
 * and all elements greater than are on the right of the pivot. It will also return the
 * new index of the pivot after partitioning. I am aware that I could have used a
 * for-loop, however, this is what I originally came up with immediately after our
 * class on quick-sort and so I have an emotional attachment to this implementation.
 * The infinite loop will always be broken out of it, as long as the preconditions of
 * the specified array and indices are valid. According to my calculations, which may
 * be  incorrect, the asymptotic complexity is still O(n), and I tested every edge case
 * I could think of, so it meets the requirement. When used in a quick sort function,
 * partition() is never called on arrays that contain less than two elements in size.
 * However, this partition will still work correctly on arrays containing only one
 * element.
 *
 * Pre-conditions: a[] is a valid int array with at least one element, and lo <= hi.
 *
 * @param int[] array - An array of at least one element in size
 * @param int lo - the starting index of the Array
 * @param int hi - The ending index of the Array
 *
 * @return int the new index of the pivot after partitioning
 */
int partition(int a[], int lo, int hi)
{
    // taking the pivot to be the first element in the array
    int pivot = a[lo];

    int i = lo; // left hand pointer starts at the index of the first element (the pivot)
    int j = hi; // right hand pointer starts at the index of the last element in the list

    while(true)
    {

        // increment left pointer until it reaches an element that is greater than
        // pivot or it reaches the hi of the
        // array
        while(a[i] <= pivot && i < hi)
        {
            i++;
        }
        // decrement right pointer until reaches an element that is smaller than pivot
        // or it reaches the
        // left most element (first element to right of pivot)
        while(a[j] > pivot && j > lo)
        {
            j--;
        }

        // if the pointer indices cross each other, or they are equal, swap the pivot
        // with a[j] and break out by
        // returning new index of pivot
        if(j<=i)
        {
            std::swap(a[lo], a[j]);
            return j;
        }

        // at this point, the pointers did not meet, and arr[i] > pivot && arr[j] < pivot
        std::swap(a[i], a[j]);
    }

}

/*
 * Standard recursive implementation of QuickSort.
 *
 * int[] a[] - An array of ints to be sorted
 * int lo - the starting index of the Array
 * int hi - The ending index of the Array
 */
void qsort1(int a[], int lo, int hi)
{
    if(lo < hi)
    {
        int k = partition(a, lo, hi);
        qsort1(a, lo, k - 1);
        qsort1(a, k + 1, hi);
    }
}

/*
 * Quicksort implementation with tail-recursion removed.
 *
 * int[] a[] - A valid int array to be sorted
 * int lo - the starting index of the Array
 * int hi - The ending index of the Array
 */
void qsort2(int a[], int lo, int hi)
{
    while(lo < hi)
    {
        int k = partition(a, lo, hi);

        // After partitioning, only recurse with the smaller of the partitions and let
        // the loop deal with the larger
        // of the partitions
        if( (k - lo) < (hi - k) )
        {
            qsort2(a, lo, k - 1);
            lo = k + 1; // update lo for next iteration

        }
        else
        {
            qsort2(a, k + 1, hi);
            hi = k - 1; // update hi for next iteration
        }
    }
}

/*
 * Iterative (Stack-based) quicksort implementation
 *
 * int[] array - A valid int array to be sorted
 * int lo - the starting index of the Array
 * int hi - The ending index of the Array
 */
void qsort3(int a[], int lo, int hi)
{
    // declare and seed the stack(s) with initial supplied hi, lo
    // Stacks are Last In, First Out
    stack<int> s;
    s.push(lo);
    s.push(hi);

    while(!s.empty())
    {
        // extract the hi, lo from the stack
        int tempHi = s.top();
        s.pop();
        int tempLo = s.top();
        s.pop();

        int k = partition(a, tempLo, tempHi);

        // If the resulting sub arrays contain more than 1 element, push the new
        // indices on stack
        if((k-1) > tempLo)
        {
            s.push(tempLo);
            s.push(k - 1);
        }
        if(tempHi > (k+1))
        {
            s.push(k + 1);
            s.push(tempHi);
        }
    }
}

