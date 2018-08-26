#ifndef __HASH_FUNC_HPP__
#define __HASH_FUNC_HPP__

#include "hash_map.hpp"
#include <string>
#ifndef WIN32 
namespace HASH_MAP_NAMESPACE
{
    template<>
        struct hash<std::string>
        {
            size_t operator()(const std::string& data) const
            {
                return __stl_hash_string(data.c_str());
            }
        };
}
#else 

#endif // 



#endif //
