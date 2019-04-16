#include <stack>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

template<class T>
class Nodo        							// clase nodo
{
public:           							// datos publicos.
	T Dato;     							// Dato.
	int fe;
	Nodo<T> *Hijo[2];                       // Crea 2 hijos tipo T de Nodo
	Nodo(T d)
    {  							            // Constructor
		Dato=d;   							// Inicializa Dato a valor d(nosotros definimos este dato)
		Hijo[0]=Hijo[1]=0;                  // Hijos inicializados en cero
		fe=0;
	}
};

template<class T>
class Arbol                                 // Clase arbol
{
public:			  							// datos publicos
	Nodo<T> *Raiz;							// Puntero raiz tipo nodo
	Arbol()
    {      							        // Constructor arbol
		Raiz=0;
	}

void RII(Nodo<T> *&p){						//Rotacion Izquierda Izquierda

	Nodo<T> *q=p->Hijo[0];
    p->Hijo[0]=q->Hijo[1];
    q->Hijo[1]=p;
    q->fe=p->fe=0;
    p=q;
}
void RDD(Nodo<T> *&p){						//Rotacion Derecha Derecha

    Nodo<T> *q=p->Hijo[1];
    p->Hijo[1]=q->Hijo[0];
    q->Hijo[0]=p;
    q->fe=p->fe=0;
    p=q;
}

void RID(Nodo<T> *&p){						//Rotacion Izquierda Derecha

	Nodo<T> *q=p->Hijo[0];
    Nodo<T> *r=q->Hijo[1];
    q->Hijo[1]=r->Hijo[0];
    p->Hijo[0]=r->Hijo[1];
    r->Hijo[0]=q;
    r->Hijo[1]=p;
    if(r->fe==0)
        r->fe=p->fe=q->fe=0;
    else
        if(r->fe==-1){
            r->fe=-1;
            q->fe=1;
            p->fe=0;
        }
    p=r;
}

void RDI(Nodo<T> *&p){						//Rotacion Derecha Izquierda

	Nodo<T> *q=p->Hijo[1];
    Nodo<T> *r=q->Hijo[0];
    q->Hijo[0]=r->Hijo[1];
    p->Hijo[1]=r->Hijo[0];
    r->Hijo[1]=q;
    r->Hijo[0]=p;
    if(r->fe==0)
        r->fe=p->fe=q->fe=0;
    else
        if(r->fe==-1){
            r->fe=-1;
            q->fe=1;
            p->fe=0;
        }
    p=r;
}

void Insert(T d)
{
  Insert(d,this->Raiz);
}

void Insert(T d,Nodo<T> *&p){

	if(!p){
        p=new Nodo<T> (d);
        return;
    }
    if(p->Dato==d) return;
    Insert(d,p->Hijo[p->Dato<d]);
    if(p->Dato<d)
        p->fe++;
    else
        p->fe--;
    switch(p->fe){
        case 0: return;
        case -2: if(p->Hijo[0]->fe<0)
                    RII(p);
                 else
                    RID(p); break;
        case 2: if(p->Hijo[1]->fe>0)
                    RDD(p);
                else
                    RDI(p); break;
    }
}

void Profundidad(Nodo<T> *p){

	stack<Nodo<T> *> Pila;
    Pila.push(Raiz);
    while(!Pila.empty()){
        Nodo<T> *tmp=Pila.top();
        Pila.pop();
        cout<<tmp->Dato<< " ";
        if(tmp->Hijo[1])
            Pila.push(tmp->Hijo[1]);
        if(tmp->Hijo[0])
            Pila.push(tmp->Hijo[0]);
    }
}

void PrintDot(Nodo<T> *n, ofstream & os){

	if(n!=0){   						            // Si n es diferente a 0 significa que no esta vacio
		if(n->Hijo[0])  os<<n->Dato<<"->"<<n->Hijo[0]->Dato<<endl;//Si tiene hijo izquierdo imprime su dato y el de su hijo
		if(n->Hijo[1])  os<<n->Dato<<"->"<<n->Hijo[1]->Dato<<endl;//si tiene hijo derecho imprime su dato y el hijo
		PrintDot( n->Hijo[0] ,os);			// llama la funcion tomando a n apuntando a su hijo izquierdo
		PrintDot( n->Hijo[1] ,os);			// Finalmente lo mismo pero con n apuntando a su hijo derecho
	}
}

void PrintDot(char * p){
	 ofstream file(p);
	 file<<"digraph {"<<endl;
	 PrintDot(this->Raiz,file);
        file<<" }"<<endl;
	}
};

int main()
{
    cout << "Hello world!" << endl;
    Arbol<int> AVL;
    for(int i=0;i<10;i++){
    	AVL.Insert(i);
	}
	/*
    AVL.Insert(8);
    AVL.Insert(4);
    AVL.Insert(5);
    AVL.Insert(6);*/
    AVL.Profundidad(AVL.Raiz);
    AVL.PrintDot("salida.dot");
    system("dot -Tpng salida.dot -o archivo.png");

    return 0;
}
