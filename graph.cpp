//Sender Shepard
#include "graph.h"

Graph::Graph()
{
    vertices = SIZE;
    adjacency_list = new vertex[vertices];
}

int Graph::build(vertex * & a_vertex)
{
    srand( time(NULL) );

    for(int i = 0; i < vertices; ++i)
    {
        adjacency_list[i].vertex_data = i + 1;
        
        //for(int k = 0; k < rand() % vertices; ++k)
          //      add_edge(adjacency_list[i].head, rand() % vertices + 1);

    }
    
    add_edge(adjacency_list[0].head, 2);
    add_edge(adjacency_list[0].head, 3);
    add_edge(adjacency_list[1].head, 3);
    add_edge(adjacency_list[2].head, 4);
    add_edge(adjacency_list[3].head, 1);

    return 0; 
}

int Graph::add_edge(edge * & head, int to_add)
{
    if(is_edge(head,to_add))
        return 0;

    if(!head)
    {
        head = new edge(to_add);
        
        return 1;
    }

    return add_edge(head -> next_edge, to_add); 
}

int fastest_path(int a, int b)
{
    return 0;
}

int Graph::is_edge(edge * vertex_head, int edge)
{
    while(vertex_head)
    {
        if(vertex_head -> edge_data == edge)
            return 1;
        
        vertex_head = vertex_head -> next_edge;
    }
    
    return 0;
}

void Graph::display(vertex * graph)
{
    for(int i = 0; i < vertices; i++)
    {
        cout << "Vertex: " << adjacency_list[i].vertex_data;
        
        while(adjacency_list[i].head)
        {
            cout << "\t -> " << adjacency_list[i].head -> edge_data;
            adjacency_list[i].head = adjacency_list[i].head -> next_edge;
        }
        cout << endl;
    }
}

