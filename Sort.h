// Code from textbook
// Modified by: Tal Bachar


#ifndef SORT_H
#define SORT_H

/**
 * Several sorting routines.
 * Arrays are rearranged with smallest item first.
 */
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
using namespace std;

/**
 * Simple insertion sort.
 */
 template <typename Comparable, typename Comparator>
 void insertionSort(vector<Comparable> & a,Comparable left, Comparable right, Comparator less_than)
 {
 	for(int i=left;i<=right;i++)
 	{
 		Comparable temp =a[i];
 		int j=i;
 		while(j>0&&less_than(temp,a[j-1]))
 		{
 			a[j]=a[j-1];
 			j--;
 		}
 		a[j]=temp;
 	}
 }


/**
 * Internal insertion sort routine for subarrays
 * that is used by quicksort.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable, typename Comparator>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    for( int p = left + 1; p <= right; ++p )
    {
        Comparable tmp = std::move( a[ p ] );
        int j;

        for( j = p; j > left && tmp < a[ j - 1 ]; --j )
            a[ j ] = std::move( a[ j - 1 ] );
        a[ j ] = std::move( tmp );
    }
}



/**
 * Shellsort, using Shell's (poor) increments.
 */
template <typename Comparable>
void shellsort( vector<Comparable> & a )
{
    for( int gap = a.size( ) / 2; gap > 0; gap /= 2 )
        for( int i = gap; i < a.size( ); ++i )
        {
            Comparable tmp = std::move( a[ i ] );
            int j = i;

            for( ; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = std::move( a[ j - gap ] );
            a[ j ] = std::move( tmp );
        }
}


/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i )
{
    return 2 * i + 1;
}


/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable> & a, int i, int n, Comparator less_than)
{
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child ) {
        child = leftChild( i );
      if (child != n-1 && less_than(a[child],a[child+1]))
            ++child;
      if(less_than(tmp,a[child]))
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}//end percDown


