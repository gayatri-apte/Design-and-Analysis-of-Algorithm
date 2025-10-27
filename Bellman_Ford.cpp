#include "bits/stdc++.h"
using namespace std;

struct Edge
{
    int src, dest, weight;
};

class BF
{
    int V, E;
    vector<Edge> edges;
    public:
    void input()
    {
        cout<<"Enter the number of vertices:"<<endl;
        cin>>V;
        cout<<"Enter the number of Edges:"<<endl;
        cin>>E;
        cout<<"Enter the ehes in format as src, dest and weight:"<<endl;
        for(int i =0; i<E; i++)
        {
            Edge edge;
            cout<<"Enter the edge"<<i+1<<endl;
            cin>>edge.src>>edge.dest>>edge.weight;
            edges.push_back(edge);
        }
    }

    void Bellman_ford()
    {
        int src;
        cout<<"Enter the source vertex";
        cin>>src;
        vector<int> output(V, INT_MAX);
        vector<int> parent(V);
        output[src] = 0;
        for(int i =0; i< V-1; i++)
        {
            for(auto edge:edges)
            {
                int u = edge.src;
                int v = edge.dest;
                int weight = edge.weight;
                if(output[u]!=INT_MAX && output[u]+ weight < output[v])
                {
                    output[v] = output[u] + weight;
                    parent[v] = u;
                }
            }
        }
        for(auto edge : edges)
        {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if(output[u]!= INT_MAX && output[u] + weight < output[v])
            {
                cout<<"Graph contains negative cycle.";
                return;
            }

        }
        cout<<"Vertex\tparent\tDistance from Source"<<endl;
        for(int i =0; i< V; i++)
        {
            if(output[i]==INT_MAX)
            {
                cout<<i<<"\t"<<parent[i]<<"\t"<<"INF"<<endl;
            }
            else
            {
                cout<<i<<"\t"<<parent[i]<<"\t"<<output[i]<<endl;
            }
        }
    }

};
int main()
{
    BF bf;
    bf.input();
    bf.Bellman_ford();
    return 0;
}