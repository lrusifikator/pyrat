#include "handler.hpp"
#include "functions.hpp"

extern string prog_name;
extern vector<string> topics;

int handler::remove_backup(){
	string file;
	string com;
	while(db != db.end()){
		file = work_dir + db.get_topic() + string("/backup");
		clean_file(file);
		system(com.c_str());
		db++;
	}
	return 0;
}

int handler::remove_backup(vector<string> topics){
	string file;
	string com;
	for(vector<string>::iterator it = topics.begin();
					it != topics.end(); it++){
		file = work_dir + *it + string("/backup");
		clean_file(file);
		system(com.c_str());
	}
	return 0;
}

handler::handler(int argc, char **argv){
	arguments = strar_to_vec(argc, argv);
	work_dir = work_directory;
	run = rm = add = vdb = show = n = k = cat = backup = 0;
}

handler::handler(int argc, char **argv, string dir){
	arguments = strar_to_vec(argc, argv);
	work_dir = dir;
	run = rm = add = vdb = show = k = backup = cat = 0;
}

vector<string> handler::strar_to_vec(int argc, char **argv){
	vector<string> ret;
	
	for(int i=1; i!=argc; i++)
		ret.push_back(string(argv[i]));
	return ret;
}

int handler::asum(){
	static int ret = run + rm + add + show + vdb;
	return ret;
}

int handler::nsum(){
	static int ret = k + backup + cat;
	return ret;
}

int handler::exec(vector<string> args){
	string com;
	
	if(asum()>1 )
		errorp(prog_name + string(" :  can not execute more then one command"));
	
	if(!asum()){
		errorp(prog_name + string( " : no command found"));	
	}
	
	if(vdb == 1){	
		if(nsum()==0  && args.empty()){
			com = string("nano ") + work_dir + string("database");
			system(com.c_str());
			
		}else
			errorp(prog_name + string(" :  not right arguments"));
		
		exit(0);
	}else if(rm){
		if(nsum() == 0){
			if(args.empty())
				errorp(prog_name + string(" :  nothing to remove found"));
			db.remove_topic(args);
			
		}else if(nsum() == 1){
			if(backup){
				if(!args.empty())
					remove_backup(args);
				remove_backup();
				
			}else if(args.empty())
				errorp(prog_name + string(" :  not right arguments"));
			
		}else
			errorp(prog_name + string(" :  not right arguments"));
		exit(0);
	}else if(add){
		
		if(args.empty())
				errorp(prog_name + string(" : nothing to add"));
		
		if(!nsum()){
			db.add_entry(args, work_dir + string("database"));
		}else if(nsum() == 1){
			if(k){
				if(args.size() == 2){
					move(args[0], work_dir + args[1] + string("/key.json"));
				}else{
					errorp(prog_name + string(" : too many arguments"));
				}
			}
		}else
			errorp(prog_name + string(" : too many arguments"));
		
		exit(0);
	}else if(show){
		if(nsum()>1)
			errorp(prog_name + string(" : too many arguments"));
		if(cat){
			if(!args.empty())
				errorp(prog_name + string(" : too many arguments"));
			db.show_cat();
		}else
			db.show(args);
		exit(0);
	}else if(run){
		if(args.empty())
			errorp(prog_name + string(" : nothing to run"));
			
		if(nsum()!=0)
			errorp(prog_name + string(" : too many arguments"));
		
		topics = args;
	}else{
		exit(0);
	}
}



int handler::args_handler(vector<string> arg){
	vector<string> args;
	
	for(vector<string>::iterator it = arg.begin(); 
						it!=arg.end(); it++){
		if(*it == "key"){
			k = 1;
		}else if(*it == "database" || *it == "db"){
			vdb=1;
		}else if(*it == "rm"){
			rm = 1;
		}else if(*it == "add"){
			add = 1;
		}else if(*it == "show"){
			show = 1;
		}else if(*it == "run"){
			run = 1;
		}else if(*it == "backup"){
			backup=1;
		}else if(*it == "--categories" || *it == "-cat"){
			cat = 1;
		}else
			args.push_back(*it);
	}

	exec(args);
	return 0;
}

int handler::args_handler(){
	return args_handler(arguments);
}

