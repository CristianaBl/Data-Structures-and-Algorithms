#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;

    TElem* elems;
    int len;
    int index;

	SMMIterator(const SortedMultiMap& map);



public:
    void modifycurrent( TValue* newValues, TKey newKey);
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

