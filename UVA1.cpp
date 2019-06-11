#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
 
using namespace std;

typedef vector<int> VI;
vector<int> Vector;


class SegmentTree{    
public:
   VI A, tree;
   SegmentTree(VI & _A) : A(_A) {
      int N = A.size();
      tree = VI(4 * N, 1);
      build(1, 0, N - 1);
   }
   


   //construir
   void build(int node, int low, int high) {
      if(low == high) {
         tree[node] = A[low];
         return;
   }
      int mid = (low+high)/2;
       
      
// calcular los valores en los subárboles izquierdo y derecho
      build(2*node, low, mid);  //hijo izquiero
      build(2*node + 1, mid + 1, high); // hijo derecho 
       
// cada nodo padre es igual al producto de sus hijos
      tree[node] = tree[2*node] * tree[2*node+1];
   }


   void update(int ind, int val) {
      Update1(1, ind, val, 0, A.size() - 1);
   }
   
   void Update1(int node, int ind, int val, int low, int high) {
      
      // si el índice actual no está contenido en el intervalo,
      
      // omite este intervalo
      if(ind < low || ind > high)
         return;
        

      if(low == high) {
         tree[node] = val;
         return;
      }
       
      int mid = (low + high) / 2;

      // actualizar los valores en los subárboles izquierdo y derecho

      Update1(2*node, ind, val, low, mid);
      Update1(2*node + 1, ind, val, mid + 1, high);
       
      tree[node] = tree[2*node] * tree[2*node+1];
   }
    


   int query(int i, int j) {
      return _query(1, 0, A.size() - 1, i, j);
   }

   int _query(int node, int low, int high, int i, int j) {
       
// si el intervalo actual no se cruza con la consulta
// intervalo de retorno 1, este valor no va a afectar
// el signo del producto final
      if(high < i || low > j) 
         return 1;
       

// si el intervalo actual está incluido en la consulta
// árbol de retorno de intervalo [nodo]
      if(low >= i && high <= j) 
         return tree[node];
       
      int mid = (low + high) / 2;
       

// producto de los intervalos incluidos en la consulta.
      return _query(2*node, low, mid, i, j) * 
                _query(2*node+1, mid + 1, high, i, j);
   }
};
 
 
int main() {
   //CAMBIO C
   //4tamaño 6consultas
   //vector
   //c= consulta 1 por 10, cambio en la posicion 1 por 10
   //p= producto 1x4 posicion 1 por posicion 4    int x[q]=;
   int n, q,low,high,uva,i,v,total;
   char c;
   int x;
   char cmd;
      cin>>n;
      cin>>q;
      for (int i=0;i<n;i++){
         cin>>x;
         if(x > 0) x = 1;
         if(x < 0) x = -1;
         Vector.push_back(x);
      }

      SegmentTree ST(Vector);
      for(int j=0;j<q;j++){
         cin>>c;
         if(c =='C'){
            cin>>i;
            cin>>v;
            i--;
            if(v> 0) v= 1;
            if(v< 0) v= -1;
            ST.update(i,v);
            Vector[i]=v;
         }else{
            cin>>low;
            cin>>high;
            low--;
            high--;
            total=ST.query(low,high);
            if(total>0) cout <<"(+)";
            else{
               if(total< 0) cout <<"(-)";
               else cout<<"(0)";
            }
            }
         }

         cout<<endl;
         cout<<"HOLA MUNDO"<<endl;
         return 0;
         

   /*
4 6
-2 6 0 -1
C 1 10
P 1 4
C 3 7
P 2 2
C 4 -5
P 1 4
   */
}