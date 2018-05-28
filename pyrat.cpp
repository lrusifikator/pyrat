#include "functions.hpp"
#include "pyrat.hpp"
#include "slist.hpp"

int pyrat::set(string ppath, string plink){
	name = "";
	tags = "";
	desc = "";
	
	link = plink;
	page = get_page(plink);
	path = ppath;
	video_path = ppath + "video";
	
	vdesc = get_vdesc();
	name = get_name();
	tags = get_tags();
	desc = get_description();
	
}

string pyrat::get_vdesc(string link){
	string path = work_directory + "desc";
    string com = string("youtube-dl -j \"") + link + string("\" > ") + path;
	string pg;
	system(com.c_str());
    pg = decip(file_to_string(path));
    return pg;
}

string pyrat::get_vdesc(){
    return get_vdesc(link);
}

string pyrat::decip(string str){
	string ret;
	unsigned int i=0, pos=0;
	
	while((i=str.find("\\n", pos)) != string::npos){
		if(i+1<=pos){
			break;
		}
		ret+=substr(str, pos, i - 1) + "\n";
		i+=2;
		pos=i;
	}
	
	ret += substr(str, pos, str.size()-1);
	return ret;
}


string pyrat::get_page(string url){
	string path = work_directory + "temp";
    string com = string("wget \"") + url + string("\" -O ") + path;
	string pg;
	system(com.c_str());
    pg = file_to_string(path);
    remove(path.c_str());
    return pg;
}

string pyrat::get_description(){
	if(!desc.empty()) 
		return desc;
		
	desc = get_description(link);
	return desc + string("\nOrginal video : ") + link;
}

string pyrat::get_tags(string link){ 
	return get_tags_page(get_page(link));
}

string pyrat::get_tags(){
	if(!tags.empty())
		return tags;
	return (tags = get_tags_page(page));
}

string pyrat::get_tags_page(string pg){
	unsigned long int pos;

	if((pos = pg.find("keyword", pg.find("keyword")+1)) == string::npos)
		return string("");

	pos+=11;
	return substr(pg, pos, pg.find("\"", pos));
}

string pyrat::get_name(){
	if(!name.empty())
		return name;
		
	unsigned int pos, i;	
	
	pos = vdesc.find("fulltitle");
	pos = vdesc.find("\"", pos) + 1;
	pos = vdesc.find("\"", pos) + 1;
	i = vdesc.find("\"", pos);
	
	return substr(vdesc, pos, i-1);
}

string pyrat::mainol(string str){
	int pos=0;
	int i=0;
	while(i<3){
		pos = str.find("<ol", pos) + 1;
		i++;
	}
	pos--;
	return substr(str, pos, str.find("</ol>", pos) + 5);
}

int pyrat::get_likes(string link){
	unsigned int pos;	
	string pg = get_vdesc(link);
	
	pos = pg.find("\"like_count\":") + 14;
	pg = substr(pg, pos, pg.find(", ", pos));
	return stoi(pg);
}


string pyrat::get_description(string l){
	unsigned int pos, i;
	string d = get_vdesc(l);
	pos = d.find("description");
	pos = d.find("\"", pos) + 1;
	pos = d.find("\"", pos) + 1;
	i = d.find("\"", pos);
	
	return substr(d, pos, i-1);
}

string pyrat::get_rvdesc(string link){
	rvdesc = get_vdesc(link);
	return rvdesc;
}

string pyrat::get_description_r(string link){
	unsigned int pos, i;
	if(rlink != link){
		rlink = link;
		get_rvdesc(link);
	}
	pos = rvdesc.find("description");
	pos = rvdesc.find("\"", pos) + 1;
	pos = rvdesc.find("\"", pos) + 1;
	i = rvdesc.find("\"", pos);
	
	return substr(rvdesc, pos, i-1);
}

