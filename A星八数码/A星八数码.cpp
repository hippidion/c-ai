#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
using namespace std;
struct Node{								
	vector<int> array;
	int g;
	int f;
	bool operator < (const Node &a) const	
    {
        return a.f < f;
    }
	Node(vector<int> arg){
		array=arg;
	}
};

int getno(vector<int> a,vector<int> b){	 
	int count=0;
	for(int i=0;i<9;i++){
		if(a[i]){
			for(int j=0;j<9;j++){
				if(a[i]==b[j]){
					count+=(abs(i/3-j/3)+abs(i%3-j%3));
					break;
				}
			}
		}
	}
	return count;
}

void disp(vector<int> a){					 
	for(int i=0;i<9;i++){
		if(i%3) cout<<" ";
		else cout<<endl;
		cout<<a[i];
	}
}

void swap(vector<int> &a,int i,int j){		 
	int t=a[i];	
	a[i]=a[j];
	a[j]=t;
} 
vector<vector<int> > getnext(vector<int> a){
	vector<vector<int> > res;
	vector<int> cur=a;
	int i;
	for(i=0;i<9;i++){
		if(cur[i]==0) break;
	}
	if(i/3+1!=3){
		swap(cur,i,i+3);
		res.push_back(cur);
		swap(cur,i,i+3);		
	}											 
	if(i/3-1!=-1){
		swap(cur,i,i-3);
		res.push_back(cur);
		swap(cur,i,i-3);		
	}
	if(i%3+1!=3){
		swap(cur,i,i+1);
		res.push_back(cur);
		swap(cur,i,i+1);
	}
	if(i%3-1!=-1){
		swap(cur,i,i-1);
		res.push_back(cur);
		swap(cur,i,i-1);
	}
	return res;
}

int main(){
	vector<int> start(9);
	vector<int> goal(9);
	int a[]={2,8,3,1,6,4,7,0,5};
	int b[]={1,2,3,8,0,4,7,6,5};
	for(int i=0;i<9;i++){
		start[i]=a[i];
		goal[i]=b[i];
	}
	Node s(start);
	s.g=0;
	s.f=getno(s.array,goal);
	priority_queue<Node> q;				
	q.push(s);
	map<vector<int>,vector<int> > open;		
	map<vector<int>,vector<int> > close;	
	open[start]=start;
	Node newnode(vector<int>(9));
	while(q.size()){						 
		Node cur=q.top();					
		q.pop();
		close[cur.array]=open[cur.array];		
		if(cur.array==goal) break;		
		vector<vector<int> > v=getnext(cur.array);
		for(int i=0;i<v.size();i++){
			if(close.find(v[i])!=close.end()) continue;	 
			open[v[i]]=cur.array;
			newnode.array=v[i];						
			newnode.g=cur.g+1;
			newnode.f=newnode.g+getno(newnode.array,goal);	
			q.push(newnode);						
		}
	}
	vector<int> array;								
	vector<vector<int> > result;
	array=goal;
	while(close[array]!=array){
		result.push_back(array);
		array=close[array];
	}
	result.push_back(array);
	for( i=result.size()-1;i>=0;i--){			
		disp(result[i]);
		cout<<endl;
	}
	return 0;
}
