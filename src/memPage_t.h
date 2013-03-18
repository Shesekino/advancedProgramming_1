/*
 * memPage_t.h
 *
 *  Created on: 18 ???? 2013
 *      Author: user1
 */

#ifndef MEMPAGE_T_H_
#define MEMPAGE_T_H_

#define DEFAULT_SIZE 16

class memPage_t {
public:
	memPage_t(int pageSize);
	~memPage_t();
	int getPageCapacity() const;
	int getPageActualSize() const;
	bool isPageEmpty() const;
	bool isPageFull() const;
	int getCurrentPosition() const;
	bool setCurrentPosition(int position);
	int read(char* buffer, int length);
	int read(char* buffer, int length, int position);
	int write(const char* const buffer, int length);
	int write(const char* const buffer, int length, int position);
private:
	memPage_t(const memPage_t& p);
	void operator=(const memPage_t& p);
	const int capacity;
	char * const data;
	int currentPosition;
	int actualSize;
};

#endif /* MEMPAGE_T_H_ */
