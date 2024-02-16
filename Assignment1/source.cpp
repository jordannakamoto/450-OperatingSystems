
#include <iostream>
#include <vector>
#include "file_reader.cpp"

using namespace std;

static const vector<int> PageTable = { 8192, 24576, 32768, 28672, 4096, 16384, 20480 };
static const int PageSize = 4096;

void translateLogical(int LogicalAddress){
	// Get the logical address
		int LogicalAddr = LogicalAddress;
		int PhysicalAddr;

		// Convert Logical address to physical address
		int LogicalIdx, offset;
		offset = LogicalAddr % PageSize;
		LogicalIdx = (LogicalAddr / PageSize);
		cout << "Logical Address: " << LogicalAddr << endl;
		cout << "Page Table Index = " << LogicalIdx << "  |  ";
		cout << "Offset = " << offset << endl;
		

		// Calculate Physical Address Location
		// Check upper bound of Page Table
		if (LogicalIdx <= PageTable.size()){
			int PhysicalValue = PageTable[LogicalIdx];
			// cout << "Physical Address Value of PageTable Entry for Logical Address is: " << PhysicalValue << endl;
			PhysicalAddr = PhysicalValue + offset;
			cout << "Corresponding Physical Address =  " << PhysicalAddr << endl;
		}
		else {
			cout << "Page Fault: Corresponding Physical Address Not in Memory" << endl;
		}
		cout << endl;
}

void translatePhysical(int PhysicalAddress){
	// Get the physical address
	int PhysicalAddr = PhysicalAddress;

		// Convert Physical address to Logical address
	        int PhysicalReference, offset;
			int LogicalAddr;
			int LogicalIdx = -1;
	        offset = PhysicalAddr % PageSize;
	        PhysicalReference = (PhysicalAddr - offset);
			cout << "Physical Address: " << PhysicalAddr << endl;
			cout << "PageFrame = " << PhysicalReference / PageSize << " | ";

	        // Perform Search
			// Assumes valid PageTable
			for (int i = 0; i < PageTable.size(); i++) {
		        if(PageTable[i] == PhysicalReference){
					LogicalIdx = i;
					break;
				}
		    }
			if (LogicalIdx != -1){
				LogicalAddr = LogicalIdx * PageSize + offset;
				cout << "PageTableIndex = " << LogicalIdx << " | ";
				cout << "LogicalPage = " << LogicalAddr << " | ";
				cout << "Offset = " << offset << endl;
				
				cout << "Corresponding Logical Address = " << LogicalAddr << endl;
			}
			else{
				cout << "Page Frame not in Page Table => Physical Address currently not allocated to the process"<< endl;
			}
			cout << endl;
}

/** *********************************************
 *  MAIN DRIVER CODE FOR TRANSLATING ADDRESSES  *
 ***********************************************/
int main() {

	FileReader fileReader;

	cout << "Page Table Entries : ";
	for(auto tableEntry: PageTable){
		cout << tableEntry << " ";
	}
	cout << endl;
	cout << "Page Size = " << PageSize << endl;

	fileReader.readFile("Logical.txt");
	cout << "******************************************\n\nTranslating from Logical to Physical Address\n" << endl;
	for(auto item: fileReader.fileItems){
		translateLogical(stoi(item));
	}
	fileReader.clearItems();
	fileReader.readFile("Physical.txt");
	cout << "******************************************\n\nTranslating from Physical to Logical Address\n" << endl;
	for(auto item: fileReader.fileItems){
		translatePhysical(stoi(item));
	}

    return 0;
}
