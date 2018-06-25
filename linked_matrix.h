#ifndef LINKED_MATRIX_H
#define LINKED_MATRIX_H

#include <string>

//namespace 
namespace linked_matrix_GJK
{

class Dummy
{
};

template<class T>
class MNode;                // forward declaration.  Not really sure if this will work

typedef MNode<Dummy> MNode0;


class LMatrix
{
public:
    LMatrix(); 
    LMatrix(bool **matrix, int m, int n);
    void remove_row(MNode0 *node);
    void restore_row(MNode0 *node);
    ~LMatrix();
private:
    MNode0 *root;
};



template<class T>
class MNode
{
public:
    MNode() : data(NULL), right_link(NULL), left_link(NULL), up_link(NULL), down_link(NULL) {}
    MNode(const T& theData, MNode<T> *theRight = NULL, MNode<T> *theLeft = NULL,
                     MNode<T> *theUp = NULL, MNode<T> *theDown = NULL) : data(theData), right_link(theRight), 
                                                                left_link(theLeft), up_link(theUp), down_link(theDown) {}
    void set_data(const T& theData) {data = theData;}
    T * get_data() const {return data;}
    MNode<T> * right() const {return right_link;}
    MNode<T> * left() const {return left_link;}
    MNode<T> * up() const {return up_link;}
    MNode<T> * down() const {return down_link;}
    void set_right(MNode<T> *const node) {right_link = node;}
    void set_left(MNode<T> *const node) {left_link = node;}
    void set_up(MNode<T> *const node) {up_link = node;}
    void set_down(MNode<T> *const node) {down_link = node;}
    // ~MNode() { data->~T;}
private:
    T * data;
    MNode<T> *right_link;
    MNode<T> *left_link;
    MNode<T> *up_link;
    MNode<T> *down_link;
};



class Column : public MNode0
{
public:
    Column(int theSize=0, std::string theName="") : MNode0(), _size(theSize), _name(theName) {}
    int size() const {return _size;}
    void set_size(int N) {_size = N;}
    std::string name() const {return _name;}
    void set_name(std::string S) {_name = S;}
private:
    int _size;
    std::string _name;
};


template<class T>
void join_lr(MNode<T> *a, MNode<T> *b);

template<class T>
void join_du(MNode<T> *a, MNode<T> *b);


}
#endif