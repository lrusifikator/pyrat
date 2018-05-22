#ifndef _HANDLER_
#define _HANDLER_

#include "db.hpp"

class handler{
	private:
		bool run, rm, add, vdb, backup, show, n, k,cat;
		vector<string> number, topics, arguments;
		database db;
		string work_dir;
		
	public:
		handler(int argc, char **argv);
		handler(int argc, char **argv, string dir);
		int remove_backup();
		int remove_backup(vector<string>);
		vector<string> strar_to_vec(int argc, char **argv);
		int asum();
		int nsum();
		int exec(vector<string> args);
		int args_handler();
		int args_handler(vector<string> arg);
};

#endif
