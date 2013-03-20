/*
 * memPool_t.cpp
 *
 *  Created on: 18 ???? 2013
 *      Author: user1
 */

#include "memPage_t.h"
#include "memPool_t.h"

memPool_t::memPool_t(int defaultPageSize, int capacityPages) : 	defaultPageSize(defaultPageSize),
																capacityPages(capacityPages),
																actualPages(0),
																currentPage(0) {
	if(capacityPages >= 1) {
		head = new memPageNode_t(defaultPageSize);
	} else {
		head = 0;
	}

	memPageNode_t *curr, *next;
	curr = head;
	for(int i = 1; i < capacityPages; i++) {
		next = new memPageNode_t(defaultPageSize);
		curr->nextNode = next;
		curr = curr->nextNode;
	}
}

memPool_t::~memPool_t() {
	memPageNode_t *curr, *next;
	curr = head;
	while(curr != 0) {
		next = curr->nextNode;
		delete curr;
		curr = next;
	}
}

int memPool_t::getCurrentPosition() const {
	int sum = 0;
	int pagesPassed = 0;
	memPageNode_t* curr = head;

	while(pagesPassed < currentPage) {
		sum += curr->currentPage.getPageCapacity();
		curr = curr->nextNode;
		pagesPassed++;
	}

	sum += curr->currentPage.getCurrentPosition();

	return sum;
}

bool memPool_t::setCurrentPosition(int position) {

	int newCurrentPage = 0;
	memPageNode_t* curr = head;

	while((curr != 0) && (position > curr->currentPage.getPageCapacity())) {
		if(!(curr->currentPage.isPageFull())) {
			return false; // tried to create a hole in the memory
		}

		position -= curr->currentPage.getPageCapacity();
		curr = curr->nextNode;
		newCurrentPage++;
	}

	if(curr->currentPage.setCurrentPosition(position)) {
		currentPage = newCurrentPage;
		return true;
	}

	return false;
}

bool memPool_t::isPoolEmpty() const {
	return (head->currentPage.isPageEmpty());
}

int memPool_t::getActualSize() const {
	memPageNode_t* curr = head;
	int sum = 0;

	while(curr != 0) {
		sum += curr->currentPage.getPageActualSize();
		if(!curr->currentPage.isPageFull())
			break;
		curr = curr->nextNode;
	}

	return sum;
}

int memPool_t::getPoolCapacity() const {
	memPageNode_t* curr = head;
	int sum = 0;
	while(curr != 0) {
		sum += curr->currentPage.getPageCapacity();
		curr = curr->nextNode;
	}
	return sum;
}

int memPool_t::getNumberOfPages() const {
	memPageNode_t* curr = head;
	int num = 0;

	while(curr != 0) {
		num++;
		curr = curr->nextNode;
	}

	return num;
}

int memPool_t::getDefaultPageSize() const {
	return defaultPageSize;
}

void memPool_t::setDefaultPageSize(int newPageSize) {
	if(newPageSize > 0) {
		defaultPageSize = newPageSize;
	}
}

int memPool_t::read(char* buffer, int length) {
	int numRead = 0;

	// getting relevant page
	memPageNode_t* curr = head;
	for(int j = 0 ; j < currentPage ; j++) {
		curr = curr->nextNode;
	}

	while (curr != 0) {
		int temp = curr->currentPage.read(buffer, length);
		numRead += temp;
		length -= temp;
		buffer += temp;

		if (length==0) { // finished reading
			return numRead;
		}

		if(!(curr->currentPage.isPageFull())) { // nothing left to read
			return numRead;
		}

		curr = curr->nextNode;
		if (curr != 0) {
			currentPage++;
			curr->currentPage.setCurrentPosition(0);
		}
	}

	return numRead;
}

int memPool_t::read(char* buffer, int length, int position) {
	if(!(this->setCurrentPosition(position))) {
		return 0;
	} else {
		return read(buffer, length);
	}
}

int memPool_t::write(const char* buffer, int length) {
	int numWrote = 0;

	// getting relevant page
	memPageNode_t* curr = head;
	for(int j = 0 ; j < currentPage ; j++) {
		curr = curr->nextNode;
	}

	while(length > 0) {

		// writing to the page
		int temp = curr->currentPage.write(buffer, length);
		numWrote += temp;
		length -= temp;
		buffer += temp;

		if(length == 0) {
			return numWrote;
		} else {
			if(curr->nextNode == 0) { // creating new node
				curr->nextNode = new memPageNode_t(defaultPageSize);
			}

			curr = curr->nextNode;
			currentPage++;
		}
	}

	return numWrote;
}

int memPool_t::write(const char* const buffer, int length, int position) {
	if(!(this->setCurrentPosition(position))) {
		return 0;
	} else {
		return write(buffer, length);
	}
}

