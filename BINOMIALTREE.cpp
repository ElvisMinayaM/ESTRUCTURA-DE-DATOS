#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;
template <class T,size_t n=64>
class BHeap;

template <class T>
class BTree{
    T dato;
    vector<BTree<T>*>p_child;
    int max;
public:
    BTree(const T d){
        dato=d;
    }

    friend class BHeap<T>;
};

template <class T,size_t n>
class BHeap{
    BTree<T> * head[n];
public:
    BHeap(){
        memset(head,0,sizeof(head));
    }


    //UNION DE PARTE 1 Y PARTE 2
    BTree<T> * Union(BTree<T> * p1,BTree<T> *p2){
        if(p1->dato>p2->dato){
            p2->p_child.push_back(p1);
            return p2;
        }
        p1->p_child.push_back(p2);
        return p1;
    }
    void Insert(const T & d){
        Insert(new BTree<T>(d));
    }
    //INNSERT
    /*
    template <typename T>
void BinomialHeap<T>::insert(T v)
{
	BinomialNode<T> *p = head?  head->parent:  nullptr;
	BinomialNode<T> *singleton = new BinomialNode<T>(v, p);
	head = unionHeap(singleton, head);

}
	*/
    void Insert(BTree<T> *b){
        int i=b->p_child.size();
        if(!head[i]){
            head[i]=b;
            return;
        }
        Insert(Union(head[i],b));
        head[i]=0;
      }


    //SACAR EL VALOR MINIMO
    BTree<T> * VMin(){
        BTree<T> * t;
        bool c=1;
        for(int i=0;i<n;i++){
            if(head[i]){
                if(c){
                    t=head[i];
                }
                if(head[i]->dato<t->dato){
                    t=head[i];
                }
                c=0;
            }
            cout<<i<<endl;
        }
        return t;
    }


    //eliminar valor minimo VMIN
    void Delete(){
        BTree<T> *temp;
        temp=VMin();
        for(int i=0;i<n;i++){
            if(!head[i]){
                head[i]=temp;
            }
            else
                Union(head[i],temp);
        }
        delete temp;
    }

    

};


int main(){
    BHeap<int> Binomial;
    Binomial.Insert(5);
    Binomial.Insert(4);
    Binomial.Insert(6);
    Binomial.Insert(3);
    Binomial.Insert(7);
    Binomial.VMin();
   
    cout<<"hola mundo"<<endl;
}
