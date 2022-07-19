// change log
// 2022-06-01 K.OHWADA
// xercesc_2_8 to xercesc_3_2
// xalanc_1_10 to xalanc_1_12

// original : https://github.com/purcaro/feed-reader-lib

/*

Copyright (c) 2009, Yoav Aviram
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the distribution.
* Neither the name of the author nor the names of its
contributors may be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include "StdAfx.hpp"
#include "XmlGlobalState.hpp"

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

namespace FeedReader {
XmlGlobalState::XmlGlobalState() {
  try {
    xercesc_3_2::XMLPlatformUtils::Initialize();
    xalanc_1_12::XalanTransformer::initialize();
  }
  catch (const xercesc_3_2::XMLException& xe) {
    char* message = xercesc_3_2::XMLString::transcode(xe.getMessage());
    std::cout << "Error during Xerces-c Initialization: " << message
              << std::endl;
    xercesc_3_2::XMLString::release(&message);
    throw;
  }
}

XmlGlobalState::~XmlGlobalState() {
  xalanc_1_12::XalanTransformer::terminate();
  xercesc_3_2::XMLPlatformUtils::Terminate();
}
}
