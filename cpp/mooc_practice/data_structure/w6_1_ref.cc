#include <iostream>
#include <queue>

using namespace std;

void num_sort(int weight[],int group)
{
    int t;
    for(int i=0;i<group;i++)
    {
        for(int j=0;j<group-i-1;j++)
        {
            if(weight[j]<weight[j+1])
            {
                t=weight[j];
                weight[j]=weight[j+1];
                weight[j+1]=t;
            }
        }
    }
}

int num_count(int weight[],int group)
{
    if(group==1)
        return 0;
    else
    {
        num_sort(weight,group);
        weight[group-2]=weight[group-1]+weight[group-2];
        return weight[group-2]+num_count(weight,group-1);
    }
}

int main()
{
    int num,group;
    cin >>num;
    while(num--)
    {
        int i;
        cin >>group;
        int weight[group];
        for(i=0;i<group;i++)
        {
            cin >>weight[i];
        }
        cout <<num_count(weight,group) <<endl;
    }
    return 0;
}
