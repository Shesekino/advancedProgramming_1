/*
 * memPool_t.h
 *
 *  Created on: 18 ???? 2013
 *      Author: user1
 */

#ifndef MEMPOOL_T_H_
#define MEMPOOL_T_H_

#include "memPage_t.h"
#define DEFAULT_PAGE_CAPACITY 16

class memPool_t {
public:
	memPool_t(int defaultPageSize, int capacityPages = DEFAULT_PAGE_CAPACITY);
	~memPool_t();
	int getCurrentPosition() const;
	bool setCurrentPosition(int position);
	bool isPoolEmpty() const;
	int getActualSize() const;
	int getPoolCapacity() const;
	int getNumberOfPages() const;
	int getDefaultPageSize() const;
	void setDefaultPageSize(int newPageSize);
	int read(void* buffer, int length);
	int read(void* buffer, int length, int position);
	int write(const void* buffer, int length);
	int write(const void* buffer, int length, int position);


private:
	memPool_t(const memPool_t& p);
	void operator=(const memPool_t& p);
	int defaultPageSize;
	int capacityPages;
	int actualPages;
	int currentPage;

	class memPageNode_t {
	public:
		memPageNode_t(int pageSize) : currentPage(pageSize), nextNode(0) { }
		~memPageNode_t() { }
		memPage_t currentPage;
		memPageNode_t* nextNode;
	};
	memPageNode_t* head;

	const memPageNode_t* getCurrentNode() const;
};

#endif /* MEMPOOL_T_H_ */
