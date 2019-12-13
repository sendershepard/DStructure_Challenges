//Sender Shepard
#include "list.h"

//Copy Constructor.
Linear_Linked_List::Linear_Linked_List(const Linear_Linked_List & list_to_copy)
{ 
    node * temp = list_to_copy.head;
    
    copy_list(temp, head);
}

//Assigment Operator.
//We pass by value increasing optimization in the compilier since we are copying the object.
Linear_Linked_List & Linear_Linked_List::operator= (Linear_Linked_List rhs)
{
    swap(*this, rhs); //Copy-swap-idiom related to exception safety.

    return *this; //Copy-swap-idiom removes the need for self-assignment.
}

//Functions that builds a LLL and returns sum of list. Uses random number generator
int Linear_Linked_List::build(node * & head)
{
    srand( time(NULL) );
    int sum, length = rand() % 20;

    for(int k = 0; k < length; ++k)
        sum += build_helper(head, rand() % 100);

    return sum;
}

int Linear_Linked_List::build_helper(node * & head, int to_add)
{
    if(!head)
    {
        head = new node(to_add);

        return 1;
    }

    return build_helper(head -> next, to_add);
}

void Linear_Linked_List::display(node * head)
{
    if(!head)
        return;

    cout << head -> data;
    if(head -> next)
        cout << " -> ";

    return display(head -> next);
}

//Deep copies the whole list. 
void Linear_Linked_List::copy_list(node * & source, node * & destination)
{
    if(!source)
        return;

    destination = new node(source -> data); 

    copy_list(source -> next, destination -> next);
}

//Returns the amount of nodes found on the Linear Linked List.
int Linear_Linked_List::list_length(node * head)
{
    if(!head)
        return 0;

    return list_length(head -> next) + 1;
}

//Deletes all the dyamically allocated memory
void Linear_Linked_List::destroy(node * & head)
{
    while(head)
    {
        node * temp = head;
        head = head -> next;
        delete temp;
    }

    head = NULL; //Once the list has been deleted, reset head to point NULL;
}

void Linear_Linked_List::swap(Linear_Linked_List & first, Linear_Linked_List & second)
{
    node * temp = first.head;
    first.head = second.head;
    second.head = temp;
}

//Insert a node before every multiple of [n] in a LLL. Return the average of the new list
int Linear_Linked_List::insert_before(node * & head)
{
    int multiple = rand() % list_length(head);

    if(multiple == 0)
        ++multiple;

    cout << "\nInserting: " << multiple << " before every node that is a multiple.\n";

    return insert_multiple(head, multiple) / list_length(head);
}

int Linear_Linked_List::insert_multiple(node * & head, int multiple)
{
    if(!head)
        return 0;

    if(head -> data % multiple == 0)
    {
        cout << "Inserting: " << multiple << " before " << head -> data << endl;

        node * temp = new node(multiple);
        temp -> next = head;
        head = temp;

        return insert_multiple(head -> next -> next, multiple) + head -> data + 
            head -> next -> data;
    }

    return insert_multiple(head -> next, multiple) + head -> data;
}

int Linear_Linked_List::copy_from_BST(Binary_Search_Tree & tree)
{
    int length = tree.length();
    int * tree_array = tree.return_tree_array(tree);
    
    for(int i = 0; i < length; ++i)
        build_helper(head, tree_array[i]);
   
    delete [] tree_array;
    
    return * tree_array;
}

int * Linear_Linked_List::return_list_array(Linear_Linked_List & list)
{
    int length = list.length();
    static int * array = new int[length];

    return_list_array_helper(list.head, array, 0);

    return array;
}

int Linear_Linked_List::return_list_array_helper(node * & head, int * array, int array_index)
{
    static int index = 0;

    if(head)
    {
        array[index] = head -> data;

        return_list_array_helper(head -> next, array, ++index);
    }
    
    return 0;
}


