#pragma once
/**
 * ws_response_builer.hpp
 * 2022-10-01 K.OHWADA
 */

#include <boost/format.hpp>
#include "sha1.hpp"
#include "base64.hpp"


// prototype
std::string ws_build_response(std::string accept_key);
std::string gen_accept_key(std::string seckey);


/**
 *  build_response
 */
std::string ws_build_response(std::string accept_key)
{

    const std::string FORMAT(
"HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: %s\r\n\r\n");

    auto response =
    boost::str(boost::format(FORMAT) % accept_key);

    return response;
}


/**
 * gen_accept_key
 */
std::string gen_accept_key(std::string seckey)
{

	const std::string GUID(
"258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

    std::string text = seckey + GUID;

    auto hash = 
    get_sha1_hash( text.c_str(), text.size() );

    std::vector<char> vec(20);

    for(int i=0; i<20; i++){
        vec[i] = hash[i];
    }

    auto accept_key = encode_base64(vec);

    return accept_key;
}

