#ifndef mpq_h
#define mpq_h
#include <vector>
using namespace std;

template <class Comparable>
struct node{
	Comparable value;
	int label;

	node(const Comparable & v, const int & l): value(v),label(l){}
};

template <class Comparable>
class mpq
{
	public:
		mpq(const int & buildings):currentSize(0){
			for(int i = 1 ; i <= buildings+1; i++)
			{
				node<int> n(0,0);
				heap.push_back(n);
			}
			vector<int>l(buildings+2);
			location = l;
		}

        bool isEmpty( ) const;
        const Comparable & findMax( ) const;
        void insert( const Comparable & v , const int & label);
        Comparable remove(const int & label );
		void destructor();//wasn't used

      private:
         int currentSize;
		 vector<node<Comparable>>heap;
		 vector<int> location;       

		 void percolate_down(int hole);

};

#endif