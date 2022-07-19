// change log
// 2022-06-01 K.OHWADA

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

#ifndef _FEEDREADER_FEEDVALIDATOR_
#define _FEEDREADER_FEEDVALIDATOR_

#include <string>
#include <sstream>

#include "Feed.hpp"

// this is the size of the standard header placed by all xsl templates:
//
static const int XML_HEADER_SIZE = 42;

namespace FeedReader {
class FeedValidator {
 public:
  FeedValidator(const std::string& feedData, Feed& feed);

  void Validate(std::string& results);

 private:
  void ValidateFeedFormat(const std::string& xslPath, FeedFormat feedFormat,
                          std::string& results);
  void TransformFeed(std::stringstream& xslStream, std::string& results);
  bool ValidateFeed(const std::string& feed) const;

 private:
  const std::string& m_feedData;
  Feed& m_feed;
  bool m_validationValid;
};
}

#endif
