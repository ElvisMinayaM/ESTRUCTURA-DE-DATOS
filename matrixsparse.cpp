#include <iostream>
#include <cstring>
#include <map>

using namespace std;

template <class T>
class sparse_matrix
{
	struct node
	{
		T value;
		size_t pos[2];		// pos[0] = i-row, pos[1] = i-col
		node * p_next[2];	// p_next[0]: next row node
							// p_next[1]: next col node
		
		node(size_t i, size_t j, node * nr, node * nc)
		{
			pos[0] = i;
			pos[1] = j;
			p_next[0] = nr;
			p_next[1] = nc;
		}
	};
	
	private:
		map<size_t, node *> p_head[2];
		size_t n_rows, n_cols;
		
	public:
		sparse_matrix(size_t nr = 0, size_t nc = 0): n_rows(nr), n_cols(nc)
		{
			if(!n_cols) n_cols = n_rows;
			
		}
		~sparse_matrix(){
		node **n;
        for (size_t i=0; i<n_rows; ++i) {
            for (size_t j=0; j<n_cols; ++j) {
                if(find(n,i,j,true))
      				delete *n
            }
        }
		}






		bool find(node **& n, size_t i, size_t j, bool c)
		{
			n = &p_head[c][i];
			while(*n && (*n)->pos[!c] < j)
				n = &(*n)->p_next[c];
			
			return (*n) && (*n)->pos[!c] == j;
		}
		
		T & operator () (size_t i, size_t j)
		{
			node ** nr;
			if(!find(nr, i, j, 0))
			{
				node ** nc;
				find(nc,i,j, 1);
				*nr = *nc = new node(i, j, *nr, *nc);
			}
			
			return (*nr)->value;
		}
		

    void print()
    {
        node **n;
        for (size_t i=0; i<n_rows; ++i) {
            for (size_t j=0; j<n_cols; ++j) {
                int val = !find(n, i, j, true) ? !find(n, i,j, false) ? 0 : (*n)->value : (*n)->value ;
                cout << val << ", ";
            }
            cout<< "\n";
        }
    }

    void transpuesta()
    {
        node **n;
        for (size_t i=0; i<n_rows; ++i) {
            for (size_t j=0; j<n_cols; ++j) {
                int val = !find(n, j, i, true) ? !find(n, j,i, false) ? 0 : (*n)->value : (*n)->value ;
                cout << val << ", ";
            }
            cout<< "\n";
        }
    }
};



int main()
{
	sparse_matrix<int> sq(3);
	
	sq(0, 0) = 1;
	sq(0, 2) = 2;
	sq(1, 1) = 3;

	sq.print();
	cout<<"------------------"<<endl;
	sq.transpuesta();



	return 0;
}
/*

print 
destructor
remove
css

map solo destruye
destruir nodos
liberar memoria en bloque
eliminar nodos de adentro

*/
