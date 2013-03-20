/*
 * memPage_t.cpp
 *
 *  Created on: 18 ???? 2013
 *      Author: user1
 */

#include "memPage_t.h"

memPage_t::memPage_t(int pageSize) : capacity((pageSize > 0) ? pageSize : DEFAULT_SIZE), currentPosition(0), actualSize(0), data(new char[(capacity > 0) ? capacity : DEFAULT_SIZE]) { }

memPage_t::~memPage_t() {
	delete[] data;
}

int memPage_t::getPageCapacity() const {
	return capacity;
}

int memPage_t::getCurrentPosition() const {
	return currentPosition;
}

bool memPage_t::setCurrentPosition(int position) {
	if(position <= actualSize) {
		currentPosition = position;
		return true;
	}
	return false;
}

int memPage_t::getPageActualSize() const {
	return actualSize;
}

bool memPage_t::isPageEmpty() const {
	return actualSize == 0;
}

bool memPage_t::isPageFull() const {
	return actualSize == capacity;
}

int memPage_t::read(void* buffer, int length) {
	return read(buffer, length, currentPosition);
}

int memPage_t::read(void* buffer, int length, int position) {
	int i;

	for(i = 0; (i < length) && (position < actualSize); i++) {
		((char*)buffer)[i] = data[position++];
	}

	currentPosition = position;
	return i;
}

int memPage_t::write(const void* const buffer, int length) {
	return write(buffer, length, currentPosition);
}

int memPage_t::write(const void* const buffer, int length, int position) {
	int i;

	for(i = 0; (i < length) && ( position < capacity); i++) {
		data[position++] = ((char*)buffer)[i];
	}

	if(position > actualSize) {
		actualSize = position;
	}

	currentPosition = position;
	return i;
}
