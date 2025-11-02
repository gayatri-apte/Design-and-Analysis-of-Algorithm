#include "bits/stdc++.h"
using namespace std;

struct Pair
{
    int profit;
    int weight;
    Pair(int p , int w) : profit(p), weight(w) {}
};

vector<Pair>mergePurge(vector<Pair>&A,vector<Pair>&B, int m)
{
    vector<Pair>merged;
    int i = 0, j= 0;
    while(i< (int)A.size() && j < (int)B.size())
    {
        if(A[i].weight < B[j].weight)
        {
            merged.push_back(A[i++]);
        }
        else if(A[i].weight > B[j].weight)
        {
            merged.push_back(B[j++]);
        }
        else
        {
            merged.push_back((A[i].profit > B[j].profit)? A[i++]: B[j++]);
        }
    }
    while(i < (int)A.size()) merged.push_back(A[i++]);
    while(j < (int)B.size()) merged.push_back(B[j++]);

    //purge dominated pairs
    vector<Pair> purged;
    int bestprofit = -1;
    for(auto p :merged)
    {
        if(p.weight <=m && p.profit > bestprofit)
        {
            purged.push_back(p);
            bestprofit = p.profit;
        }
    }
    return purged;
}

void Dp(vector<int> &p, vector<int> &w, int n, int m)
{
    vector<vector<Pair>> s(n + 1);
    //Initialize
    s[0].push_back(Pair(0, 0));
    for(int i =1; i<=n; i++)
    {
        vector<Pair> temp;
        for(auto &prev : s[i-1])
        {
            temp.push_back(prev);
            int new_profit = prev.profit + p[i-1];
            int new_weight = prev.weight + w[i-1];
            if(new_weight <= m)
            {
                temp.push_back(Pair(new_profit, new_weight));
            }
        }
        s[i] = mergePurge(s[i-1], temp, m);
    }
    auto best = s[n].back();
    cout <<"Max profit:"<<best.profit<<endl;
    cout<<"weight ="<<best.weight<<endl;
}

int main()
{
    int n, m;
    cout<<"Enter the no.of items:";
    cin>>n;
    cout<<"Enter the knapsack capacity:";
    cin>>m;
    vector<int> profit(n), weight(n);
    cout<<"Enter the profits:";
    for(int i =0; i<n; i++) cin>>profit[i];
    cout<<"Enter the weights:";
    for(int i =0; i<n; i++) cin>>weight[i];
    Dp(profit, weight, n, m);
    return 0;

}