#ifndef __IMAP_H__
#define __IMAP_H__

#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

#include "IntMap.h"


template <typename K> class IMap
{
public:

	IMap()
	{
	}

	~IMap()
	{
	}

	void clear()
	{
		map.clear();
	}

	bool put(K key, int val)
	{
		IntMap* vals = map[key];
		if (NULL == vals) {
			vals = new IntMap();
			map[key] = vals;
		}
		return vals->add(val);
	}

	IntMap* get(K key)
	{
		IntMap* s = map[key];
		if (NULL == s) {
			s = new IntMap();
		}
		return s;
	}

	std::set<K> keySet()
	{
		std::set<K> S;
		typename std::map<K, IntMap>::iterator it = map.begin();
		for (; it != map.end(); it++)
		{
			S.insert(it->first);
		}
		return S;
	}




	// specialization for array of int maps

	static std::vector<IMap<int>*>* create(int l)
	{
		std::vector<IMap<int>*>* V = new std::vector<IMap<int>*>(l);
		for (int i = 0; i < l; i++)
			(*V)[i] = new IMap<int>();
		return V;
	}

	static bool put(std::vector<IMap<int>*>* imaps, int pos, int key, int val)
	{
		return (*imaps)[pos]->put(key, val);
	}

	static std::vector<int> get(std::vector<IMap<int>*>* imaps, std::vector<IntMap*>* vmaps, const std::vector<int>& keys)
	{
		int l = (int)imaps->size();
		std::vector<IntMap*> ms;
		std::vector<IntMap*> vms;

		for (int i = 0; i < l; i++) {
			int key = keys[i];
			if (0 == key) {
				continue;
			}
			IntMap* m = (*imaps)[i]->get(key);
			ms.push_back(m);
			vms.push_back((*vmaps)[i]);
		}

		std::vector<IntMap*> ims(ms.size());
		std::vector<IntMap*> vims(vms.size());

		for (unsigned int i = 0; i < ims.size(); i++) {
			IntMap* im = ms[i];
			ims[i] = im;
			IntMap* vim = vms[i];
			vims[i] = vim;
		}


		IntStack cs = IntMap::intersect(ims, vims); // $$$ add vmaps here
		std::vector<int> is = cs.toArray();
		for (unsigned int i = 0; i < is.size(); i++) {
			is[i] = is[i] - 1;
		}
		std::sort(is.begin(), is.end());
		return is;

	}

	static std::string show(std::vector<IMap<int>*>* imaps)
	{
		return "IMap::show()";
	}

private:
	std::map<K, IntMap*> map;
};


#endif
