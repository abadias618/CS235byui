#ifndef MAP_H
#define MAP_H
#include "bnode.h"
#include "bst.h"
#include "pair.h"

namespace custom
{
template <class K, class V>
class map
{
public:
	map();
	map();
	map(const map& rhs);
	~map();
	map& operator = (const map& rhs);
	//insert
	void insert(const pair& input);
	void insert(const K& k, const V& v);
	//access
	V& operator[](const K& k);
	V operator[](const K& k)const;
	//standard interfaces
	int size()const;
	bool empty()const;
	void clear();
	//
	class iterator;
	iterator begin();
	iterator end();


private:
	BST bst;
};
//def constructor
template <class K, class V>
map<K,V>::map()
{
}
//non-def constructor
template <class K, class V>
map<K, V>::map()
{
}
//copy constructor
template <class K, class V>
map<K, V>::map(const map& rhs)
{
}
//destructor
template <class K, class V>
map<K, V>::~map()
{
}
//assignment
template <class K, class V>
map<K, V>& map<K, V>::operator = (const map<K,V>& rhs)
{
}
//access
template <class K, class V>
V& map<K, V>::operator [] (const K& k)
{
}
//access constant
template <class K, class V>
V map<K, V>::operator [] (const K& k)const
{
}
//insert pair
template <class K, class V>
void map<K, V>::insert(const pair<K, V>& input) 
{	
}
//insert values
template <class K, class V>
void map<K, V>::insert(const K& k, const V& v)
{
	pair<K, V> mypair;
	insert(mypair);
}
//size
template <class K, class V>
int map<K, V>::size()const 
{
}
//empty
template <class K, class V>
bool map<K, V>::empty()const
{
}
//clear
template <class K, class V>
void map<K, V>::clear()
{
}


}//end namespace custom
#endif // !MAP_H