/**
 * Standard heapsort.
 */
 template <typename Comparable, typename Comparator>
 void HeapSort(vector<Comparable> &a, Comparator less_than) {

   for( int i = a.size( ) / 2 - 1; i >= 0; --i )  /* buildHeap */
        percDown(a, i, a.size(), less_than );
   for( int j = a.size( ) - 1; j > 0; --j ) {
        std::swap( a[ 0 ], a[ j ] );               /* deleteMax */
        percDown( a, 0, j, less_than );
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is an array of Comparable items.
 * tmpArray is an array to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
 template <typename Comparable, typename Comparator>
 void merge(vector<Comparable> &a,vector<Comparable> &b,Comparable leftpos,Comparable rightpos,Comparable rightend, Comparator less_than)
 {
 	Comparable leftend=rightpos-1;
 	Comparable temp_pos=leftpos;
 	Comparable num_elements=rightend-leftpos+1;

 	//main loop
 	while(leftpos<=leftend&&rightpos<=rightend)
 	{
 		if(less_than(a[leftpos],a[rightpos]))
 		{
 			b[temp_pos++]=a[leftpos++];
 		}
 		else
 		{
 			b[temp_pos++]=a[rightpos++];
 		}
 	}
 	while(leftpos<=leftend)//copy rest of first half
 	{
 		b[temp_pos++]=a[leftpos++];
 	}
 	while(rightpos<=rightend)//copy rest of right half
 	{
 		b[temp_pos++]=a[rightpos++];
 	}
 	//copy tmparray back
 	for(int i=0;i<num_elements;++i,--rightend)
 	{
 		a[rightend]=b[rightend];
 	}
 }


/**
* Internal method that makes recursive calls.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable> &a,vector<Comparable> &b,Comparable left,Comparable right, Comparator less_than)
{
	if(left<right)
	{
		Comparable center=(left+right)/2;
		mergeSort(a,b,left,center,less_than);
		mergeSort(a,b,center+1,right,less_than);
		merge(a,b,left,center+1,right,less_than);
	}
}
template <typename Comparable, typename Comparator>
void MergeSort(vector<Comparable> &a, Comparator less_than)
{
	/**
 * mergeSort algorithm (driver).
 */
	vector<Comparable>b(a.size());
	Comparable c=a.size()-1;
	mergeSort(a,b,0,c,less_than);
}

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable & median3( vector<Comparable> & a, int left, int right,Comparator less_than)
{
   int center =(left+right)/2;

  if(less_than(a[center],a[left]))
     swap(a[left],a[center]);
  if(less_than(a[right],a[left]))
     swap(a[left],a[right]);
  if(less_than(a[right],a[center]))
     swap(a[center],a[right]);
  // Place pivot at position right - 1
  swap(a[center],a[right-1]);
  return a[right-1];
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
 template <typename Comparable, typename Comparator>
 void quickSort(vector<Comparable> &a,Comparable left, Comparable right ,Comparator less_than)
 {
 	if(left+10 <= right)
 	{
 		//a[left]become the smallest,a[right]become the largest.
 		const Comparable &pivot= median3(a,left,right,less_than);
 		//cout<<a[right]<<endl;

 		//Begin partitioning
 		int i=left;
 		int j=right-1;

 		for(;;)
 		{
 			//while(a[++i]<pivot){}
 			while(less_than(a[++i],pivot)){}
 			while(less_than(pivot,a[--j])){}
 			//while(pivot<a[--j]){}
 			if(i<j)
 			{
 				swap(a[i],a[j]);
 			}
 			else
 				break;
 		}
 		swap(a[i],a[right-1]);//restore pivot
 		quickSort(a,left,i-1,less_than);//sort small elements
 		quickSort(a,i+1,right,less_than);//sort large elements
 	}
 	else
 	{
 		//Do an insertion sort on the subarray
 		//cout<<"i"<<endl;
 		//cout<<left<<"  "<<right<<endl;
 		insertionSort(a,left,right,less_than);

 	}
 }
/**
 * Quicksort algorithm (driver).
 */
 template <typename Comparable, typename Comparator>
 void QuickSort(vector<Comparable> &a, Comparator less_than)
 {
 	Comparable left=0;
 	Comparable right =a.size()-1;
 	quickSort(a,left,right,less_than);
 	//sort(a.begin(),a.end(),less_than);
 }

 template <typename Comparable>
 const Comparable & getMiddle(vector<Comparable> & a, Comparable left, Comparable right)
 {
 	int middle=(left+right)/2;
 	swap(a[middle],a[right-1]);
 	return a[right-1];
 }

 //Middle Pivot Wrapper
 template <typename Comparable, typename Comparator>
 void QuickSort2(vector<Comparable> &a, Comparator less_than) {
 	Comparable left=0;
   Comparable right =a.size()-1;
   quickSort_middle(a,left,right,less_than);
   //sort(a.begin(),a.end(),less_than)
   }
   template <typename Comparable, typename Comparator>
   void quickSort_middle(vector<Comparable> &a,Comparable left, Comparable right ,Comparator less_than)
   {
	   if(left + 10 <=right){
			const Comparable &pivot=getMiddle(a,left,right);

   		int i=left-1;
   		int j=right-1;

   		for(;;) {
   			while(less_than(a[++i],pivot)){}
   			while(less_than(pivot,a[--j])){}
   			if(i<j) {
   				swap(a[i],a[j]);
   			}
   			else {
   				break;
            }
   		}
   		swap(a[i],a[right-1]);
   		quickSort_middle(a,left,i-1,less_than);
   		quickSort_middle(a,i+1,right,less_than);
	  }
	   else {
		    insertionSort(a,left,right,less_than);
	  }
}//end quickSort_middle

 //First Pivot Wrapper
 template <typename Comparable, typename Comparator>
 void QuickSort3(vector<Comparable> &a, Comparator less_than) {


}


/**
 * Internal selection method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int left, int right, int k )
{
    if( left + 10 <= right )
    {
        const Comparable & pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                std::swap( a[ i ], a[ j ] );
            else
                break;
        }

        std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

            // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, left, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, right, k );
    }
    else  // Do an insertion sort on the subarray
        insertionSort( a, left, right );
}

/**
 * Quick selection algorithm.
 * Places the kth smallest item in a[k-1].
 * a is an array of Comparable items.
 * k is the desired rank (1 is minimum) in the entire array.
 */
template <typename Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}


template <typename Comparable>
void SORT( vector<Comparable> & items )
{
    if( items.size( ) > 1 )
    {
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;

        auto chosenItem = items[ items.size( ) / 2 ];

        for( auto & i : items )
        {
            if( i < chosenItem )
                smaller.push_back( std::move( i ) );
            else if( chosenItem < i )
                larger.push_back( std::move( i ) );
            else
                same.push_back( std::move( i ) );
        }

        SORT( smaller );     // Recursive call!
        SORT( larger );      // Recursive call!

        std::move( begin( smaller ), end( smaller ), begin( items ) );
        std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) );
        std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );


    }
}



#endif
