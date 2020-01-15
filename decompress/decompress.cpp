#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ostream>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////MAIN FILE FOR DECOMPRESSION/////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	ofstream output;
	output.open("decompout.txt");
	string arr[4096];
	
	for(int i=0;i<256;i++)
	{
		arr[i]=char(i);
	}
	
	ifstream file; 
	file.open("compout.txt");

	int prev,lastAsci=255;
	char temp;
	file >> prev;
	output << char(prev);

	while(!file.eof())
	{
		int curr;
		file >> curr;
		if(curr <= lastAsci && !file.eof())
		{
			lastAsci++;
			arr[lastAsci]=arr[prev]+arr[curr].at(0);
			output << arr[curr];
		}
		else if(!file.eof()) 
		{
			lastAsci++;
			arr[lastAsci]=arr[prev]+arr[prev].at(0);
			output << arr[lastAsci];
		}
		prev=curr;
	}

	return 0;
}