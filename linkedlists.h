#ifndef LINKEDLISTS_H
#define LINKEDLISTS_H

namespace LinkedLists

template<class T>
class Node
{
public:
    Node(T& theData, Node<T> *theRight = NULL, Node<T> *theLeft = NULL) : data(theData), right_link(theRight), left_link(theLeft);
    void append(Node<T> *node) {right_link = node;}
    void prepend(Node<T> *node) {left_link = node;}
    void setData(T& theData) {data = theData;}
    const T * getData() const {return &data;}
    Node<T> * right() const {return right_link;}
    Node<T> * left() const {return left_link;}
private:
    T *data;
    Node<T> *right_link;
    Node<T> *left_link;
};

template<class T>
void join(Node<T> *a, Node<T> *b);

template<class T>
void remove(Node<T> *a);

template<class T>
void insert_left(Node<T> *new_node, Node<T> *a);

template<class T>
void insert_right(Node<T> *new_node, Node<T> *a);

/*
// doubly linked list class
template<class T>
class DLL {
public:
    DLL();
    Node<T> first();
    Node<T> last();
private:
    Node<T> first;
    Node<T> last;
};
*/

#endif