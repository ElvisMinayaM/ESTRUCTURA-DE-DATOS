
#include <iostream>
#include <functional>

template<class Key, class T>
class AvlTree
{
private:
	struct Node 
	{
		int height;
		Key key;
		T data;
		Node *left;
		Node *right;
	} *root;

public:
	AvlTree() { root = NULL; }

	void insert(const Key& key, const T& data) 	{ root = _rcv_insert(root, key, data); }
	void erase(const Key& key) 					{ root = _del_node(root, key); }
	const T& search(const Key& key)				
	{ 
		if (root == NULL) return T();
		return _find(root, key)->data;
	}

	// Para hacer pruebas.
	inline void preOrder()
	{
		std::function<void(Node*)> ly = [&ly](Node *node) { 
			if (node) {
				std::cout << node->key << " ";
				ly(node->left);
				ly(node->right);
			}
		};
		ly(root);
		std::cout << std::endl;
	}

private:
	// Agregar nodo.
	Node *_rcv_insert(Node *node, const Key& key, const T& data)
	{
		if (node == NULL) 
			return _mk_node(key, data);

		if (key < node->key)
			node->left = _rcv_insert(node->left, key, data);
		else if (key > node->key)
			node->right = _rcv_insert(node->right, key, data);
		else 
			return node; // Si son iguales las claves no se inserta.

		// Actualizar la altura de este nodo pasado.
		node->height = 1 + _max(_height(node->left),
								_height(node->right));

		// Obtener el balance de este nodo pasado y chequea si este nodo esta desbalanceado.
		int balance = _get_balance(node);

		// (PARTE IZQUIERDA) En el caso izquierdo
		/*
			   Root
			   	|
			 L------R
			(l)-r
		*/
		if (balance > 1 && key < node->left->key)
			return _r_rotation(node);

		// (PARTE DERECHA) En el caso derecho
		/*
			   Root
			   	|
			 L------R
				   l-(r)
		*/
		if (balance < -1 && key > node->right->key)
			return _l_rotation(node);

		// (PARTE IZQUIERDA) En el caso derecho
		/*
			   Root
			   	|
			 L------R
			l-(r)
		*/
		if (balance > 1 && key > node->left->key) 
		{
			node->left = _l_rotation(node->left);
			return _r_rotation(node);
		}

		// (PARTE DERECHA) En el caso izquierdo
		/*
			   Root
			   	|
			 L------R
				  (l)-r
		*/
		if (balance < -1 && key < node->right->key)
		{
			node->right = _r_rotation(node->right);
			return _l_rotation(node);
		}

		// Nodo sin ningun cambio
		return node;
	}

	// Eliminar nodo.
	Node *_del_node(Node *node, const Key& key)
	{
		if (node == NULL) 
			return node;

		if (key < node->key)		// El nodo a eliminar esta en la parte izquierda de la raiz.
			node->left = _del_node(node->left, key);
		else if (key > node->key)	// El nodo a eliminar esta en la parte derecha de la raiz.
			node->right = _del_node(node->right, key);
		else						// El nodo a eliminar es la raiz.
		{
			if ((node->left == NULL) || (node->right == NULL))
			{
				Node *aux = node->left
							? node->left
							: node->right;

				if (aux == NULL) 
				{ // Si no tiene hijos
					aux = node;
					node = NULL;
				}
				else // Si tiene un hijo
					*node = *aux; // Copiar el contenido del hijo no vacio

				delete aux;
			}
			else // Nodo con dos hijos
			{
				Node *aux = _min_value_node(node->right); // Obtener el inorder
				node->key = aux->key;
				node->right = _del_node(node->right, aux->key);
			}
		}

		if (!node)
			return node;

		node->height = _max(_height(node->left),
							_height(node->right)) + 1;

		int balance = _get_balance(node);

		// Izquierda - caso izquierdo
		if (balance > 1 && _get_balance(node->left) >= 0)
			return _r_rotation(node);
		// Izquierda - caso derecho
		if (balance > 1 && _get_balance(node->left) < 0)
		{
			node->left = _l_rotation(node->left);
			return _r_rotation(root);
		}
		// Derecho - caso derecho
		if (balance < -1 && _get_balance(node->right) <= 0)
			return _l_rotation(node);
		// Derecho - caso izquierdo
		if (balance < -1 && _get_balance(node->right) > 0)
		{
			node->right = _r_rotation(node->right);
			return _l_rotation(node);
		}

		return node;
	}

	// Buscar un nodo
	Node *_find(Node *node, const Key& key)
	{
		if (node == NULL || node->key == key)
			return node;
		if (node->key < key) // Parte derecha
			return _search(node->right, key);

		// Parte izquierda
		return _search(node->left, key);
	}

	// Rotaciones
	Node *_r_rotation(Node *y)	// Derecha
	{
		Node *x = y->left;
		Node *T2 = x->right;
		// Rotacion
		x->right = y;
		y->left = T2;
		// Actualizar alturas
		y->height = _max(_height(y->left),
						 _height(y->right)) + 1;
		x->height = _max(_height(x->left),
						 _height(x->right)) + 1;
		// Nueva raiz
		return x;
	}

	Node *_l_rotation(Node *x)	// izquierda
	{
		Node *y = x->right;
		Node *T2 = y->left;
		// Rotacion
		y->left = x;
		x->right = T2;
		// Actualizar alturas
		x->height = _max(_height(x->left),
						 _height(x->right)) + 1;
		y->height = _max(_height(y->left),
						 _height(y->right)) + 1;
		// La nueva raiz
		return y;
	}

	// Utilidades
	int _max(int x, int y) { return x>y ? x : y; }

	int _height(Node *node) 
	{ 
		return node != NULL
				? node->height
				: 0; 
	}

	int _get_balance(Node *node) 
	{ 
		return node != NULL
				? _height(node->left) - _height(node->right) 
				: 0;	
	}

	Node *_mk_node(const Key& key, const T& data)
	{
		Node *n = new Node();
		n->height = 1;
		n->key = key;
		n->data = data;
		n->left = NULL;
		n->right = NULL;
		return n;
	}

	Node *_min_value_node(Node *node)
	{
		Node *aux = node;
		while (aux->left != NULL)
			aux = aux->left;
		return aux;
	}
};

int main(){
	AvlTree<int,int> v;
	v.insert(1,20);
	


	return 0;
}
