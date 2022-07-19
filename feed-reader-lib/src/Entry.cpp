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
#include "Entry.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include "Feed.hpp"

namespace FeedReader {
Entry::Entry(const xercesc_3_2::DOMNode* const entryNode)
    : UniqueId(), Published(boost::date_time::min_date_time), IsLive(true) {
  ParseNodeData(entryNode);
}

Entry::Entry(const Entry& other) {
  UniqueId = other.UniqueId;
  Published = other.Published;
  IsLive = other.IsLive;
  m_entryElements = other.m_entryElements;
}

Entry& Entry::operator=(const Entry& other) {
  if (this != &other) {
    UniqueId = other.UniqueId;
    Published = other.Published;
    IsLive = other.IsLive;
    m_entryElements = other.m_entryElements;
  }
  return *this;
}

void Entry::ParseNodeData(const xercesc_3_2::DOMNode* const entryNode) {
  const xercesc_3_2::DOMNodeList* const children = entryNode->getChildNodes();
  for (XMLSize_t i = 0, listLength = children->getLength(); i < listLength;
       ++i) {
    const xercesc_3_2::DOMNode* const node = children->item(i);
    const std::string nodeName = XmlCharsToStdString(node->getNodeName());
    const std::string textContent = XmlCharsToStdString(node->getTextContent());

    if (nodeName == XERCESC_EMPTY_NODE_NAME) {
      continue;
    }
    if (xercesc_3_2::XMLString::equals(nodeName.c_str(), "entryUniqueId")) {
      UniqueId = textContent;
      m_entryElements["entryUniqueId"] = textContent;
    } else if (xercesc_3_2::XMLString::equals(nodeName.c_str(),
                                              "publishDateTime")) {
      Published = boost::posix_time::microsec_clock::universal_time();
      m_entryElements["publishDateTime"] = textContent;
    } else {
      m_entryElements[nodeName] = textContent;
    }
  }

  if (UniqueId.empty()) {
    UniqueId = m_entryElements["url"];
  }
}

const std::string& Entry::operator[](const std::string& node) const {
  EntryElements::const_iterator itr = m_entryElements.find(node);
  if (itr == m_entryElements.end()) {
    static const std::string empty = "";
    return empty;
  }

  return itr->second;
}

void Entry::Print(std::ostream& os) const {
  for (EntryElements::const_iterator itr = m_entryElements.begin();
       itr != m_entryElements.end(); itr++) {
    os << itr->first << ": '" << itr->second << "'" << std::endl;
  }
}
}
