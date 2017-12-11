#ifndef __INTMAP_H__
#define __INTMAP_H__


#include <vector>


#include "IntStack.h"

class IntMap
{
public:
	IntMap();
	IntMap(int size);
	IntMap(int size, double fillFactor);
	~IntMap();


	int get(int key);
	bool contains(int key);
	bool add(int key);
	bool del(int key);
	bool isEmpty();
	int put(int key, int value);
	int remove(int key);
	int size();
		




	static void intersect0(IntMap *m, std::vector<IntMap*>& maps, std::vector<IntMap*>& vmaps, IntStack& r);
	static IntStack intersect(std::vector<IntMap*>& maps, std::vector<IntMap*>& vmaps);



	static const int NO_VALUE = 0;

private:

	void construct(int size, double fillFactor);

	int shiftKeys(int pos);
	void rehash(int newCapacity);
	static long long nextPowerOfTwo(long long x);
	static int arraySize(int expected, double f);
	static int phiMix(int x);


	static const int FREE_KEY = 0;


	/** Keys and values */
	int* m_data;

	/** Do we have 'free' key in the map? */
	bool m_hasFreeKey;
	/** Value of 'free' key */
	int m_freeValue;

	/** Fill factor, must be between (0 and 1) */
	double m_fillFactor;
	/** We will resize a map once it reaches this size */
	int m_threshold;
	/** Current map size */
	int m_size;

	/** Mask to calculate the original position */
	int m_mask;
	int m_mask2;


	static const int INT_PHI = 0x9E3779B9;

	int m_dataSize;
};

#endif