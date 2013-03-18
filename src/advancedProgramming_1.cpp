//============================================================================
// Name        : advancedProgramming_1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "memPage_t.h"
#include "memPool_t.h"
using namespace std;

int main() {
	/*
	memPage_t myObj(16);

	cout << "current position is: " << myObj.getCurrentPosition() << endl;
	myObj.write("amir", 4);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	cout << "rewinding..." << flush;
	myObj.setCurrentPosition(0);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	char Stuff[16];
	int readChars = myObj.read(Stuff, 6);
	cout << "read things: " << Stuff << " total of " << readChars << endl;

	cout << "attempting to set current position to 5..." << flush;
	myObj.setCurrentPosition(5);
	cout << "current position is: " << myObj.getCurrentPosition() << endl;

	//memPage_t mySecondObj = myObj;
	//memPage_t mySecondObj(16);
	//mySecondObj = myObj;

	*/

	memPool_t pool3(2 ,1);

	char Stuff[16];
	int derp = pool3.read(Stuff, 4);
	cout << "pool 3 read : " << derp << " chars, content is : " << Stuff << endl;
	int herp = pool3.write("amiramiramir", 13, 0);
	cout << "pool 3 wrote : " << herp << " chars " << endl;
	derp = pool3.read(Stuff, 13, 0);
	cout << "pool 3 read : " << derp << " chars, content is : " << Stuff << endl;
	cout << "actual size is  : " << pool3.getActualSize() << endl;
	cout << "page num is  : " << pool3.getNumberOfPages() << endl;

	return 0;
}
