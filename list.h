//Sender Shepard
#include "BST.h"
#include "graph.h"

class Linear_Linked_List: public List 
{
     private:
        struct node {
            int data;
            node * next;
            node(int d) { data = d; next = NULL; }
        };
        node * head;

     public:
        Linear_Linked_List(void) : head(NULL) {} //Default Constructor. 
        //The Big Three
        Linear_Linked_List(const Linear_Linked_List & head); //Copy Constructor.
        ~Linear_Linked_List(void) { destroy(head); } //Destructor for LLL. 
        Linear_Linked_List & operator= (Linear_Linked_List rhs); //Assignment Operator.
        //Public functions. 
        int build(void) { return build(head); }
        int length(void) { return list_length(head); }
        void display(void) { display(head); }        
        void destroy(void) { destroy(head); }
        int copy_from_BST(Binary_Search_Tree & tree);
        int * return_list_array(Linear_Linked_List & list);
        int return_list_array_helper(node * & head, int * array, int array_index);

        friend ostream& operator<<(ostream& o, Linear_Linked_List & ls) { 
            ls.display(); return o; }


     protected:
        int build(node * & head);
        int build_helper(node * & head, int counter);
        void display(node * head);
        void copy_list(node * & source, node * & destination);
        int list_length(node * head);
        void destroy(node * & head);
        int insert_before(node * & head);
        int insert_multiple(node * & head, int multiple);
        void swap(Linear_Linked_List & first, Linear_Linked_List & second); 
};

