
namespace dancing_links_GJK
{

typedef linked_matrix_GJK::MNode MNode;
typedef linked_matrix_GJK::LMatrix LMatrix;
typedef linked_matrix_GJK::Column Column;

typedef std::vector<int> S_Stack;

enum class RC {row, column};
struct RC_Item {
    Node* node;
    RC type;
};
typedef std::stack<RC_Item> RC_Stack;
typedef std::stack<RC_Stack> H_Stack;



bool DLX(LMatrix& M, S_Stack& solution, H_Stack& history);



Column* choose_column(LMatrix& M);



void update(LMatrix& M, S_Stack& solution, H_Stack& history, Node *r);



void downdate(LMatrix& M, S_Stack& solution, H_Stack& history);
    
    
}