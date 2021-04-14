#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n,m;
	cout<<"Give the number of nodes\n";
	cin>>n;
	cout<<"Give the number of edges\n";
	cin>>m;
	cout<<"Give the directed edges(\"from\" to \"to\")\n";
	set<int> pred[n+1];
	for(int i = 0;i<m;i++)
	{
		int u,v;
		cin>>u>>v;
		pred[v].insert(u);
	}
	set<int> deno[n+1];
	deno[1].insert(1);
	for(int i = 2;i<=n;i++)
	{
		deno[i].insert(i);
		if(pred[i].size() > 0)
		{
			int cmp = *(pred[i].begin());
			cout<<"Comparing for "<<i<<" --> "<<cmp<<endl;
			for(int j : deno[cmp])
			{
				int sz = 0;
				for(int k: pred[i])
				{
					if(deno[k].size() == 0)
					{
						sz++;	
					}
					else if(deno[k].find(j) != deno[k].end())
					{
						sz++;
					}
				}
				cout<<"For "<<i<<" and "<<j<<" --> "<<sz<<" pred --> "<<pred[i].size()<<endl;
				if(sz == pred[i].size())
				{
					deno[i].insert(j);
				}
			}
		}
	}
	for(int i = 1;i<=n;i++)
	{
		cout<<"D("<<i<<") -- > ";
		for(auto j : deno[i])
		{
			cout<<j<<" ";
		}
		cout<<endl;
	}
}