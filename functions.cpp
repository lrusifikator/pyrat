#include "functions.hpp"

string file_to_string(string path, int from, int limit){
	string res;
	string str;
	int i;
	
	if(!fexist(path.c_str())){
		ofstream outfile(path.c_str());
		outfile.close();
		ifstream myfile(path.c_str());
		if(!myfile.is_open()){
			cout << "can't create a file named : " << path << endl;
			exit(1);
		}
		myfile.close();
		return "";
	}
	
	i=0;

	ifstream file(path.c_str());
	while(getline(file, str) && i!=limit){
		if(i>=from){
			res += str;
			i++;
		}
	}
	
	file.close();
	return res;
}

string file_to_string(string path){
	return file_to_string(path, 0, -1);
}

string file_to_string(string path, int from){
	return file_to_string(path, from, -1);
}

void errorp(string str){
	cout << str << endl;
	exit(1);
}

vector<int> vec_to_int(vector<string> vec){
	vector<int> ret;
	int error;
	for(vector<string>::iterator it = vec.begin(); 
					it!= vec.end(); it++){
		ret.push_back(stoi(*it, error));
		if(error)
			errorp("error : argument is not a number");
	}
	return ret;
}

void move(string from, string to){
	string com = string("mv ") + from + " " + to;
	system(com.c_str());
}

long long int pow(int num, int n){
	long long int res=1;
	if(!n)
		return 1;
	
	for(int i=0; i<n; i++){
		res *= num;
	}
	return res;
}
	
long long int stoi(string str, int &er){
	long long int ret=0;
	er=0;
	for(unsigned int i=0, j=str.size()-1; i !=str.size() ; i++, j--){
		if(!isdigit(str[i])){
			er=1;
			break;
		}
		ret += (str[i]-'0') * pow(10, j) ; 
	}
	return ret;
}

long long int stoi(string str){
	int er;
	return stoi(str, er);
}

void addvec(vector<string> &in, vector<string> from){
	for(vector<string>::iterator it = from.begin();	
					it != from.end(); it++){
		in.push_back(*it);
	}	
}

int write_vec(string file, vector<string> vec){
	for(vector<string>::iterator it = vec.begin(); 
			it!=vec.end(); it++)
		write_string(file, *it);
	return 0;
}

void print_vec(vector<string> vec){
	for(vector<string>::iterator it = vec.begin(); it != vec.end(); it++)
		cout << it - vec.begin() + 1 << ") "<< *it << endl;
}


string substr(string str, int i, int pos){
	string res;
	
	for(; i<pos; i++){
		res += str[i];
	}
	
	return res;
}

int cutstr(string str, string &res, int i, char c){
	int pos;
	static bool mark=0;
	if(mark)
		return (mark=0);
	
	pos = str.find(c, i);
	if(pos<=i){
		pos = str.find("\n", i);
		if(pos<=i){
			pos = str.length();
			mark=1;
		}
	}
	
	res = substr(str, i, pos);
	return pos+1;
}

int cutstr(string str, string &res, int i, string c){
	return cutstr(str, res, i, c[0]);
}

int cutstr(string str, string &res, int i){
	return cutstr(str, res, i, ' ');
}

int cutstr(string str, string &res){
	return cutstr(str, res, 0);
}

vector<string> getdir (string dir)
{
    DIR *dp;
    vector<string> files;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error" << " opening " << dir << endl;
        return vector<string>();
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return files;
}

int compare(string s1, vector<string> arr){
	for(vector<string>::iterator it = arr.begin(); it != arr.end(); it++){
		if(*it == s1)
			return -1;
	}
	return 0;
}


void clean_file(string path){
	string com = string("echo '' > ") + path;
	system(com.c_str());
}

int write_string(string path, string str){
	if(!fexist(path.c_str())){
		ofstream outfile(path.c_str());
		outfile.close();
		ifstream myfile(path.c_str());
		if(!myfile.is_open()){
			cout << "can't create a file named : " << path << endl;
			exit(1);
		}
		myfile.close();
	}
	string com = string("echo \"") + str + string("\" >> ") + path;
	system(com.c_str());
	return 0;
}


bool fexist(const char *filename){
  ifstream ifile(filename);
  return ifile;
}


int find_last(string str, char c){
	int res=0;
	if(str[str.size()-1]==c){
		str = substr(str, 0, str.size()-1);
	}
	
	for(int i=0; (i=str.find(c, i)) !=  string::npos; i++){
		res = i;
	}
	return res;
}


vector<string> file_to_vector(string path, int from, int limit){
	vector<string> res;
	string str;
	int i;
	
	if(!fexist(path.c_str())){
		ofstream outfile(path.c_str());
		outfile.close();
		ifstream myfile(path.c_str());
		if(!myfile.is_open()){
			cout << "can't create a file named : " << path << endl;
			exit(1);
		}
		myfile.close();
		return vector<string>();
	}
	
	i=0;

	ifstream file(path.c_str());
	while(getline(file, str) && i!=limit){
		if(i>=from){
			res.push_back(str);
			i++;
		}
	}
	
	file.close();
	return res;
}

int count_symb(string str, char c){
	int i=0, count = 0;
	while(i < str.size()){
		if(str[i]==c)
			count++;
		i++;
	}
	return count;
}

vector<string> file_to_vector(string path){
	return file_to_vector(path, 0, -1);
}

vector<string> file_to_vector(string path, int from){
	return file_to_vector(path, from, -1);
}


int create_dir(string path){
	struct stat info;
		
	if(stat( path.c_str(), &info )){
		if(mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH )){
			cout << "can't create a foler named : " << path << endl;
			exit(1);
		}
	}
	return 0;
}


int writer(char *data, size_t size, size_t nmemb, string *buffer){
	int result = 0;
	if(buffer != NULL){
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}
