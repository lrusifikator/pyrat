#include <string>
#include <vector>
#include "slist.hpp"
#define key "key.json"

using namespace std;

class pyrat{
		string page;
		string video_path;
		string name;
		string path;
		string link;
		string tags;
		string desc;
		string vdesc;
		string rlink;
		string rvdesc;
	public:
		string get_vdesc();
		string get_description_r(string);
		string get_rvdesc(string link);
		int get_likes_r(string);
		bool check_catgory(string, string);
		slist top_search_videos(string, string);
		string get_vdesc(string);
		int get_likes(string);
		string decip(string);
		string temp(string, char, char);
		string get_full_name(string, string);
		vector<string> search_videos(string);
		string get_page(string);
		string get_description();
		string mainol(string);
		string get_tags();
		string get_tags(string);
		string get_tags_page(string);
		string get_name();
		string get_name(string);
		string get_name_page(string);
		int download();
		int upload(string);
		int set(string, string);
		int remove_video();
		bool lang_test(string l);
		string get_description(string l);
		
};
