#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define pii pair<int, int>

using namespace std;

int N;
string strategy;
set<pii> leaked_memory, free_memory;
map<string, pii> allocated_memory;

pii getFirstFit(int size)
{
	for(auto ii : free_memory)
	{
		if(ii.second-ii.first+1 >= size)
			return ii;
	}
	return mp(-1,-1);
}

pii getBestFit(int size)
{
	int curmin = INT_MAX;
	pii retpair = mp(-1,-1);

	for(auto ii : free_memory)
	{
		if((ii.second-ii.first+1 >= size) && (ii.second-ii.first+1 < curmin))
		{
			curmin = ii.second-ii.first+1;
			retpair = ii;
		}
	}
	return retpair;
}

pii getWorstFit(int size)
{
	int curmax = INT_MIN;
	pii retpair = mp(-1,-1);

	for(auto ii : free_memory)
	{
		if((ii.second-ii.first+1 >= size) && (ii.second-ii.first+1 > curmax))
		{
			curmax = ii.second-ii.first+1;
			retpair = ii;
		}
	}
	return retpair;
}

void myMalloc(string pointer, int size)
{
	pii allotted_block;
	if(strategy == "first-fit")
		allotted_block = getFirstFit(size);
	else if(strategy == "best-fit")
		allotted_block = getBestFit(size);
	else if(strategy == "worst-fit")
		allotted_block = getWorstFit(size);

	if(allotted_block == mp(-1,-1))
	{
		cout<<"out-of-memory error\n"; // what if pointer is already allocated in this case?
		if(allocated_memory.find(pointer) != allocated_memory.end()) // you can insert even if it is mp(-1,-1) ... no issues
			leaked_memory.insert(allocated_memory[pointer]);
		allocated_memory.erase(pointer);
	}
	else
	{
		if(allocated_memory.find(pointer) != allocated_memory.end()) // you can insert even if it is mp(-1,-1) ... no issues
			leaked_memory.insert(allocated_memory[pointer]);

		free_memory.erase(allotted_block);
		if(allotted_block.second - allotted_block.first+1 > size)
			free_memory.insert(mp(allotted_block.first+size, allotted_block.second));

		allocated_memory[pointer] = mp(allotted_block.first, allotted_block.first + size - 1);
		cout<<"success\n";
	}
}

void myFree(string pointer)
{
	if(allocated_memory.find(pointer) == allocated_memory.end())
		cout<<"invalid-pointer error\n";
	else if(allocated_memory[pointer] == mp(-1,-1))
		cout<<"double-free error\n";
	else
	{
		free_memory.insert(allocated_memory[pointer]);
		allocated_memory[pointer] = mp(-1,-1);
		cout<<"success\n";
	}
}

int main()
{
	cin>>N;
	cin>>strategy;

	free_memory.insert(mp(0,N-1));
	leaked_memory.insert(mp(-1,-1)); // in case you later add it, so u add it before itself

	string command, pointer;
	int size;
	while(cin>>command)
	{
		if(command == "malloc")
		{
			cin>>pointer;
			cin>>size;
			myMalloc(pointer, size);
		}
		else if(command == "free")
		{
			cin>>pointer;
			myFree(pointer);
		}
		else if(command == "exit")
			break;
	}

	for(auto mm : allocated_memory)
		leaked_memory.insert(mm.second);

	cout<<"\nleaked-memory\n";
	for(auto ii : leaked_memory)
	{
		if(ii.first != -1)
			cout<<ii.first<<" "<<ii.second<<endl;
	}
	return 0;
}