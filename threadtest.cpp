#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;
void helper1(){
	for(int i=0;i<50;i++){
		cout<<"T1: helper1"<<endl;
		sleep(1);
	}
}
void helper2(){
	for(int i=0;i<50;i++){
		cout<<"T2:-helper2"<<endl;
		sleep(1);
	}
}
int main(){
	cout<<"Main Thread"<<endl;
	thread t1(helper1);
	thread t2(helper2);
	t1.join();
	t2.join();
	return 0;
}