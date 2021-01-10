#ifndef heap_sort_h
#define heap_sort_h
#include <vector>
using namespace std;

enum side {
  LEFT = 1,
  RIGHT,
};


struct x_coord
{
	int x;
	int building;
	side s;

	x_coord(const int & x_i, const int & b, const side & s_i): x(x_i), building(b),s(s_i){}

};


class heap_sort
{
public:

	heap_sort()
	{
		currentSize = 0;
		x_coord x_init(0,0,LEFT);
		arr.push_back(x_init);
	}

	bool isEmpty() const
	{
		return(currentSize ==0);
	}



	void delete_min(x_coord & min)
	{
		if( isEmpty( ) )
		{
		}
		else
		{
			min = arr[1];
			arr[ 1 ] = arr[currentSize--];
			percolate_down(1);
		}
	}
	void build_heap(const vector<x_coord> & input)
	{
		currentSize = input.size()-1;
		for(int i = 1; i <= currentSize; i++)
		{
			arr.push_back(input[i]);
		}
		for(int i = currentSize / 2; i > 0; i-=1 )
		{
			percolate_down( i );
		}
	}

private:
	int currentSize;
	vector<x_coord> arr;

	void percolate_down(int hole)
	{
		int child;
		x_coord tmp = arr[hole];
		for( ; hole * 2 <= currentSize; hole = child )
		{
			child = hole * 2;
			if( child != currentSize && arr[ child + 1 ].x < arr[ child ].x )
			     child++;
			if( arr[ child ].x < tmp.x )
				arr[ hole ] = arr[ child ];
			else
				break;
		}
		arr[ hole ] = tmp;

	}
};



#endif