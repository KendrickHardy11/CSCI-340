/*	Kendrick Hardy
	z1945923
	CSCI 340-2
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

Entry newEnt;
string rec = "";

/**
 * Creates the hash tables
 *
 * @param hs The size of the hash table
 * ***********************************************************/
HT::HT(const unsigned &hs) {
	hsize = hs;
	hTable.resize(hs);
	list<Entry> entList;
	Entry Ent;
	entList.push_front(Ent);
	unsigned listEnt = 0;
	while(listEnt < hs){
		hTable[listEnt] = entList;
		listEnt += 1;
	}
} //End of HT

/**
 * Destructor of the hash table
 * ******************************************/
HT::~HT() {

	unsigned ents = 0;
	while(ents < hsize){
		hTable[ents].clear();
		ents += 1;
	}

	hTable.clear();
	pTable.clear(); 
} //End of ~HT

/**
 * Checks if a key already exists in a table
 *
 * @param l A list containing entries
 *
 * @returns true if the key is already in the table, false otherwise
 * **************************************************************************/
bool Dup(const list<Entry> &l){
	auto it = l.begin();
	while(it != l.end()){
		if(it->key == newEnt.key){
			return true;
		}
		++it;
	}
	return false;
} //End of Dup

/**
 * Inserts the record of the item into the hash table
 *
 * @param e The record
 *****************************************************************************/
void HT::insert(const Entry &e) 
{
	int value = hash(e.key);
	newEnt = e;
	auto it = std::find_if(hTable.begin(), hTable.end(), Dup);
	if(it != hTable.end()){
		cout << " not inserted - duplicate key!!!\n";
	}
	else
	{
		cout << " entry =" << setw(3) << right << value << "\n";
		if(hTable[value].front().key == ""){	
			hTable[value].front() = e;
			Entry * ent = &hTable[value].front();
			pTable.push_back(ent);
		}
		else{
			hTable[value].push_front(e);
			Entry * ent = &hTable[value].front();
			pTable.push_back(ent);
		}
	}
} //End of Insert

/**
 * Checks if the record is in the table
 *
 * @param e The entry to check
 *
 * @returns true if the record is in the hash table, false otherwise
 * *********************************************************************************/
bool findRec(const Entry &e){
	if(e.key == rec){
		return true;
	}
	else{
		return false;
	}
} //End of findRec

/**
 * Searches a hash table for a record with key
 *
 * @param key The key to search for
 * ****************************************************************************************************************/
void HT::search(const string &key) 
{
	int value = hash(key);
	rec = key;
	auto it = std::find_if(hTable[value].begin(), hTable[value].end(), findRec);
	if(it == hTable[value].end())
	{
		cout << " not in table!!\n";
	}
	else{
		cout << " ==> number: " << setw(4) << right << it->num << " - item: " << it->desc << "\n";
	}
} //End of search

/**
 * prints the contents of all the active records in the hash table
 * **********************************************************************/
void HT::hTable_print() {
	for(int i = 0; i < (int) hTable.size(); i++){
		if(hTable[i].front().key != "")
		{
			auto it = hTable[i].begin();
			while(it != hTable[i].end()){
				cout << i << ":  " << it->key << "  -  " << setw(4) << right << it->num << "  -  " << it->desc << "\n";
				++it;
			}
		}
	}
} //End of hTable_print

/**
 * checks if item in location p comes before the item in location q in alphabetical order
 *
 * @param p Location of item
 * @param q Location of item
 *
 * @returns true if key of the item in location p comes before the item in location q in alphabetical order, false otherwise
 * **************************************************************************************************************************/
bool cmp(Entry *p, Entry *q)
{
	if(p->key < q->key){
		return true;
	}
	else{
		return false;
	}
} //End of cmp

/**
 * Prints the contents of all the active records in the hash table
 *
 * @note Uses sort()
 * ***************************************************************************/
void HT::pTable_print() 
{
	sort(pTable.begin(), pTable.end(), cmp);
	auto it = pTable.begin();
	while(it != pTable.end()){
		cout << "   " <<(*it)->key << "  -  " << setw(4) << (*it)->num << "  -  " << (*it)->desc << "\n";
		++it;
	}
} //End of pTable_print
