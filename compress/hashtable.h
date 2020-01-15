#include <iostream>
#include <string>
#include <vector>

using namespace std;

int TABLE_SIZE = 4096; //initial table size is 4096

template<class k,class v>
class HashTable
{

private:
	
	int hash(k key) //hash function to determine an index for each of the strings
	{
		int hashValue=0;

		if(key.length() == 1)
			return int(key[0]);

		for(unsigned int i=0; i<key.length(); i++)
			hashValue = 31 * hashValue + int(key[i]);

		hashValue += 255;
		hashValue = hashValue %TABLE_SIZE;
		if (hashValue<0)
			hashValue+=TABLE_SIZE;

		return hashValue;
	}

public:
	
	struct HashEntry //struct to keep an element in the vector
	{
		k key;
		v value;
		HashEntry(){key="";value=0;}
	
		HashEntry(k &first,v &second)
		{
			key=first;
			value=second;
		}
	};
	
	HashTable(); //default constructor
	vector<HashEntry>hashVec;	
	void addFunc(k key,v &value);
	int findPos(k key);
	bool isExists(k key);
	bool operator==(const HashTable&rhs);
	bool operator!=(const HashTable&rhs);
	int get(k k);
};

template<class k,class v>
HashTable<k,v>::HashTable(): hashVec(4096) //constructer
{
	for (unsigned int i=0; i<=255; i++)
	{ 
		char ch = char(i);  
		hashVec[i].key = ch; 
		hashVec[i].value = i;
	} 
	for(unsigned int j=256; j<hashVec.size(); j++)
	{
		hashVec[j].key = "notFound";
		hashVec[j].value = NULL;
	}	
}

template<class k,class v>
void HashTable<k,v>::addFunc(k key,v &value) //this function allows us to add an element to the vector
{
	int index = hash(key);
	if(value>=TABLE_SIZE)
		return ;

	if(hashVec[index%TABLE_SIZE].key == "notFound") //if the key element is equal to notFound that means that part of the vector is empty
	{
		hashVec[index%TABLE_SIZE].key = key;
		hashVec[index%TABLE_SIZE].value = value;
		value++;
	}
	else //for the lineer probing
	{
		int a=0;
		while(hashVec[(index+a)%TABLE_SIZE].key != "notFound")
			a++;
		hashVec[(index+a)%TABLE_SIZE].key = key;
		hashVec[(index+a)%TABLE_SIZE].value = value;
		value++;
	}
}

template<class k,class v>
int HashTable<k,v>::findPos(k key) //find the possition for the element of the vector
{
	int pos = hash(key);
	return pos;
}

template<class k,class v>
bool HashTable<k,v>::isExists(k key) //this function allows us to check whether it exists in the vector
{
	int index=findPos(key);

	if(hashVec[index%TABLE_SIZE].key == "notFound")
		return false;

	else if(hashVec[index%TABLE_SIZE].key==key)
		return true;

	else if(hashVec[index%TABLE_SIZE].key!=key)
	{
		int i=0;
		while(hashVec[(index+i)%TABLE_SIZE].key != "notFound")
		{
			if(hashVec[(index+i)%TABLE_SIZE].key==key)
				return true;
			i++;
		}
				return false;
	}
}

template<class k,class v>
bool HashTable<k,v>::operator==(const HashTable &rhs) // == operator overload
{
	if(rhs.hashVec.size() != hashVec.size())
		return false;
	for(int i=0; i < TABLE_SIZE; i++)
	{
		if(rhs.hashVec[i].key != hashVec[i].key)
			return false;
	}
			return true;
}

template<class k,class v>
bool HashTable<k,v>::operator!= (const HashTable &rhs) // != operator overload
{
    return !((*this) != rhs);
}

template<class k,class v>
int HashTable<k,v>::get(k key) //this function allows us to get the value kept in the vector
{
	int pos = findPos(key);
	
	if(hashVec[pos%TABLE_SIZE].key==key)
		 return hashVec[pos%TABLE_SIZE].value;

	else
	{
		int i=0;
		while(hashVec[(pos+i)%TABLE_SIZE].key != "notFound") //it checks whether we made linear probing or not 
		{
			if(hashVec[(pos+i)%TABLE_SIZE].key==key)
				return hashVec[(pos+i)%TABLE_SIZE].value;
			i++;
		}
	}
}

