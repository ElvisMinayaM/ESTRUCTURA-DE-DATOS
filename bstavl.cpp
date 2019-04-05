#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
template <class D, class K>
class AVL;
template <class D, class K>
class Node{
private:
  K key;
  D dato;
  int height;
  Node<D,K>* p_child[2];
public:
  Node(const D & d,const K & k,int h=0);
  ~Node();
  friend class AVL<D,K>;
};

template <class D, class K>
Node<D,K>::Node(const D & d,const K & k,int h){
  dato=d;
  key=k;
  height=h;
  p_child[0]=NULL;
  p_child[1]=NULL;
}
template <class D, class K>
Node<D,K>::~Node(){
  dato=0;
  p_child[0]=NULL;
  p_child[1]=NULL;
}
template <class D, class K>
class AVL{
private:
  Node<D,K>* root;
public:
  AVL();
  ~AVL();
  void insert(const D & d, const K & k);
  bool find(Node<D,K>**tmp,const K & k);
};
template <class D, class K>
AVL<D,K>::AVL(){
  root=NULL;
}
template <class D, class K>
AVL<D,K>::~AVL(){
  root=0; }
template <class D,class K>
bool AVL<D,K>::find(Node<D,K>** tmp,const K & k){
    tmp=&root;
    while(*tmp){
      if((*tmp)->k=k) return true;
      tmp=&(*tmp)->p_child[(*tmp->k<k)];

    }
    return false;

}


template <class D, class K>
bool insert(k &key;D & dato){
  return insert(& root,key,dato){
    bool insert(node **n,k&key,D & dato){
      if(!*n){
        *n=new node(key,dato);
        return true;
      }
      if((*n)->key==key) return false;
      int d= key>(*n)->key;
      if(!insert(&(*n)->p_child[d],key,dato))
        return false;
      //insert true
      //verificacion valance
      (*n)->h=max((*n)->p_child[0]->h,(*n)->p_child[1]->h)+1;
      int f=(*n)->p_child[o]->h-(*n)->p_child[i]->h;
      if(f==-2 or f==2){
      //SE EVALUAN LAS ROTACIONES SIMPLE O DOBLE
      }
      return true;

    }
  }
}

void turn(node **n, int d){
  node *aux=(*n)->p_child[d];
  (*n)->p_child[d]=aux->p_child[!d];
  aux->p_child[!d]=*n;
  *n=aux;
}


int main(){
  
}