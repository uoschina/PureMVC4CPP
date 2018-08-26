#ifndef __HASH_MAP_HPP__
#define __HASH_MAP_HPP__ 

// !cj! if all these machine have to use map then we can just delete them and use the default 

#  if ( (__GNUC__ == 3) && (__GNUC_MINOR__ >= 1) ) || ( __GNUC__ > 3 )
#    include <ext/hash_map>
#    include <ext/hash_set>
#    define HASH_MAP_NAMESPACE __gnu_cxx
#    define HashMap __gnu_cxx::hash_map
#    define HashSet __gnu_cxx::hash_set

// this allows us to hash on a pointer as the key 
namespace HASH_MAP_NAMESPACE
{
    template <class T>
        struct hash<T*>
        {
            size_t operator()(const T* t) const
            {
                return size_t(t);
            }
        };

}

#define HashValue(type)                           \
    namespace HASH_MAP_NAMESPACE                      \
{                                                 \
    template <>                                       \
    struct hash<type>                                 \
    {                                                 \
        size_t operator()(const type& data) const;  \
    };                                                \
}                                   
#define HashValueImp(type, ret) size_t HASH_MAP_NAMESPACE::hash<type>::operator()(const type& data) const { return ret; }

#  elif  defined(__INTEL_COMPILER )
#    include <hash_map>
#    define HASH_MAP_NAMESPACE std
#    define HashMap std::hash_map
#    define HashSet std::hash_set
#    define HashValue(type)              \
    namespace HASH_MAP_NAMESPACE        \
{                                   \
    size_t hash_value(const type& data);\
}                                   
#    define HashValueImp(type, ret) size_t HASH_MAP_NAMESPACE::hash_value(const type& data) { return ret; }
#  elif  defined(WIN32) && defined(_MSC_VER) && (_MSC_VER >= 1310)  // hash_map is in stdext namespace for VS.NET 2003
#    include <hash_map>
#    include <hash_set>
#    define HASH_MAP_NAMESPACE stdext
#    define HashMap stdext::hash_map
#    define HashSet stdext::hash_set
#    define HashValue(type)              \
    namespace HASH_MAP_NAMESPACE        \
{                                   \
    size_t hash_value(const type& data);\
}                                   
#    define HashValueImp(type, ret) size_t HASH_MAP_NAMESPACE::hash_value(const type& data) { return ret; }
#  else
#    include <map>
#    define HashMap std::map
#    define HashSet std::set
#    define HashValue(type)    
#    define HashValueImp(type, ret) 
#  endif


#endif



