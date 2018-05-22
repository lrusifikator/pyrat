#include "functions.hpp"
#include "db.hpp"

#include <algorithm>
  
database::database(string dir){
	work_dir = dir;
	init_categories();
	counter=0;
	path = work_dir + string("database");
	protect_initialize_db(work_dir);
	file = file_to_vector(path);
}

database::database(){
	work_dir = work_directory;
	init_categories();
	counter=0;
	path = work_dir + string("database");
	protect_initialize_db(work_dir);
	file = file_to_vector(path);
	
}

int database::protect_initialize_db(string dir){
	int error;
	if((error = set_db(dir + "/database"))){
		
		if(error==-2){
			cout << "it's not a database" << endl;
			cout << "sample : " << endl;
			cout << "{                 - begin of the block" << endl;
			cout << "news              - name of the folder, where the information will be stored " << endl;
			cout << "news              - search word" << endl;
			cout << "News & Politics   - category of the video (It's not necessary). " << endl;
			cout << "}                 - end of the block" << endl;
			cout << endl;
			cout << "To see the available categories type ";
			cout << "in the terminal : \"" << "pyrat show " << " --categories\"" << endl;
			cout << "before the first symbol \"{\" you can write what you want" << endl;
			exit(1);
		}else if(error==-1){
			cout << "warning : database is empty" << endl;
			cout << "to add an entry type : \"" << "pyrat" << " add topic_search word_category\"" << endl;
			cout << "database file : " << dir << "database" << endl; 
			return 1;
		}else{ 
			cout << "line : " << error << endl;
			exit(1);
		}
	}
	return 0;
}

vector<string> database::get_topics(){
	return topic;
}

string database::get_keyword(string tp){
	for(vector<string>::iterator it = topic.begin();
					it != topic.end(); it++){
		if(*it==tp)
			return keyword[it-topic.begin()];
	}
	
	errorp(string("no topic names \"") + tp + string("\"found"));
}

string database::get_category(string tp){
	for(vector<string>::iterator it = topic.begin();
					it != topic.end(); it++){
		if(*it==tp)
			return category[it-topic.begin()];
	}
	
	errorp(string("no topic names \"") + tp + string("\"found"));
}


