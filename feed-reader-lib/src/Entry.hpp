// change log
// 2022-06-01 K.OHWADA
// xercesc_2_8 to xercesc_3_2
// added <map>

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

#ifndef _FEEDREADER_ENTRY_
#define _FEEDREADER_ENTRY_

#include <vector>
#include <string>
#include <map>

#include <boost/date_time/posix_time/ptime.hpp>

#include <xercesc/dom/DOMNode.hpp>

namespace FeedReader {
static const std::string XERCESC_EMPTY_NODE_NAME = "#text";

class FEED_EXPORT Entry {
 private:
  typedef std::map<std::string, std::string> EntryElements;
  EntryElements m_entryElements;

 public:
  std::string UniqueId;
  boost::posix_time::ptime Published;
  bool IsLive;

 private:
  void ParseNodeData(const ::xercesc_3_2::DOMNode* const entryNode);

 public:
  Entry(const xercesc_3_2::DOMNode* const entryNode);
  Entry(const Entry& other);
  Entry& operator=(const Entry& other);

  const std::string& operator[](const std::string& node) const;
  void Print(std::ostream& os) const;

  // iterator interface to entry elements
  typedef EntryElements::const_iterator entry_element_iterator;
  typedef EntryElements::const_reverse_iterator reverse_entry_element_iterator;

  entry_element_iterator begin_entry_elements() const {
    return m_entryElements.begin();
  }
  entry_element_iterator end_entry_elements() const {
    return m_entryElements.end();
  }
  reverse_entry_element_iterator rbegin_entry_elements() const {
    return m_entryElements.rbegin();
  }
  reverse_entry_element_iterator rend_entry_elements() const {
    return m_entryElements.rend();
  }

  int num_entry_elements() const { return (int)m_entryElements.size(); }
};
}

#endif
