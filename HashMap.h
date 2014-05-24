
#ifndef __HASHMAP_H
#define __HASHMAP_H
#include "ElementNotExist.h"
#define debug cout<<"not here\n"
#include <iostream>
#include <cassert>
using namespace std;

template <class K, class V, class H>
class HashMap
{
public:
    int max(int a,int b)
    {
        return a>b?a:b;
    }
	class Entry
	{
		K key;
		V value;

	public:
		Entry *next;
		Entry(const K &k,const V& v)
		{
			key = k;
			value = v;
			next = NULL;
		}

		Entry()
		{
			next = NULL;
		}

		const K& getKey() const
		{
			return key;
		}

		const V& getValue() const
		{
			return value;
		}

		V &changeValue()
		{
		    return value;
		}
	};

private:
	Entry **elem;
	int Size;
	int num;

	int reHash(const K& x) const
	{
		int h = H::hashCode(x);
		h ^= (h >> 20) ^ (h >> 12);
		return ((h^(h >> 7) ^ (h >> 4)) & ((1 << 20) - 1));
	}

	void reSize()
	{
		int size0 = Size;
		if (2 * Size >= (1 << 20))
            Size = 1 << 20;
        else Size *= 2;
		Entry ** tmp = elem;
		elem = new Entry*[Size];
		for (int i = 0; i < Size; i++)
		{
			if (i < size0) elem[i] = tmp[i];
			else elem[i] = new Entry();
		}
	}

public:
	class Iterator
	{
	    int cnt;// number returned
		int index;//index in elem
        Entry *cur;
		HashMap * location;

	public:
		Iterator(HashMap *l):location(l)
		{
			cnt = 0;
			cur = location -> elem[0];
			index = 0;
		}

		bool hasNext()
		{
			return (cnt < location -> num);
		}

		const Entry &next()
		{
            if (!hasNext()) throw ElementNotExist();
            if (cur -> next == NULL)
            {
                cur = location -> elem[++index];
                while (location -> elem[index] -> next == NULL)
                    index++;
                cur = location -> elem[index] -> next;
                cnt++;
                return *cur;
            }
            else
            {
                cur = cur -> next;
                cnt++;
                return *cur;
            }
		}
	};

	HashMap()
	{
		num = 0;
		Size = 10;
		elem = new Entry *[Size];
		for (int i = 0; i < Size; i++)
			elem[i] = new Entry();
	}

	~HashMap()
	{
        clear();
		delete []elem;
	}

	HashMap &operator=(const HashMap &x)
	{
		clear();
		delete [] elem;
        num = x.num;
		Size = x.Size;
		elem = new Entry*[Size];
		for (int i = 0; i < Size; i++)
		{
			elem[i] = new Entry();
			Entry *tmp1, *tmp2;
			tmp2 = x.elem[i];
			tmp1 = elem[i];
			while (tmp2 -> next != NULL)
			{
				tmp1 -> next = new Entry(tmp2 -> next -> getKey(), tmp2 -> next -> getValue());
				tmp2 = tmp2 -> next;
				tmp1 = tmp1 -> next;
			}
		}
		return *this;
	}

	HashMap(const HashMap &x)
	{
		num = x.num;
		Size = x.Size;
		elem = new Entry*[Size];
		for (int i = 0; i < Size; i++)
		{
			elem[i] = new Entry();
			Entry *tmp1, *tmp2;
			tmp2 = x.elem[i];
			tmp1 = elem[i];
			while (tmp2 -> next != NULL)
			{
				tmp1 -> next = new Entry(tmp2 -> next -> getKey(), tmp2 -> next -> getValue());
				tmp2 = tmp2 -> next;assert(tmp2);
				tmp1 = tmp1 -> next;
			}
		}
	}

	void clear()
	{
		for (int i = 0; i < Size; i++)
		{
			Entry *tmp = elem[i] -> next;
			Entry *tmp2;
			while (tmp != NULL)
			{
				tmp2 = tmp;
				tmp = tmp -> next;
				delete tmp2;
				tmp2 = NULL;
			}
		}
		num = 0;
	}

	bool containsKey(const K& key) const
	{
		int loc = reHash(key);
		Entry *tmp = elem[loc] -> next;
		while (tmp != NULL && tmp -> getKey() != key) tmp = tmp -> next;
		if (tmp == NULL) return false;
		else return true;
	}

	bool containsValue(const V &value) const
	{
		for (int i = 0; i < Size; i++)
		{
			Entry *tmp = elem[i] -> next;
			while (tmp != NULL && tmp -> getValue() != value) tmp = tmp -> next;
			if (tmp != NULL) return true;
		}
		return false;
	}

	const V &get(const K & key) const
	{
		int loc = reHash(key);
		Entry *tmp = elem[loc] -> next;
		while (tmp != NULL && tmp -> getKey() != key) tmp = tmp -> next;
		if (tmp == NULL) throw ElementNotExist();
		else return tmp -> getValue();
	}

	bool isEmpty() const
	{
	    return (num == 0);
	}

	void put(const K & key, const V &value)
	{
		int loc = reHash(key);
		while (loc + loc / 2 > Size && Size < (1 << 20)) reSize();
		Entry *tmp = elem[loc] -> next;
		while (tmp != NULL && tmp -> getKey() != key)
			tmp = tmp -> next;
		if (tmp == NULL)
		{
			tmp = new Entry(key, value);
			tmp -> next = elem[loc] -> next;
			elem[loc] -> next = tmp;
			num++;
		}
		else
			tmp -> changeValue() = value;
	}

	void remove(const K &key)
	{
		int loc = reHash(key);
		Entry *tmp = elem[loc];
		while (tmp -> next != NULL && tmp -> next -> getKey() != key)
			tmp = tmp -> next;
		if (tmp -> next == NULL) throw ElementNotExist();
		else
		{
			Entry *tmp2 = tmp -> next;
			tmp -> next = tmp2 -> next;
			delete tmp2;
		}
		num--;

	}

	int size() const
	{
		return num;
	}

	Iterator iterator()
	{
		return Iterator(this);
	}


};

#endif
