#include "slist.hpp"

slist::slist(){
	indicator = 0;
	counter = 0;
	limit = 0;
}

bool slist::operator == (int num){
	if(counter == num)
		return 1;
	return 0;
}

bool slist::operator != (int num){
	if(*this == num)
		return 0;
	return 1;
}

slist& slist::operator--(){  
   counter--;  
   return *this;  
}  

slist slist::operator--(int){  
   slist temp = *this;  
   --*this;  
   return temp;  
}

slist& slist::operator++(){  
   counter++;  
   return *this;  
}  

slist slist::operator++(int){  
   slist temp = *this;  
   ++*this;  
   return temp;  
}  

void slist::show(){
	if(!indicator){
		sort();
		indicator=1;
	}	
	
	for(vector<string>::iterator it = str.begin();
				it != str.end(); it++){
		cout << *it << " " << num[(it - str.begin())]<< endl;
	}
}
bool slist::empty(){
	if(!limit)
		return 1;
	return 0;
}

string slist::search(int n){
	for(int i = 0;i!=limit; i++)
		if(num[i]==n)
			return str[i];
	
	return string("");
}

int slist::search(string s){
	for(int i = 0;i!=limit; i++)
		if(str[i]==s)
			return num[i];
			
	return -1;
}

int slist::get_counter(){
	return counter;
}

void slist::sort(){
	for(int i=0; i != limit; i++){
		for(int j=0; j != limit; j++){
			if(num[j]<num[i]){
				swap(num[j], num[i]);
				swap(str[j], str[i]);
			}
		}	
	}	
}

void slist::add(string s, int n){
	if(indicator)
		indicator = 0;
	limit++;
	str.push_back(s);
	num.push_back(n);
}

void slist::add(int n, string s){
	add(s, n);
}

string slist::get(int i){
	if(!indicator){
		sort();
		indicator=1;
	}
	
	return search(i);
}

int slist::get(string s){
	if(!indicator){
		sort();
		indicator=1;
	}
	
	return search(s);
}


string slist::get_s(int i){
	if(!indicator){
		sort();
		indicator=1;
	}
	
	if(i>=limit)
		i = limit - 1;
	return str[i];
}

string slist::get(){
	if(!indicator){
		sort();
		indicator=1;
	}
	
	if(counter>=limit)
		counter = limit - 1;
	return str[counter];
}

int slist::get_n(int i){
	if(!indicator){
		sort();
		indicator=1;
	}
	if(i>=limit)
		i = limit - 1;
	return num[i];
}

int slist::get_n(){
	if(!indicator){
		sort();
		indicator=1;
	}
	
	if(counter>=limit)
		counter = limit - 1;
	return num[counter];
}

int slist::end(){	
	return limit;	
}
