#include <iostream>
#include <map>

template<class T>
class SparseMatrix
{
    struct Node
    {
        T value;
        std::size_t pos[2];	// 0: i=row, 1: j=col
        Node *p_next[3]; 	// 2: prev node. 0: next row node. 1: next col node
        Node(std::size_t i, std::size_t j, Node *nr, Node *nc, Node *prev)
        {
            pos[0] = i; pos[1] = j;
            p_next[0] = nr; p_next[1] = nc; p_next[2] = prev;
            }
    };
    
    std::map<std::size_t, Node*> p_head[2];
    std::size_t n_rows, n_cols;
    T __helper;
    
public:
    SparseMatrix(std::size_t nr=0, std::size_t nc=0)
        : n_rows(nr), n_cols(nc)
    {
        if (!n_cols) n_cols = n_rows;
    }
    
    bool find(Node **&n, std::size_t i, std::size_t j, bool is_col)
    {
        n = &p_head[is_col][i];
        
        while (*n && (*n)->pos[!is_col] < j)
            n = &(*n)->p_next[is_col];
    
        return (*n) && (*n)->pos[!is_col] == j;
    }
    
    // INSERT
    T& operator()(std::size_t i, std::size_t j)
    {
        if (i >= n_rows || j >= n_cols) return __helper;
    
        Node **nr;
        if (!find(nr, i, j, false))
        {
            Node **nc;
            find(nc, j, i, true);
            *nr = *nc = new Node(i, j, *nr, *nc,NULL);
        }
        return (*nr)->value;
    }
    

    
    void print()
    {
        Node **n;
        for (std::size_t i=0; i<n_rows; ++i) {
            for (std::size_t j=0; j<n_cols; ++j) {
                int val = !find(n, i, j, true) ? !find(n, i,j, false) ? 0 : (*n)->value : (*n)->value ;
                std::cout << val << ", ";
            }
            std::cout << "\n";
        }
    }
};

int main()
{
    SparseMatrix<int> sm(3,3);
    sm(0,0) = 1; 
    sm(0,1) = 2; 
    sm(0,2) = 3;
    sm(1,0) = 4; 
    sm(1,1) = 5; 
    
    sm.print();

    return 0;
}

