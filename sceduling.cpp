#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class process{
	int pno;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int xx;
	int priority;
	public:
	 process(int p,int a,int b){
		this->pno = p;
		this->at = a;
		this->bt = b;
		this->xx = b;
		priority = ct = tat = wt = -1;
	}
	bool operator < (const process & other)const{ 
		if(this->priority==-1){
			return xx > other.xx;
		}
		else{
			return priority < other.priority;
		}
	}
	friend class scheduling;
};
class scheduling{
	vector<process> table;
	int time_quantum;
	public:
		void get_input(vector<process>arr,int tq){
			table = arr;
			sort(table.begin(),table.end(),[](process &a,process &b){
				return a.at < b.at;
			});
			if(tq==-1){
				time_quantum = INT_MAX;
			}
			else{
				time_quantum = tq;
			}
		}
		void display(){
			cout<<"\nProcess no \tArrival\t     Bust\t  Completion\t   TurnAround\t      Wait";
			for(auto it : table){
				cout<<"\n"<<it.pno<<"\t\t"<<it.at<<"\t\t"<<it.bt<<"\t\t"<<it.ct<<"\t\t"<<it.tat<<"\t\t"<<it.wt;
			}
		}
		void fcfs_p(){
			table[0].ct= table[0].at + table[0].bt;
			for(int i = 0;i<table.size();i++){
				table[i].ct= max(table[i-1].ct,table[i].at) + table[i].bt;
			} 
		}
		void turnaround(){
			for(int i  = 0;i<table.size();i++){
				table[i].tat = table[i].ct - table[i].at;
			}
		}
		void wait(){
			
			for(int i  = 0;i<table.size();i++){
				table[i].wt = table[i].tat - table[i].bt;
			}
		}
		
		
		void sjf(){
			vector<process> temp;
			priority_queue<process> q;
			int current = 0;
			while(!table.empty() || !q.empty()){
				while(!table.empty() && table.front().at<=current){
					q.push(table.front());
					table.erase(table.begin());
				}
				if(!q.empty()){
					process k = q.top();
					q.pop();
					k.xx--;
					current++;
					if(k.xx>0){
						q.push(k);
					}
					else{
						k.ct = current;
						temp.push_back(k);
					}
				}
				else{
					current++;
				}
			}
			table = temp;
		}
		void rr(int tq){
			queue<process>q;
			vector<process>temp;
			int current = 0;
			while(!table.empty() || !q.empty()){
				while(!table.empty() && table.front().at <= current){
					q.push(table.front());
					table.erase(table.begin());
				}
				if(!q.empty()){
					process k = q.front();
					q.pop();
					int deduct = min(k.xx,tq);
					k.xx -= deduct;
					current += deduct;
					if(k.xx > 0){
						while(!table.empty() && table.front().at <= current){
							q.push(table.front());
							table.erase(table.begin());
						}
						q.push(k);
					}
					else{
						k.ct = current;
						temp.push_back(k);
					}
				}
				else{
					current++;
				}
			}
			table = temp;
		}
		void pp(){
			for(int i = 0;i<table.size();i++){
				cout<<"\nPriority for "<<table[i].pno;
				cin>>table[i].priority;
			}
			int current = 0;
			vector<process>temp;
			while(!table.empty()){
				int high_priority = INT_MIN;
				int hpi = -1;
				
				for(int i = 0;i<table.size();i++){
					if(table[i].at <= current && table[i].priority > high_priority){
						high_priority = table[i].priority;
						hpi = i;
					} 
				}
				
				if(hpi == -1){
					current++;
				}
				else{
					current += table[hpi].bt;
					table[hpi].ct= current;
					temp.push_back(table[hpi]);
					table.erase(table.begin() + hpi);
					
				}
			}
			table = temp;
			
		}
};
int main(){
	int count;

	vector<process> arr;
	cout<<"How many process: ";
	cin>>count;
	for(int i = 0;i<count;i++){
			int pno,a,b;
			cout<<"\nProcess No: ";
			cin>>pno;
			cout<<"\nArrival Time : ";
			cin>>a;
			cout<<"\nBust Time : ";
			cin>>b;
			process p(pno,a,b);
			arr.push_back(p);	
			cout<<"\n------------------";
	}
	int ch;
	cout<<"\n1.FCFS\n2.SJF(Primitive)";
	cin>>ch;
	if(ch==1){
		scheduling fcfs;
		fcfs.get_input(arr,-1);
		fcfs.fcfs_p();
		fcfs.turnaround();
		fcfs.wait();
		fcfs.display();
		
	}
	if(ch==2){
		scheduling fcfs;
		fcfs.get_input(arr,-1);
		fcfs.sjf();
		fcfs.turnaround();
		fcfs.wait();
		fcfs.display();
	}
	if(ch==3){
		scheduling rr;
		int c ;
		cout<<"\nTime Quantum : ";
		cin>>c;
		rr.get_input(arr,-1);
		rr.rr(c);
		rr.turnaround();
		rr.wait();
		rr.display();
	}
	if(ch==4){
		scheduling priority;
		priority.get_input(arr,-1);
		priority.pp();
		priority.turnaround();
		priority.wait();
		priority.display();	
	}
}