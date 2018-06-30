#ifndef LINKED_MATRIX_H
#define LINKED_MATRIX_H

#include <string>

//namespace 
namespace linked_matrix_GJK
{


template<class T>
class MNode;                // forward declaration

/*
class Dummy
{
};
typedef MNode<Dummy> MNode0;
*/

class Column;

class MData
{
public:
    MData(int r=-1, Column *c=NULL) : row_id(r), column_id(c) {}
    int row_id;
    Column *column_id;
};

typedef MNode<MData> MNode0;

class LMatrix
{
public:
    LMatrix(); 
    LMatrix(bool **matrix, int m, int n);
    MNode0* head() const;
    bool is_trivial() const;
    int num_rows() const;
    void remove_row(MNode0 *node);
    void restore_row(MNode0 *node);
    void remove_column(MNode0 *node);
    void restore_column(MNode0 *node);
    ~LMatrix();
private:
    MNode0 *root;
    int row_count;
};

void DEBUG_display(LMatrix&);

template<class T>
class MNode
{
public:
    MNode(const T& theData, MNode<T> *theRight = NULL, MNode<T> *theLeft = NULL,
          MNode<T> *theUp = NULL, MNode<T> *theDown = NULL) 
          : _data(theData), right_link(theRight), left_link(theLeft), up_link(theUp), down_link(theDown) {}
    void set_data(const T& theData) {_data = theData;}
    T& data() const {return const_cast<T&>(_data);}  // don't know why I have to cast it, but compiler otherwise complains
    MNode<T> * right() const {return right_link;}
    MNode<T> * left() const {return left_link;}
    MNode<T> * up() const {return up_link;}
    MNode<T> * down() const {return down_link;}
    void set_right(MNode<T> *node) {right_link = node;}
    void set_left(MNode<T> *node) {left_link = node;}
    void set_up(MNode<T> *node) {up_link = node;}
    void set_down(MNode<T> *node) {down_link = node;}
private:
    T _data;
    MNode<T> *right_link;
    MNode<T> *left_link;
    MNode<T> *up_link;
    MNode<T> *down_link;
};



class Column : public MNode0
{
public:
    Column(const MData& theData, int theSize=0, ::std::string theName="") 
        : MNode0(theData), _size(theSize), _name(theName) {}
    int size() const {return _size;}
    void set_size(int N) {_size = N;}
    void add_to_size(int N) {_size += N;}
    ::std::string name() const {return _name;}
    void set_name(::std::string S) {_name = S;}
private:
    int _size;
    ::std::string _name;
};


template<class T>
void join_lr(MNode<T> *a, MNode<T> *b);

template<class T>
void join_du(MNode<T> *a, MNode<T> *b);


}
#endif