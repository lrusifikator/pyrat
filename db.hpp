#ifndef __DB__
#define __DB__

#include <stdlib.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>


using namespace std;


class database{
	private:
		vector<string> keyword;
		vector<string> topic;
		vector<string> category;		
		vector<string> categories;
		vector<string> file;
		string work_dir;
		int counter;
		int len;
		string path;
	
	public:		
	    void show_cat();
	    vector<string> del_topic(string t);
		vector<string> get_topics();
		int add_entry(string, string);
		int protect_initialize_db(string);
		database(string);
		database();
		int show(vector<string>);
		int show_num(vector<int>);
		vector<string> search_topic(string word);
		int remove_topic(vector<string>);
		int remove_topic_num(vector<int>);
		int check_topic(string t);
		int add_entry(vector<string>, string );
		void init_categories();
		database& operator++();
		database operator++(int);
		vector<string> check_if_exist(vector<string>);
		int corection(vector<string> &);
		int set_db(string);
		int er_check(vector<string>);
		string get_topic();
		string get_keyword();
		string get_keyword(string);
		string get_category();
		string get_category(string);
		int get_counter();
		int inc();
		int dec();
		int end();
		void print_all();
		bool operator != (int num);
		bool operator == (int num);
		database& operator--();
		database operator--(int);
};

#endif
