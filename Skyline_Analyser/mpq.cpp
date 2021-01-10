#include "mpq.h"
using namespace std;


template <class Comparable>
const Comparable & mpq<Comparable>::findMax( ) const// the size of the location array is 1 bigger than what is needed and the max value's index is stored in that last slot of the location array
{
	return(heap[location[location.size()-1]].value);
}

template <class Comparable>
void  mpq<Comparable>::insert( const Comparable & v , const int & l)
{

	int hole = ++currentSize;
	node <int>b(v,l);
	for( ; hole > 1 && v< (heap[hole/2]).value; hole /= 2 )
	{
		heap[ hole ] = heap[ hole / 2 ];
		if(location[heap[hole/2].label] == location[location.size()-1] )//if the max is percolated down then change the last slot of the location array accordingly
		{
			 location[location.size()-1] = hole;
		}
		location[heap[hole/2].label] = hole;//update the percolated down node's index in the location array
	}
	heap[hole] = b;

	if((*this).findMax() == 0)//if the heap is empty
	{
		location[location.size()-1] = hole;
	}
	else
	{
		if((*this).findMax() < v)//if the newly inserted element is the greater than the max of the heap update the max
		{
			location[location.size()-1] = hole;
		}
		else
		{
		}
	}

	location[l] = hole;
}



template <class Comparable>
bool mpq<Comparable>::isEmpty() const
{
	return(currentSize==0);
}


template <class comparable>
void mpq<comparable>::percolate_down(int hole)
{
	int child;
	node<int> tmp = heap[hole];
	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && heap[ child + 1 ].value < heap[ child ].value )
		     child++;
		if( heap[ child ].value < tmp.value )
			heap[ hole ] = heap[ child ];
		else
			break;
	 }
	 heap[ hole ] = tmp;

}


template <class Comparable>
Comparable mpq<Comparable>::remove(const int & label )
{
	if( isEmpty( ) )
	{
		return(-1);
	}
	int index = location[label];
	node<int> removed = heap[index];
	heap[index] = heap[currentSize--];
	int max=0;
	if(location[label] == location[location.size()-1])//if the max value is being deleted search for the max starting from the (currentSize/2)'th index of the heap
	{
		int i ;
		if(currentSize == 1)//if only 1 element is left that is the max
		{
			i = 1;
			location[location.size()-1] = i;
		}
		else// if not initiate the i as the currentSize/2
		{
			i = (currentSize/2);
		}
		max = heap[i].value;
		if(i == 0)
		{
			location[location.size()-1] = 0;
		}
		for(; i< currentSize; i++)
		{
			if(heap[i].value >= max)
			{
				location[location.size()-1] = i;
			}
		}
	}
	int child;
	int hole = index;
	node<int> tmp = heap[hole];
	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && heap[ child + 1 ].value < heap[ child ].value )
		     child++;
		if( heap[ child ].value < tmp.value )
			heap[ hole ] = heap[ child ];
		else
			break;
	 }
	 heap[ hole ] = tmp;

	 if(location[tmp.label] == location[location.size()-1] )//if the max value of the heap was percolated up
	 {
		 location[location.size()-1] = hole;
	 }
	 location[tmp.label] = hole;


	return (removed.value);
}









template <class Comparable>
void mpq<Comparable>::destructor()//wasn't used
{
	

}




