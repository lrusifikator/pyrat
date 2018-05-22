#ifndef _SLIST_
#define _SLIST_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class slist{
	private:
		vector<string> str;
		vector<int> num;
		bool indicator;
		int counter;
		int limit;
	public:
		
		slist();
		void show();
		slist operator--(int);
		slist &operator--();
		void sort();
		void add(string, int);
		void add(int, string);
		string get_s();
		string get_s(int);
		int get_n(int);
		int get_n();
		int get_counter();
		int end();
		string get();
		string get(int);
		int get(string);
		string search(int);
		int search(string);
		bool operator == (int num);
		bool operator != (int num);
		slist& operator++();
		slist operator++(int);
		bool empty();
};

#endif
