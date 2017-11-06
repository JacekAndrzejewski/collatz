#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;
#define ulint unsigned long long int

struct sol
{
	ulint x;
	unsigned int sol;
}typedef solution;

void preCalcSteps()
{
	unsigned int limit=100000000;
	int* tab=new int[limit];
	for(unsigned int i=0;i<limit;i++)
		tab[i]=0;

	tab[0]=-1;
	tab[1]=0;

	fstream file;
	file.open("collatzPrecalc.txt",ios::trunc | ios::in | ios::out);

	file<<-1<<"\n"<<0<<"\n";

	for(ulint i=2;i<limit;i++)
	{
		ulint temp=i;
		unsigned int count=0;
		bool und;
		if(tab[i]==0)
			und=true;
		else
			und=false;
		while((temp>=limit || tab[temp]==0) && temp!=1)
		{
			count++;
			if(temp%2==0)
				temp=temp/2;
			else
				temp=3*temp+1;
		}
		if(und==true)
			tab[i]=tab[temp]+count;
		file<<tab[i]<<"\n";
	}
	delete tab;

	file.close();
}

solution maxChange(ulint lim)
{
	fstream file;
	unsigned int limit=100000000;
	
	file.open("collatzPrecalc.txt");
	if(file.good()==false)
	{
		file.close();
		preCalcSteps();
		file.open("collatzPrecalc.txt");
	}
	solution max;
	ulint digit=limit*10;
	int adder=0;

	//max for limit lesser than 100 000 000 is i=63728127 steps:950
	//it's always precalculated in the file, so we can just enter it
	max.x=63728127;
	max.sol=950;

	int* tab=new int[limit];
	
	for(unsigned int i=0;i<limit;i++)
		file>>tab[i];

	//explanation about the loop:
	//we don't need to check the first half of our range, because it is guaranteed a number with bigger number
	//of steps will be in the second half
	//Proof:
	//Let's say we have K for which f(k) is biggest in the first half of range
	//that means K<N/2, where N is biggest number to check
	//if f(K) gives us X steps, then f(2K)=1+f(K)=X+1 steps
	//and 2K<N, so we have a number with bigger number of steps in the second half
	//
	//Second thing: using adder
	//from experiments it shows up that checking numbers k%3==2 has no sense
	//because all changes of max number of steps are at k%3!=2
	//Adder makes sure that we always get k%3!=2
	//
	//One afterthought: We could just check bigger numbers that are probable to have bigger number of steps,
	//but we wouldn't be sure that we get K with biggest possible number of steps

	for(ulint i=limit;i<lim;i+=adder+1)
	{
		adder=(adder+1)%2;
		ulint temp=i;
		unsigned int count=0;
		unsigned int sol=0;

		while(temp>=limit)
		{
			if(temp%2==0)
				temp=temp/2;
			else
				temp=temp*3+1;
			count++;
		}

		sol=tab[temp]+count;
		if(sol>max.sol)
		{
			cout<<"Max change at "<<i<<" from "<<max.sol<<" to "<<sol<<" change is "<<sol-max.sol<<"\n";
			max.sol=sol;
			max.x=i;
		}
		if(i>=digit)
		{
			digit=digit*10;
			i=digit/2+1;
			adder=0;
		}
		if(i%limit==0)
			cout<<"Calculating "<<i<<"\n";
	}

	delete tab;
	file.close();

	return max;
}

int main()
{
	solution sol;
	ulint n;
	cout<<"Give n\n";
	cin>>n;
	sol=maxChange(n);
	cout<<"Max steps for n smaller than "<<n<<":"<<sol.sol<<" i="<<sol.x<<"\n";
	//Max steps for n smaller than 100 000 000 000:1229 i=75 128 138 247
	//Max steps for n smaller than 757 800 000 000:1333 i=674 190 078 379

	return 0;
}