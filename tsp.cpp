#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#define SIZE 5
#define INF INT_MAX
using namespace std;

void printmatrix(int matrix[][SIZE])
{
    for(int i =0; i<SIZE; i++)
    {
        for(int j =0; j<SIZE; j++)
        {
            if(matrix[i][j]== INF)
            {
                cout<<"INF";
            }
            else
            {
                cout<<matrix[i][j];
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

int reducematrix(int matrix[][SIZE], int reduced[][SIZE])
{
    int reductioncost = 0;
    for(int i =0; i<SIZE; i++)
    {
        for(int j =0; j<SIZE; j++)
        {
            reduced[i][j] = matrix[i][j];
        }
    }
    //row reduction
    for(int i =0; i<SIZE; i++)
    {
        int rowMin = INF;
        for(int j =0; j<SIZE; j++)
        {
            rowMin = min(rowMin, reduced[i][j]);
        }
        if(rowMin != INF && rowMin > 0)
        {
            reductioncost+= rowMin;
            for(int j =0; j <SIZE; j++)
            {
                if(reduced[i][j]!= INF)
                {
                    reduced[i][j]-= rowMin;
                }
            }
        }
    }
    //col reduction
    for(int j =0; j<SIZE; j++)
    {
        int colMin = INF;
        for(int i =0; i< SIZE; i++)
        {
            colMin = min(colMin, reduced[i][j]);
        }
        if(colMin != INF && colMin >0)
        {
            reductioncost+= colMin;
            for(int i =0; i<SIZE; i++)
            {
                if(reduced[i][j]!= INF)
                {
                    reduced[i][j]-= colMin;
                }
            }
        }
    }
    return reductioncost;
}

void BranchAndBound(int level, int currentcity, int costsofar, vector<int>&path, vector<bool>visited, int reduced[][SIZE], int matrix[][SIZE], int &mincost, vector<int>& bestpath)
{
    if(level == SIZE)
    {
        int totalcost = costsofar + matrix[currentcity][0];
        if(totalcost < mincost)
        {
            mincost = totalcost;
            bestpath = path;
        }
    }

    for(int next = 0; next<SIZE; next++)
    {
        if(!visited[next] && matrix[currentcity][next]!= INF)
        {
            int temp[SIZE][SIZE];
            for(int i =0; i<SIZE; i++)
            {
                for(int j =0; j<SIZE; j++)
                {
                    temp[i][j] = reduced[i][j];
                }
            }
            int newcost = costsofar + matrix[currentcity][next];
            for(int k =0; k<SIZE; k++)
            {
                temp[currentcity][k] =INF;
                temp[k][next]= INF;
            }
            temp[next][0] = INF;
            int reducedcopy[SIZE][SIZE];
            int reduction = reducematrix(temp, reducedcopy);
            int bound = newcost + reduction;

            if(bound< mincost)
            {
                visited[next] = true;
                path.push_back(next);
                BranchAndBound(level+1, next, newcost, path, visited, reducedcopy, matrix, mincost, bestpath);
                path.pop_back();
                visited[next] = false;

            }
        }
    }
}

int main()
{
    int matrix[SIZE][SIZE];
    cout<<"Enter the matrix\n";
    for(int i =0; i<SIZE; i++)
    {
        for(int j =0; j<SIZE; j++)
        {
            int val;
            cin>>val;
            matrix[i][j]= (val==-1)? INF: val;
        }
    }
    cout<<"Original matrix:\n";
    printmatrix(matrix);
    int reduced[SIZE][SIZE];
    int initialbound = reducematrix(matrix, reduced);
    cout<<"Reduced matrix :\n";
    printmatrix(reduced);
    cout<<"Initial bound"<<initialbound<<endl;

    vector<int>path, bestpath;
    vector<bool>visited(SIZE, false);
    int mincost = INF;
    path.push_back(0);
    visited[0]= true;
    BranchAndBound(1, 0, 0, path, visited, reduced, matrix, mincost, bestpath);
    cout<<"Optimal path is:";
    for(int i =0; i<bestpath.size(); i++)
    {
        cout<<bestpath[i]+1<<" ->";
    
    }
    cout<<"mincost :"<<mincost<<endl;
    return 0;
}