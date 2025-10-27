#include <iostream>
#include <vector>
using namespace std;

void merge(vector<float>&p, vector<float>& w, int left, int mid, int right)
{
    int n1 = mid - left +1;
    int n2 = right - mid;

    vector<float> Lp(n1), Lw(n1), Rp(n2), Rw(n2);

    for (int i =0; i< n1; i++){
        Lp[i] = p[left + i];
        Lw[i] = w[left + i];
    }
    for (int i =0; i<n2; i++){
        Rp[i] = p[mid + 1 + i];
        Rw[i] = w[mid + 1 + i];
    }

    int i =0, j =0, k = left;
    while (i < n1 && j < n2){
        if(Lp[i]/Lw[i] >= Rp[j]/Rw[j]){
            p[k] = Lp[i];
            w[k] = Lw[i];
            i++;
        }
        else
        {
            p[k] = Rp[j];
            w[k] = Rw[j];
            j++;
        }
        k++;
    }
    while ( i < n1)
    {
        p[k] = Lp[i];
        w[k] = Lw[i];
        i++; k++;
    }
    while( j < n2)
    {
        p[k]= Rp[j];
        w[k] = Rw[j];
        j++; k++;
    }
}

void mergesort(vector<float>&p, vector<float>& w, int left, int right)
{
    if(left <right)
    {
        int mid = (left + right)/2;
        mergesort(p, w, left, mid);
        mergesort(p , w, mid +1, right);
        merge(p, w, left, mid, right);

    }
}

int main()
{
    int m, n;
    cout<<"Enter the knapsack capacity:";
    cin>> m;
    cout<<"Enter the number of elements:";
    cin>> n;

    vector<float> p(n), w(n);
    for(int i =0; i< n; i++)
    {
        cout<<"Enter the weight and profit "<<i+1<<":";
        cin>>w[i]>>p[i];
    }

    mergesort(p, w, 0, n-1);
    vector<float> x(n, 0.0);
    int remaining = m;
    for(int i =0; i<n && remaining > 0; i++)
    {
        if(w[i] <= remaining)
        {
            x[i] = 1.0;
            remaining-= w[i];
        }
        else
        {
            x[i] = (float)remaining/ w[i];
            remaining = 0;
        }
    }
   float total_profit = 0;
   for(int i =0; i<n; i++)
   {
    total_profit += x[i] * p[i];
   }
   cout<<"items taken are:";
   for(float val:x)
   {
    cout<<val<<" ";
   }
   cout<<"Total_profit is :"<<total_profit<<endl;
   return 0;
}