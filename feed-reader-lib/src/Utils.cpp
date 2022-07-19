// change log
// 2022-06-01 K.OHWADA
// xercesc_2_8 to xercesc_3_2

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
#include "Utils.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <xercesc/util/XMLString.hpp>

namespace FeedReader {

std::string XmlCharsToStdString(const XMLCh* const xmlChars) {
  char* stdChars = xercesc_3_2::XMLString::transcode(xmlChars);
  const std::string result = std::string(stdChars);
  xercesc_3_2::XMLString::release(&stdChars);
  return result;
}

FeedUrlPredicate::FeedUrlPredicate(const std::string& url) : _url(url) {}

bool FeedUrlPredicate::operator()(const Feed& feed) const {
  return boost::algorithm::iequals(_url, feed.GetUrl());
}

EntryUniqueIdPredicate::EntryUniqueIdPredicate(const std::string& uniqueId)
    : _uniqueId(uniqueId) {}

bool EntryUniqueIdPredicate::operator()(const Entry& entry) const {
  return boost::algorithm::iequals(_uniqueId, entry.UniqueId);
}
}
