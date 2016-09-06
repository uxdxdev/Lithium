//
//  Util.cpp
//  Lithium
//
//  Created by David Morton on 06/09/2016.
//
//
#include "util/Util.h"
#include <uuid/uuid.h>

std::string Util::GenerateUuid()
{
    uuid_t id;
    uuid_generate_time(id);
    char uuid_str[37];
    uuid_unparse_lower(id, uuid_str);
    return std::string(uuid_str);
}