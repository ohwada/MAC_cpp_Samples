/**
 *  gen_uuid.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/mariusbancila/stduuid

#define UUID_SYSTEM_GENERATOR

#include <iostream>
#include "uuid.h"


/**
 * main
 */
int main()
{
    uuids::uuid const id = uuids::uuid_system_generator{}();
    assert(!id.is_nil());
    assert(id.version() == uuids::uuid_version::random_number_based);
    assert(id.variant() == uuids::uuid_variant::rfc);

    std::cout << id << std::endl;

    return 0;
}
