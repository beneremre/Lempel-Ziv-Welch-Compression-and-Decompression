#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "hashtable.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////MAIN FILE FOR COMPRESSION///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	ifstream file;  //file opening
	ofstream output; //output file
	file.open("compin.txt");
	output.open("decompout.txt");
	HashTable<string,int> Hash; // vector
	int value=256;
	char p,c;
	string line;
	string stringForP= "";
	istringstream ss(line);
	file.get(p);	// get the first char from the txt file
	stringForP=p;
	while(!file.eof()) //while not end of file, keep reading
	{
		file.get(c); // get the second char from thetxt file
		if(Hash.isExists((stringForP+c))&& !file.eof()) //if exists in the vector
			stringForP=(stringForP+c);

		else if(!Hash.isExists((stringForP+c)) && !file.eof()) //if not exists
		{
			Hash.addFunc((stringForP+c),value); //add it to vector
			output << Hash.get(stringForP) << " " ;
			stringForP=c;
		}
	}
		output << Hash.get(stringForP) << endl;
	
	return 0;
}
