#include <iostream>
using namespace std;


class ArbolRB{    
    enum Color { RED, BLACK, DOUBLE_BLACK };

    struct Node {
        int data;
        int color;
        //p_child[2]; -> left rigth
        Node *left, *right, *parent;
        
        Node(int data):data(data),color(RED) {
            left = NULL;
            right = NULL;
            parent = NULL;
        }
    } *root;
    


    void rotate_left(Node *&node) {
        Node *r_child = node->right;
        node->right = r_child->left;
        
        if (node->right) node->right->parent = node;
        
        r_child->parent = node->parent;
        
        if (!node->parent) root = r_child;
        else if (node == node->parent->left)
            node->parent->left = r_child;
        else
            node->parent->right = r_child;
        
        r_child->left = node;
        node->parent = r_child;
    }

    void rotate_right(Node *&node) {
        Node *l_child = node->left;
        node->left = l_child->right;
        
        if (node->left) node->left->parent = node;
        
        l_child->parent = node->parent;
        
        if (!node->parent) root = l_child;
        else if (node == node->parent->left)
            node->parent->left = l_child;
        else
            node->parent->right = l_child;
        
        l_child->right = node;
        node->parent = l_child;
    }


    void fix_insert_rbtree(Node *&node) {
        Node *parent = NULL;
        Node *g_parent = NULL;
        
        while (node != root && get_color(node) == RED &&
                get_color(node->parent) == RED) {
            parent = node->parent;
            g_parent = parent->parent;
            if (parent == g_parent->left) {
                Node *uncle = g_parent->right;
                if (get_color(uncle) == RED) {
                    set_color(uncle, BLACK);
                    set_color(parent, BLACK);
                    set_color(g_parent, RED);
                    node = g_parent;
                } else {
                    if (node == parent->right) {
                        rotate_left(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotate_right(g_parent);
                    std::swap<int>(parent->color, g_parent->color);
                    node = parent;
                }
            } else {
                Node *uncle = g_parent->left;
                if (get_color(uncle) == RED) {
                    set_color(uncle, BLACK);
                    set_color(parent, BLACK);
                    set_color(g_parent, RED);
                    node = g_parent;
                } else {
                    if (node == parent->left) {
                        rotate_right(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotate_left(g_parent);
                    std::swap<int>(parent->color, g_parent->color);
                    node = parent;
                }
            }
        }
        set_color(root, BLACK);
    }
    void remove_rb(Node *&node) {
        if (!node) return;
        if (node == root) {
            root = nullptr;
            return;
        }
        
        if (get_color(node) == RED || get_color(node->left) == RED ||
            get_color(node->right) == RED) {
            Node *child = node->left ? node->left : node->right;
            
            if (node == node->parent->left) {
                node->parent->left = child;
                if (child) child->parent = node->parent;
                set_color(child, BLACK);
                delete node;
            } else {
                node->parent->right = child;
                if (child) child->parent = node->parent;
                set_color(child, BLACK);
                delete node;
            }
        } else {
            Node *sibling = nullptr;
            Node *parent = nullptr;
            Node *ptr = node;
            set_color(ptr, DOUBLE_BLACK);
            while (ptr != root && get_color(ptr) == DOUBLE_BLACK) {
                parent = ptr->parent;
                if (ptr == parent->left) {
                    sibling = parent->right;
                    if (get_color(sibling) == RED) {
                        set_color(sibling, BLACK);
                        set_color(parent, RED);
                        rotate_left(parent);
                    } else {
                        if (get_color(sibling->left) == BLACK &&
                            get_color(sibling->right) == BLACK) {
                            set_color(sibling, RED);
                            if (get_color(parent) == RED)
                                set_color(parent, BLACK);
                            else
                                set_color(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (get_color(sibling->right) == BLACK) {
                                set_color(sibling->left, BLACK);
                                set_color(sibling, RED);
                                rotate_right(sibling);
                                sibling = parent->right;
                            }
                            set_color(sibling, parent->color);
                            set_color(parent, BLACK);
                            set_color(sibling->right, BLACK);
                            rotate_left(parent);
                            break;
                        }
                    }
                } else {
                    sibling = parent->left;
                    if (get_color(sibling) == RED) {
                        set_color(sibling, BLACK);
                        set_color(parent, RED);
                        rotate_right(parent);
                    } else {
                        if (get_color(sibling->left) == BLACK &&
                            get_color(sibling->right) == BLACK) {
                            set_color(sibling, RED);
                            if (get_color(parent) == RED)
                                set_color(parent, BLACK);
                            else
                                set_color(parent, DOUBLE_BLACK);
                            ptr = parent;
                        } else {
                            if (get_color(sibling->left) == BLACK) {
                                set_color(sibling->right, BLACK);
                                set_color(sibling, RED);
                                rotate_left(sibling);
                                sibling = parent->left;
                            }
                            set_color(sibling, parent->color);
                            set_color(parent, BLACK);
                            set_color(sibling->left, BLACK);
                            rotate_right(parent);
                            break;
                        }
                    }
                }
            }
            if (node == node->parent->left)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
            delete node;
            set_color(root, BLACK);
        }
    }

    int get_color(Node *&node) {
        return node ? node->color : BLACK;
    }
    void set_color(Node *&node, int color) {
        if (!node) return;
        node->color = color;
    }


    Node *insert_bst(Node *&root, Node *&node) {
        if (!root) return node;
        if (node->data < root->data) {
            root->left = insert_bst(root->left, node);
            root->left->parent = root;
        } else if (node->data > root->data) {
            root->right = insert_bst(root->right, node);
            root->right->parent = root;
        }
        return root;
    }
    Node *delete_bst(Node *&root, int data) {
        if (!root) return root;
        
        if (data < root->data)
            return delete_bst(root->left, data);
        if (data > root->data)
            return delete_bst(root->right, data);
        
        if (!root->left || !root->right) return root;
        
        Node *t = min_value_node(root->right);
        root->data = t->data;
        return delete_bst(root->right, t->data);
    }
    
    Node *min_value_node(Node *&node) {
        Node *ptr = node;
        while (ptr->left)
            ptr = ptr->left;
        
        return ptr;
    }
    Node *max_value_node(Node *&node) {
        Node *ptr = node;
        while (ptr->right)
            ptr = ptr->right;
            
        return ptr;
    }
    
public:
    ArbolRB() : root(NULL) { }
    
    void insert(int data) {
        Node *t = new Node(data);
        root = insert_bst(root, t);
        fix_insert_rbtree(t);
    }
    
    void remove(int data) {
        Node *t = delete_bst(root, data);
        remove_rb(t);
    }
    

};

int main() {
    ArbolRB rbt;
    rbt.insert(1);
    cout<<"HOLA MUNDO"<<endl;
    rbt.remove(1);
    cout<<"HOLA MUNDO"<<endl;
    return 0;
}