int database::add_entry(vector<string> vec, string path){
	for(vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
		add_entry(*it, path);	
	
	return 0;
}
	
int database::add_entry(string str, string path){
	int pos, i;
	string t, k, c;
	
	str = del_mesc(str);
	pos = count_symb(str, '_');
		
	if(pos > 2 || pos < 1){
		cout << "not right format" << endl;
		errorp("topic_search word_category");
	}	
	
	t = substr(str, 0, (pos=str.find("_")));
	if(check_topic(t)){
		errorp("topic already exist");
	}	
	
	
	pos+=1;
	if((i=str.find("_", pos)) == string::npos){
		k = substr(str, pos, str.size());
	}else{
		k = substr(str, pos, i);
		c = substr(str, str.find("_", pos)+1, str.size() );
		if(!compare(c, categories)){
			errorp(c + string(" : not right category"));
		}
	}
	
	write_string(path, "{");
	write_string(path, t);
	write_string(path, k);
	
	if(!c.empty()){
		write_string(path, c);
	}
	
	write_string(path, "}");
	return 0;
}


int database::check_topic(string t){
	vector<string> vec;
	
	vec = search_topic(t);
	if(vec.empty())	
		return 0;
	return 1;
}

vector<string> database::search_topic(string word){
	vector<string> args;
	
	for(vector<string>::iterator it = file.begin();
				it != file.end(); it++){				
					
		args = vector<string> ();
		while(1){
			if(it == file.end())
				return vector<string> ();
			if(*it == "{")
				break;
			it++;
		}
		
		while(1){
			args.push_back(*it);
			
			if(*it == "}")
				break;
			it++;
		}
			
		if(args[1] == word)
			return args;
			
	}
	return vector<string> ();
}


int database::remove_topic(vector<string> topics){
	for(vector<string>::iterator it = topics.begin();
					it != topics.end(); it++){
		file = del_topic(*it);
		system(string(string("rm -rf ") + string(work_dir + *it)).c_str());
	}
	
	remove(path.c_str());
	write_vec(path, file);
	return 0;
}

vector<string> database::del_topic(string t){
	vector<string> args;
	vector<string> out;
	
	if(!compare(t, topic)){
			cout << "warning topic \"" << t <<"\" don't exist" << endl;
			return file;
	}
	
	for(vector<string>::iterator it = file.begin();
				it != file.end(); it++){				
					
		args = vector<string> ();
		while(1){
			if(it == file.end())
				return vector<string> ();
			if(*it == "{")
				break;
			it++;
		}
		
		while(1){
			args.push_back(*it);
			
			if(*it == "}")
				break;
			it++;
		}
			
		if(args[1] != t)
			addvec(out, args);
			
	}
	return out;
}

int database::show(vector<string> topics){
	vector<string> vec;
	if(topics.empty())
		topics = topic;
	cout << "---------------------" << endl;
	for(vector<string>::iterator i = topics.begin();
					i != topics.end(); i++){
		
		vec = search_topic(*i);
		if(!vec.empty()){
			cout << "topic : " << vec[1] << endl;
			cout << "keyword : " << vec[2] << endl;
			if(vec[3]!="}")
				cout << "category : " << vec[3] << endl;
			cout << "---------------------" << endl;
		}else{
			cout << "warning : topic \"" << *i << "\"" << " not found" << endl;
		}
	}
		
	return 0;
}


int database::set_db(string path){
	string work_dir = path;
	vector<string> file = file_to_vector(path);
	vector<string> args;
	int error;
	int esc;
	vector<string>::iterator itt;
	vector<string>::iterator i;
	
	if(file.empty()){
		return -1;
	}
	
	if((esc = corection(file))==-1)
		return -2;

	for(vector<string>::iterator it = file.begin();
				it != file.end(); it++){
		itt=it;
		args = vector<string> ();
		while(1){
				args.push_back(*it);
				if(*it == "}")
					break;
				it++;
		}
		
		if((error = er_check(args)))
			return itt - file.begin() + error + esc;
		
		topic.push_back(args[1]); 
		keyword.push_back(args[2]);
		if(args[3]=="}")
			args[3]="";
		if(!compare(args[3], categories))
			return itt - file.begin() + 4;
			
		category.push_back(args[3]); 
		len++;
	}
	return 0;
}

vector<string> database::check_if_exist(vector<string> test){
	vector<string> ret; 
	for(vector<string>::iterator it = test.begin(); 
						it != test.end(); it++){
		if(compare(*it, topic))
			ret.push_back(*it);
		else{
			cout << "warning topic \"" << *it << "\" dont exist" << endl;
		}
	}
	return ret;
}

void database::print_all(){
	cout << "	*topics*" << endl;
	print_vec(topic);
	cout << "	*keyword*" << endl;
	print_vec(keyword);
	cout << "	*category*" << endl;
	print_vec(category);
}

void database::show_cat(){
	print_vec(categories);
}

void database::init_categories(){
    categories.push_back("Film & Animation");
    categories.push_back("Autos & Vehicles");
    categories.push_back("Music");
    categories.push_back("Pets & Animals");
    categories.push_back("Sports");
    categories.push_back("Short Movies");
    categories.push_back("Travel & Events");
    categories.push_back("Gaming");
    categories.push_back("Videoblogging");
    categories.push_back("People & Blogs");
    categories.push_back("Comedy");
    categories.push_back("Entertainment");
    categories.push_back("News & Politics");
    categories.push_back("Howto & Style");
    categories.push_back("Education");
    categories.push_back("Science & Technology");
    categories.push_back("Nonprofits & Activism");
    categories.push_back("Movies");
    categories.push_back("Anime/Animation");
    categories.push_back("Action/Adventure");
    categories.push_back("Classics");
    categories.push_back("Comedy");
    categories.push_back("Documentary");
    categories.push_back("Drama");
    categories.push_back("Family");
    categories.push_back("Foreign");
    categories.push_back("Horror");
    categories.push_back("Sci-Fi/Fantasy");
    categories.push_back("Thriller");
    categories.push_back("Shorts");
    categories.push_back("Shows");
    categories.push_back("Trailers");
}

bool database::operator == (int num){
	if(counter == num)
		return 1;
	return 0;
}

bool database::operator != (int num){
	if(*this == num)
		return 0;
	return 1;
}

database& database::operator++(){  
   counter++;  
   return *this;  
}  

database database::operator++(int){  
   database temp = *this;  
   ++*this;  
   return temp;  
}  

database& database::operator--(){  
   counter--;  
   return *this;  
}  

database database::operator--(int){  
   database temp = *this;  
   --*this;  
   return temp;  
}

string database::get_keyword(){
	return keyword[counter];
}

string database::get_category(){
	return category[counter];
}

int database::er_check(vector<string> args){
	if(args[0]!="{")
		return 1;
	if(args[1].empty())
		return 2;
	if(args[2].empty())
		return 3;
	if(args[3]!="}"){
		if(args[3].empty())
			return 4;
		if(args[4]!="}")
			return 5;
	}
	return 0;
	
}

int database::corection(vector<string> &str){  
	vector<string> ret;
	string s;
	vector<string>::iterator it = str.begin();
	int esc;
	
	for(; it != str.end(); it++){
		if(*it=="{")
			break;
	}
	esc = it - str.begin();
	if(it == str.end())
		return -1;
	
	for(; it != str.end(); it++){
		
		s = del_mesc(*it);
		if(s.empty())
			continue;
		ret.push_back(s);
	}
	str = ret;
	
	return esc;
}

string database::get_topic(){
	return topic[counter];
}

int database::get_counter(){
	return counter;
}

int database::inc(){
	return (counter++);
}

int database::dec(){
	return (counter--);
}

int database::end(){
	return len;
}



string del_mesc(string str){
	string ret;
	bool count=0;
	char c;
	unsigned int i=0;
	unsigned int j=str.size();
	
	for(; i < str.size(); i++)
		if(!(str[i]=='\n' || str[i]=='\t' || str[i]==' '))
			break;
			
	for(; j >= 0; j--)
		if(!(str[i]=='\n' || str[i]=='\t' || str[i]==' '))
			break;
				
	for(; i < j; i++){
		if(str[i]=='\n' || str[i]=='\t')
			c=' ';
		else
			c=str[i];
			
		if(c==' ')
			if(count)
				continue;
			else 
				count=1;
		else 
			count = 0;
		
		ret+=str[i];
	}
	return ret;
} 
