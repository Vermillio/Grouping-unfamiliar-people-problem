#pragma once

#include <vector>

using namespace std;



class SplitInTwoGroupsProblem
{

	private:
	
		typedef struct List
		{
			int key;
			List *next;

			List() : key(-1), next(nullptr) {};
			List(int x) : key(x), next(nullptr) {};
		};

		void push(List *&l, int key);
		bool CheckGroup(List *l, int l_key);
		
		vector<List*> contacts;
		int *groups;

	public:

		void Run();
		int *SplitInTwo(vector<List*> contact);

};