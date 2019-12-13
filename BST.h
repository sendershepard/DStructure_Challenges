//Sender Shepard
//This is the .h file containing all of the
//classes making use of OOP

#include <cstdlib>
#include<iostream>

using namespace std;

#ifndef LIST
#define LIST

class Linear_Linked_List; //Forward declaration e.g. LLL * list;

class List
{
    protected:

    public:
        List(void) { }
        virtual ~List(void) { }
        virtual int build(void) = 0;
        virtual void display(void) = 0;
        void print(void) { this -> display(); }
};

class Binary_Search_Tree: public List
{
    private:
        struct node {
            int data, height;
            node * left, * right;
            node(int d) { data = d; left = right = NULL; height = 1; }
        };
        node * root;

    public:
        Binary_Search_Tree(void) : root(NULL) {}
        //The Big Three
        Binary_Search_Tree(const Binary_Search_Tree & root); //Copy Constructor
        ~Binary_Search_Tree(void) { destroy(root); }
        Binary_Search_Tree & operator= (Binary_Search_Tree rhs); //Assignment Operator.
        //Public functions.
        int build(void) { return build(root); }
        int length(void) { return length(root); }
        void destroy(void) { destroy(root); }
        void display(void) { display(root); }
        int delete_item(void);
        void structure(void);
        int copy_from_LLL(Linear_Linked_List & list);
        int * return_tree_array(Binary_Search_Tree & tree);
        int return_tree_array_helper(node * & root, int * array, int index);

        friend ostream& operator<< (ostream & o, Binary_Search_Tree & bst ) {
            bst.display(); return o; }

       
    protected:
        int build(node * & root);
        int build_helper(node * & root, int to_add);
        void display(node * root);
        int length(node * root);
        int height(node * & root);
        int height_reset(node * & root);
        int right_rotation(node * & root);
        int left_rotation(node * & root);
        void destroy(node * & root);
        int delete_item_helper(node * & root, int item);
        int balance_tree(node * & root);
        node * succesor(node * root);
        void structure(node * temp, int level);
        void copy_list(node * & source, node * & destination);
        void swap(Binary_Search_Tree & first, Binary_Search_Tree & second);
};

#endif
