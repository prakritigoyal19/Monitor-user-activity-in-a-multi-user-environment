#include<bits/stdc++.h>
#define F           first
#define S           second
using namespace std;

#define N  100005

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int TESTS=1;
	freopen("changes.txt", "r", stdin); 
	freopen("output.txt", "w", stdout);
	while(TESTS--)
	{
		string s;
		int c=0,success=0,flg=0;
		map<pair<string,string>,int >m,ms;
		while(cin>>s){
			if(s=="Failed"){
				c++;
				flg=1;
				cin>>s;
			}
			else if(s=="Accepted"){
				success++;
				flg=2;
				cin>>s;
			}
			else if(flg==1){
				if(s=="for"){

					cin>>s;
					cout<<"**after for**"<<s<<"\n";
				}
				string user=s;
				cout<<"user: "<<user<<'\n';
				if(user=="invalid"){
					cin>>s;
					user=user+" "+s;
					cin>>s;
					user=user+" "+s;	
				}
				cout<<"********************************user****************:"<<user<<'\n';
				cin>>s;
				cin>>s;
				cout<<"pushed into: "<<s<<'\n';
				m[{s,user}]++;
				flg=0;
			}
			else if(flg==2){
				if(s=="for"){

					cin>>s;
					cout<<"**after for**"<<s<<"\n";
				}
				string user=s;
				cout<<"user: "<<user<<'\n';
				cin>>s;
				cin>>s;
				cout<<"pushed into: "<<s<<'\n';
				ms[{s,user}]++;
				flg=0;
			}
		}	
		cout<<"\nTotal number of Succesful login : "<<success<< " !!!\n";
		cout<<setw(13)<<"Ip address"<<setw(30)<<"Username"<<setw(60)<<"No of times session made \n";
		for(auto i:ms){
			cout<<setw(13)<<i.F.F<<setw(30)<<i.F.S<<setw(48)<<i.S<<'\n';
		}
		cout<<"\n\nTotal number of failed attempts made: "<<c<< " !!!\n";
		cout<<setw(13)<<"Ip address"<<setw(30)<<"Username"<<setw(60)<<"No of hacking attempts made\n";
		for(auto i:m){
			cout<<setw(13)<<i.F.F<<setw(30)<<i.F.S<<setw(48)<<i.S<<'\n';
		}
	}
	return 0;
}

