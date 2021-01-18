#pragma once
/**
 * vmime sample
 * 2020-07-01 K.OHWADA
 */

// header for create mail

#include <iostream>
#include <string>

#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"

#include "msg_build.hpp"
#include "msg_write.hpp"

// constant
const std::string TO("taro@example.com");
const std::string FROM("jiro@exsample.com");
