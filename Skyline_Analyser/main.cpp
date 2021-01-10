#include <fstream>
#include <sstream>
#include "mpq.h"
#include <iostream>
#include "mpq.cpp"
#include "heap_sort.h"
using namespace std;


int main()
{
	//initiating all variables and putting all x's into an array and all y's into another

	int nofcities, x_l,y,x_r;
	vector<x_coord> array_xs;
	int b_num=  0;
	ifstream infile("input1.txt");
	string line;
	x_l=0;
	x_r=0;
	getline(infile,line);
	istringstream iss(line);
	iss >> nofcities;
	mpq<int> tree(nofcities);
	vector<int> array_ys(nofcities+1);
	x_coord x_init(0,0,LEFT);
	array_xs.push_back(x_init);
	int y_init = 0;
	array_ys[0]= y_init;
	while(getline(infile, line))
	{
		b_num +=1;
		istringstream iss(line); 
		iss >> x_l>> y >> x_r;
		x_coord x_left(x_l,b_num,LEFT);
		x_coord x_right(x_r,b_num,RIGHT);
		array_xs.push_back(x_left);
		array_xs.push_back(x_right);
		array_ys[b_num] = y;
	}


	//heap sorting the array of x's

 	heap_sort heap_sort_a;
	heap_sort_a.build_heap(array_xs);
	x_coord min(0,0,LEFT);
	vector<x_coord> sorted;
	sorted.push_back(min);
	for(int i = 1; i<= 2*nofcities; i++)
	{
		heap_sort_a.delete_min(min);
		sorted.push_back(min);
	}



	//skyline program

	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int prev_max = 0;
	int prev_y = -1;
	int i = 1;
	for(; i<= 2*nofcities; i++)//sweeping the x array from left to right
	{
		counter1 +=1;
		int building_number = sorted[i].building;
		y= array_ys[building_number];// the y with the building label of the x
		int x = sorted[i].x;//take the i'th x from the sorted x array
		if(x != 0 && counter1 ==1)//if zero is not occupied
		{
			cout << 0 << " " << 0 << endl;
		}


		int l;
		if(sorted[i].s == LEFT)//if the x is a left x of a building
		{
			prev_max = tree.findMax();//to see if the max of the heap changed
			l = building_number;//label
			tree.insert(y,l);//insert the y of the x with its building_number as the label

			//if (the max of the heap changed after the addition&& (the x processed before is not the same as the current x || (if it is the same && previously removed y was not the max)
			if((x != sorted[i+1].x) && prev_max != tree.findMax() && ((x != sorted[i-1].x) ||( (x == sorted[i-1].x) &&(prev_y != tree.findMax() )) ) )
			{
				counter2 +=1;
				cout << x << " " << tree.findMax()<< endl;
			}

		}

		if(sorted[i].s == RIGHT)
		{
			prev_max = tree.findMax();
			prev_y =tree.remove(building_number);
			if(counter2 == 0)//if all the buildings were starting from the same x 
			{
				cout << sorted[i-1].x << " " << tree.findMax()<< endl;
				counter2+=1;
			}
			if(prev_max != tree.findMax())// if the max of the heap changed after the removal
			{
				if(i< sorted.size()-1 )//if the x is not the last x
				{
					if( x != sorted[i+1].x )//if the x is not the same as the following x
					{
						counter3 += 1;
						cout << x << " " << tree.findMax()<< endl;
					}
				}
				else//if x is the priorly processed x
				{
					counter3+=1;
					cout << x << " " << tree.findMax()<< endl;
				}

			}
		}
	}

	if(counter3 == 0)
	{
		cout << sorted[i-1].x << " " << tree.findMax()<< endl;
	}


 	return 0;
}
