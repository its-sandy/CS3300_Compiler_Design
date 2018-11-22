#include <bits/stdc++.h>
#define pb push_back
#define mt make_tuple
#define mp make_pair
#define tici tuple<int, int, int> // start, var, end
using namespace std;

vector<tici> liveRanges;
bool colives[26][26];
int n, numReg, numSpill, numVar;
pair<int, int> regStatus[30]; // var, end

set<vector<bool>> s1;
set<vector<bool>> s2;

void prepareLiveRanges()
{
	n = liveRanges.size();
	map<int, int> dict;
	int i,x,counter=0;

	for(auto tups : liveRanges)
	{
		x = get<1>(tups);
		if(dict.find(x) == dict.end())
		{
			dict[x] = counter;
			counter++;
		}
	}
	numVar = counter;

	for(i=0; i<n; i++)
		get<1>(liveRanges[i]) = dict[get<1>(liveRanges[i])];

	sort(liveRanges.begin(), liveRanges.end());
}

int getMaxClique()
{
	int i,j,k,x,bitPattern, maxSize;

	maxSize = 1;
	x = 1<<numVar;
	int subset[26];

	for(bitPattern=1; bitPattern<x; bitPattern++)
	{
		bitset<32> clique(bitPattern);
		
		k = 0;
		for(i=0; i<26; i++)
			if(clique[i] == 1)
				subset[k++] = i;

		for(i=0; i<k; i++)
			for(j=i+1; j<k; j++)
				if(!colives[subset[i]][subset[j]])
				{
					k = 0;
					break;
				}

		maxSize = max(k, maxSize);
	}
	return maxSize;
}

int main()
{
	int start, end, i,j;
	char var;
	bool done;

	while(cin>>var)
	{
		cin>>start>>end;
		liveRanges.pb(mt(start, var-97, end));
	}
	prepareLiveRanges();

	for(i=0; i<n; i++)
		for(j=i+1; j<n; j++)
			if((get<2>(liveRanges[i])) >= (get<0>(liveRanges[j])))
			{
				colives[get<1>(liveRanges[i])][get<1>(liveRanges[j])] = true;
				colives[get<1>(liveRanges[j])][get<1>(liveRanges[i])] = true;
			}

	numReg = getMaxClique();
	numSpill = 0;

	for(i=0; i<30; i++)
		regStatus[i] = mp(-1,-1);

	for(i=0; i<n; i++)
	{
		done = false;

		// if variable is already loaded
		for(j=0; !done && j<numReg; j++)
			if(regStatus[j].first == (get<1>(liveRanges[i])))
			{
				done = true;
				regStatus[j] = mp(get<1>(liveRanges[i]), get<2>(liveRanges[i]));
			}

		// if unused register
		for(j=0; !done && j<numReg; j++)
			if(regStatus[j].first == -1)
			{
				done = true;
				regStatus[j] = mp(get<1>(liveRanges[i]), get<2>(liveRanges[i]));
			}

		// if non-colive
		for(j=0; !done && j<numReg; j++)
			if(colives[regStatus[j].first][get<1>(liveRanges[i])] == false)
			{
				done = true;
				regStatus[j] = mp(get<1>(liveRanges[i]), get<2>(liveRanges[i]));
				numSpill++;
			}

		// if colive but replaced variable not live
		for(j=0; !done && j<numReg; j++)
			if(regStatus[j].second < (get<0>(liveRanges[i])))
			{
				done = true;
				regStatus[j] = mp(get<1>(liveRanges[i]), get<2>(liveRanges[i]));
				numSpill++;
			}
	}
	cout<<numReg<<" "<<numSpill<<endl; 
}