int pyrat::get_likes_r(string link){
	if(rlink != link){
		rlink = link;
		get_rvdesc(link);
	}
	unsigned int pos;
	
	pos = rvdesc.find("\"like_count\":") + 14;
	rvdesc = substr(rvdesc, pos, rvdesc.find(", ", pos));
	return stoi(rvdesc);	
}

bool pyrat::check_catgory(string l, string cat){
	if(cat.empty() || cat == " ")
		return 1;
	string pg = get_vdesc(l);
	int pos = pg.find("\"categories\": ") + 16;
	if(cat == substr(pg, pos, pg.find("]", pos)-1))
		return 1;
	return 0;
}

bool pyrat::lang_test(string l){
	string lang = string("ldetect \"") + get_description_r(l) + string("\"");
	if(!system(lang.c_str()))
		return 0;
	return 1;
}

slist pyrat::top_search_videos(string search_word, string cat){ 
	unsigned long int li=0, end=0, pos;
	string str;
	slist ret;
	string link;  		
	str = mainol(get_page( (str = string("https://www.youtube.com/results?search_query=") + temp(search_word, ' ', '+') + string("&sp=EgQIAhAB")) ));
		
	while(1){
		li = str.find("<li>", li);
		if(li == string::npos)
			break;
		
		end = str.find("</li>", li);
		pos = str.find("href=\"/watch?", li);
		 
		if(str.find("Live now", li) < end || pos > end){   //skip translations
			end = (li++);
			continue;
		}
		
		pos += 6;
		link = string("https://youtube.com") + substr(str, pos, str.find("\"", pos));
		
		if(check_catgory(link, cat) && (lang_test(link)))
			ret.add(link, get_likes_r(link));
		end = (li++);
	}
	
	return ret;	
}

vector<string> pyrat::search_videos(string search_word){
	unsigned long int li=0, end=0, pos;
	string str;
	vector<string> links;
	
	str = mainol(get_page( (str = string("https://www.youtube.com/results?search_query=") + temp(search_word, ' ', '+') + string("&sp=EgQIAhAB")) ));
		
	while(1){
		li = str.find("<li>", li);
		if(li == string::npos)
			break;
		
		end = str.find("</li>", li);
		pos = str.find("href=\"/watch?", li);
		 
		if(str.find("Live now", li) < end || pos > end){   //skip translations
			end = (li++);
			continue;
		}
		
		pos += 6;
		if(lang_test(link))
			links.push_back( string("https://youtube.com") + substr(str, pos, str.find("\"", pos)) );
		end = (li++);
	}
	
	return links;
}

int pyrat::download(){
	string command = string("youtube-dl ") + link + string(" -o ") + video_path;
	int ret = system(command.c_str()); 
	return ret;
}

int pyrat::upload(string category){
	if(!category.empty())
		category = string(" --category=\"") + category + string("\" ");
	else 
		category = " ";
		 
	string args = string("--title=\"") + get_name() + 
	string("\" --description=\"") + get_description() + string("\" --tags=\"") + 
	get_tags() + string("\" --client-secret=\"") + path + key + string("\"") + category + path + get_full_name(path, "video");
	string command = string("youtube-upload ") + args;
	
	cout << endl;
	cout << command << endl;
	cout << endl;
	
	return system(command.c_str());
}


int pyrat::remove_video(){
	string com = string("rm ") + path + string("video*");
	return !system(com.c_str());
}


string pyrat::temp(string str, char c, char on){
	string ret;
	for(unsigned int i=0; i < str.size(); i++){
		if(str[i]==c)
			ret+=on;
		else
			ret+=str[i];
	}
	return ret;
}

string pyrat::get_full_name(string path, string tmpl){
	vector<string> vec = getdir(path);
	string str;
	
	for(vector<string>::iterator it = vec.begin(); 
						it!= vec.end(); it++){
		str = *it;
		if(str.find(tmpl)!=string::npos)
			return str;
	}
	return string("");
}
