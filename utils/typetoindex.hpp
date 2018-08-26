#ifndef __TYPE_TO_INDEX_HPP__ 
#define __TYPE_TO_INDEX_HPP__ 

#include "hash_map.hpp"
#include <vector>

using namespace HASH_MAP_NAMESPACE; 

template <class T>
struct TypeItem 
{
	bool bUsed; 
	T name; 
};

template <class T> 
class TypeToIndex 
{
public:

    typedef std::vector<TypeItem<T> > TypeItemVector; 
    typedef TypeItemVector::iterator TypeItemVectorItr; 

    typedef hash_map<T,int>  TypeItemMap; 
    typedef TypeItemMap::iterator TypeItemMapItr; 


	int getTypeIndex(const T & t)
	{
        TypeItemMapItr itr = m_typeMap.find (t);
        if (itr != m_typeMap.end())
        {
            return itr->second; 
        }
        return 0; 

	}

	T  getIndexType(int idx)
	{
		if (idx < m_typeVec.size())
		{
			return m_typeVec[idx]; 
		}
		return T(); 
	}

	T operator [](int idx)
	{
		if (idx < m_typeVec.size())
		{
			return m_typeVec[idx]; 
		}
		return T(); 
	}

    int operator ()(const T& t)
    {
        return getTypeIndex(t); 
    }

private:
	TypeItemVector m_typeVec; 
    TypeItemMap m_typeMap; 

};

#endif//   


    
