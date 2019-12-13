//Sender Shepard
#include "BST.h"

const int SIZE = 4;

class Graph: public List
{
    private:        

        struct edge{
            int edge_data;
            edge * next_edge;
            edge(int d) { edge_data = d; next_edge = NULL; }
        };

        struct vertex{
            int vertex_data;
            edge * head;
        } * adjacency_list;
        
        int vertices;

    public:
        Graph(void);
        ~Graph(void) {}
        int build(void) { return build(adjacency_list); }
        void display(void) { display(adjacency_list); }

    protected:
        int build(vertex * & a_vertex); 
        int add_edge(edge * & head, int to_add);
        int is_edge(edge * vertex_head, int edge);
        int fastest_path(int a, int b);
        void display(vertex * graph);
};

