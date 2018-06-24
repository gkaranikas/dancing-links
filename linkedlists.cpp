#include "linkedlist.h"

namespace LinkedLists

template<class T>
void join(Node<T> *a, Node<T> *b) {
    if(a != NULL) a->append(b);
    if(b != NULL) b->prepend(a);    
}

template<class T>
void remove(Node<T> *a) {
    Node<T> *l = a->left();
    Node<T> *r = a->right();
    join(l,r);
}

template<class T>
void insert_left(Node<T> *new_node, Node<T> *a) {
    Node<T> *l = a->left();
    join(new_node,a);
    join(l,new_node);
}

template<class T>
void insert_right(Node<T> *new_node, Node<T> *a) {
    Node<T> *r = a->right();
    join(a,new_node);
    join(new_node,r);
}