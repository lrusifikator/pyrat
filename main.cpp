#include "functions.hpp"
#include "db.hpp"
#include "pyrat.hpp"
#include "handler.hpp"
#include "slist.hpp"

#define NOT_FOUND -1
#define ACCES_ERROR 1
//#define TEST

using namespace std;

string prog_name;
vector<string> topics;

bool yorn(){
	string a;
	cin >> a;
	if(a == "y" || a=="yes" || a=="Y" || a == "YES")
		return 1;
	return 0;
}

#ifndef TEST

int main(int argc, char **argv){
	database db;
	pyrat pr;
	string topic, dir;
	vector<string> backup;
	int video_number;
	string link;
	slist links;
	handler phandler(argc, argv);
	
	prog_name = string(argv[0]);
	
	if(argc>1)
		phandler.args_handler();
	
	
	create_dir(work_directory);
	
	if(topics.empty()){
		topics = db.get_topics();
		if(topics.empty())
			cout << "databse is empty" << endl;
	}else{
		topics = db.check_if_exist(topics);
	}
		
	for(vector<string>::iterator tp = topics.begin();
							tp != topics.end(); tp++){
		topic = *tp;
		dir = work_directory + topic + string("/");					
		create_dir(dir);
			
		backup = file_to_vector(dir + "backup");
		links = pr.top_search_videos(db.get_keyword(*tp), db.get_category(*tp));
		
		if(links.empty()){
			cout << endl;
			cout << "	videos on topic \"" << topic << "\" not found" << endl; 
			cout << endl;
			return 0;
		}
		
		links.show();	
		for(; links != links.end(); links++){
			link = links.get();	
			if(compare(link, backup))
				continue;
				
			pr.set(dir, link);
			
			if(pr.download()){
				cout << endl << "	warning : can't download video" << endl;
				cout << link << endl << endl;
				continue;	
			}
				
			if(pr.upload(db.get_category(*tp))){			
				cout << endl << "	warning : can't upload video" << endl;
				cout << link << endl << endl;
				cout << "do you want to continue ?(yes/no) ";
				if(yorn())
					continue;
				pr.remove_video();	
				break;
			}
			
			pr.remove_video();
			write_string( dir + "backup", link );
			break;	
		}
	}
	return 0;
}


#else

int main(){
	pyrat pr;
	cout << pr.check_catgory("https://www.youtube.com/watch?v=9P1c1Rvolb8", "News & Politics") << endl;
	return 0;
}
#endif
