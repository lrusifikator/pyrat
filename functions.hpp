#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <vector>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <dirent.h>

using namespace std;

const string home = getenv("HOME");
const string work_directory = home + string("/.pyrat/");

string file_to_string(string path, int from, int limit);
string file_to_string(string path, int from);
string file_to_string(string path);
int count_symb(string str, char c);
vector<int> vec_to_int(vector<string>);
void errorp(string);
void move(string from, string to);
long long int stoi(string str);	
long long int stoi(string str, int &er);
long long int pow(int num, int n);
int write_vec(string file, vector<string> vec);
void clean_file(string path);
void addvec(vector<string> &in, vector<string> from);
void print_vec(vector<string> vec);
bool fexist(const char *filename);
int writer(char *data, size_t size, size_t nmemb, string *buffer);
string temp(string str, char c, char on);
string del_mesc(string str);
vector<string> file_to_vector(string path);
vector<string> file_to_vector(string path, int from, int limit);
vector<string> file_to_vector(string path, int from);
string substr(string str, int i, int pos);
int cutstr(string str, string &res, int i, char c);
int cutstr(string str, string &res, int i, string c);
int cutstr(string str, string &res, int i);
int cutstr(string str, string &res);
vector<string> getdir (string dir);
int compare(string s1, vector<string> arr);
int theme_exist(string theme);
int create_dir(string path);
int write_string(string file, string str);
string get_full_name(string path, string tmpl);


#endif
