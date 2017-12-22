//There are N people and a rectangular table A [1: N, 1: N], 
//the element A [i, j] is 1 if the person i is familiar with the person j, A [i, j] = A [j, i]. 
//Can people be divided into 2 groups, so that in each group there are only strangers.

#include "SplitInTwoGroupsProblem.h"
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

void SplitInTwoGroupsProblem::Run()
{
	cout << "Enter pairs of familiar people (numeration from 0): " << endl;
	int a, b;
	int N = 0;
	vector<List*> input;
	while (cin >> a && cin >> b)
	{
		input.resize(max((int)input.size(), max(a, b) + 1));
		push(input[a], b);
		push(input[b], a);
		cin.clear();
	}

	int *output = SplitInTwo(input);

	if (!output)
		cout << "Cannot be divided." << endl;
	else
	{
		cout << "Can be divided. Example: " << endl;
		for (int i = 0; i < input.size(); i++)
			cout << i << "   " << output[i] + 1 << " group" << endl;
	}
}

void SplitInTwoGroupsProblem::push(List *&l, int key)
{
	if (!l)
		l = new List(key);
	List *p = l;
	while (p->next)
		p = p->next;
	p->next = new List(key);
}

bool SplitInTwoGroupsProblem::CheckGroup(List * l, int l_key)
{
	if (!l)
	{
		groups[l_key] = 1;
		return 1;
	}
	if (groups[l_key] == -1)
		groups[l_key] = 1;
	
	List *p = l;
	while (p)
	{
		if (groups[p->key] == -1)
		{
			groups[p->key] = 1 - groups[l_key];
			if (!CheckGroup(contacts[p->key], p->key))
				return 0;
		}
		else if (groups[p->key] == groups[l_key])
			return 0;
		p = p->next;
	}
	return 1;
}

int *SplitInTwoGroupsProblem::SplitInTwo(vector<List*> contacts_graph)
{
	contacts = contacts_graph;
	if (contacts.size() == 0)
		return nullptr;
	groups = new int[contacts.size()];
	for (int i = 0; i < contacts.size(); i++)
		groups[i] = -1;
	for (int i = 0; i < contacts.size(); i++)
	{
		if (groups[i] != -1)
			continue;
		if (!CheckGroup(contacts[i], i))
			return nullptr;
	}
	return groups;
}

