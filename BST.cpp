//Sender Shepard
//This file includes all the challenges that I could think of at the time

#include "BST.h"
#include "list.h"

Binary_Search_Tree::Binary_Search_Tree(const Binary_Search_Tree & list_to_copy)
{
    node * temp = list_to_copy.root;

    copy_list(temp, root);
}

Binary_Search_Tree & Binary_Search_Tree::operator= (Binary_Search_Tree rhs)
{
    swap(*this, rhs); //Copy-swap-idiom related to the exception safety. 

    return *this; //Copy-swap-idiiom removes the need for self-assignment.
}

int Binary_Search_Tree::build(node * & root)
{
    srand( time(NULL) );
    int sum, length = rand() % 20;

    for(int k = 0; k < length; ++k)
        sum += build_helper(root, rand() % 100);

    return sum;
}

int Binary_Search_Tree::build_helper(node * & root, int to_add)
{
    if(!root)
    {
        root = new node(to_add);

        return 1;
    }

    if(to_add < root -> data)
    {
        build_helper(root -> left, to_add);
        
        return balance_tree(root) + height_reset(root);
    }
    build_helper(root -> right, to_add);
    
    return balance_tree(root) + height_reset(root); 
}

int Binary_Search_Tree::delete_item(void)
{
    int num; 
    
    while(root)
    {
        structure();
        cout << "\n\nPlease enter number to delete: ";
        cin >> num; cin.ignore(100, '\n');

        delete_item_helper(root, num);
        cout << endl;
        display();
    }
    return 1;
}

int Binary_Search_Tree::delete_item_helper(node * & root, int item)
{
    if(!root)
        return 0;

    if(root -> data == item)
    {
        cout << "\nDeleting: " << root -> data;

        if(!root -> left and !root -> right)
        {
            delete root;
            root = NULL; 

            return 1;
        }
        else if( (root -> left and !root -> right) or (!root -> left and root -> right) )
        {
            node * temp = root -> left;
            
            if(!root -> left)
                temp = root -> right;
            delete root;
            root = NULL;
            root = temp;

            return height_reset(root);
        }
        else
        {
            node * temp = succesor(root -> right);
            
            if(temp -> left) //If right subtree exists.
            {
                temp -> left -> left = root -> left;
                node * temp2 = temp -> left -> right;//Keeps right subtree. 
                temp -> left -> right = root -> right;     
                delete root;
                root = temp -> left;
                temp -> left = temp2;
            }
            else
            {
                temp -> left = root -> left;
                delete root;
                root = temp;
            }
            
            return height_reset(root);
        }
    }
    delete_item_helper(root -> left, item);
    delete_item_helper(root -> right, item);
    
    return balance_tree(root);
}

Binary_Search_Tree::node * Binary_Search_Tree::succesor(node * root)
{
    node * temp = root;
    
    if(temp -> left)
        if(temp -> left -> left)
            while(temp -> left -> left)
                temp = temp -> left;
    
    return temp;
}   

int Binary_Search_Tree::balance_tree(node * & root)
{
    if( height(root -> left) - height(root -> right) == 2)
        return right_rotation(root); 

    if( height(root -> right) - height(root -> left) == 2)
        return left_rotation(root);

    return 0;
}

int Binary_Search_Tree::left_rotation(node * & root)
{
    if(root -> right -> left and !root -> right -> right) //Right-Left Rotation.
    {
        right_rotation(root -> right);
        left_rotation(root);

        return height_reset(root);
    }
    
    node * temp = root -> right;
    root -> right = temp -> left; //Very important step to not lose right subtree.
    temp -> left = root;
    root = temp; 

    return height_reset(root);
}

int Binary_Search_Tree::right_rotation(node * & root)
{
    if(root -> left -> right and !root -> left -> left) //Left-Right Rotation.
    {
        left_rotation(root -> left);
        right_rotation(root);

        return height_reset(root);
    }

    node * temp = root -> left;
    root -> left = temp -> right; //Very important step to not lose left subtree.
    temp -> right = root;
    root = temp;         
    
    return height_reset(root);
}

int Binary_Search_Tree::height_reset(node * & root)
{
    root -> height = height(root);
    
    if(root -> left)
        root -> left -> height = height(root -> left);
    if(root -> right)
        root -> right -> height = height(root -> right);

    return 1;
}

int Binary_Search_Tree::height(node * & root)
{
    if(!root)
        return 0;

    int left = height(root -> left) + 1;
    int right = height(root -> right) + 1;

    return left > right ? left : right;
}

void Binary_Search_Tree::display(node * root)
{
    if(root)
    {
        display(root -> left);
        cout << " -> " << root -> data;
        display(root -> right); 
    }
}

void Binary_Search_Tree::structure(void)
{
    node * temp = root;

    structure(temp, 1);
}

void Binary_Search_Tree::structure(node * temp, int level)
{
    if( temp )
    {
        structure(temp -> right, ++level);

        cout << endl;

        if(temp == root)
            cout << "Root -> ";

        else 
            for(int i = 0; i < level; ++i)
                cout << "     ";

        cout << temp -> data << ":" << temp -> height;

        structure(temp -> left, level);
    }
}

int Binary_Search_Tree::length(node * root)
{
    if(!root)
        return 0;

    return length(root -> left) + length(root -> right) + 1;
}

void Binary_Search_Tree::destroy(node * & root)
{
    if(!root)
        return;
    
    destroy(root -> left);
    destroy(root -> right);
    delete root;
    root = NULL;
}

void Binary_Search_Tree::copy_list(node * & source, node * & destination)
{
    if(!source)
        return;

    destination = new node(source -> data);
    
    copy_list(source -> left, destination -> left);
    copy_list(source -> right, destination -> right);
}

void Binary_Search_Tree::swap(Binary_Search_Tree & first, Binary_Search_Tree & second)
{
    node * temp = first.root;
    first.root = second.root;
    second.root = temp;
}

int Binary_Search_Tree::copy_from_LLL(Linear_Linked_List & list)
{
    int length = list.length();    
    int * list_array = list.return_list_array(list);

    for(int i = 0; i < length; ++i)
        build_helper(root, list_array[i]);

    delete [] list_array;

    return * list_array;
}

int * Binary_Search_Tree::return_tree_array(Binary_Search_Tree & tree)
{
    int length = tree.length();
    static int * array = new int[length];

    return_tree_array_helper(tree.root, array, 0);
    
    return array;
}

int Binary_Search_Tree::return_tree_array_helper(node * & root, int * array, int array_index)
{
    static int index = 0;

    if(root)
    {       
        array[index] = root -> data;

        return_tree_array_helper(root -> left, array, ++index);
        return_tree_array_helper(root -> right, array, index);
    }

    return 0;
}


