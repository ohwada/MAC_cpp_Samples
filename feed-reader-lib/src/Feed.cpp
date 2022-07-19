// change log
// 2022-06-01 K.OHWADA
// xercesc_2_8 to xercesc_3_2
// auto_ptr<cURL::GlobalState>' is deprecated
// auto_ptr to unique_ptr

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

#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "Curl.hpp"
#include "StdAfx.hpp"
#include "Feed.hpp"
#include "Utils.hpp"
#include "Validator.hpp"

namespace FeedReader {
bool Feed::m_initialized = false;
boost::recursive_mutex Feed::m_stateMutex;

Feed::Feed(const std::string& url, const FeedConfig& feedConfig)
    : m_etag(),
      m_url(url),
      m_lastChecked(boost::date_time::min_date_time),
      m_format(UNKNOWN_FEED_TYPE),
      m_valid(false),
      m_feedConfig(feedConfig) {
  m_entries.reserve(20);
}

Feed::~Feed() {}

const std::string& Feed::operator[](const std::string& node) const {
  FeedElements::const_iterator itr = m_feedElements.find(node);
  if (itr == m_feedElements.end()) {
    static const std::string empty = "";
    return empty;
  }

  return itr->second;
}

const std::string& Feed::GetUrl() const { return m_url; }

const Entries& Feed::GetEntries() const { return m_entries; }

const boost::posix_time::ptime& Feed::GetLastChecked() const {
  return m_lastChecked;
}

void Feed::CheckFeed() {
  m_lastChecked = boost::posix_time::microsec_clock::universal_time();
  cURL::EasyInterface easy(m_url, m_etag);
  switch (easy.PerformRequest()) {
    case 200: {
      m_etag = easy.GetResponseEtag();
      FeedValidator validator(easy.GetResponseData(), *this);
      validator.Validate(m_feedData);
      m_valid = true;
      if (m_valid) {
        CreateEntries(m_feedData);
      }
      return;
    }
    case 304: {
      m_valid = true;
      return;
    }
    default: {
      m_entries.clear();
      m_valid = false;
    }
  }
}

void Feed::CreateEntries(const std::string& feedData) {
  const xercesc_3_2::MemBufInputSource input(
      reinterpret_cast<const XMLByte*>(feedData.c_str()), feedData.size(), "");
  xercesc_3_2::XercesDOMParser parser;
  parser.setValidationScheme(xercesc_3_2::XercesDOMParser::Val_Never);
  parser.parse(input);
  if (!parser.getDocument()->hasChildNodes() ||
      !parser.getDocument()->getChildNodes()->item(0)->hasChildNodes()) {
    return;
  }

  const xercesc_3_2::DOMNodeList* const children =
      parser.getDocument()->getChildNodes()->item(0)->getChildNodes();
  for (XMLSize_t i = 0, listLength = children->getLength(); i < listLength;
       ++i) {
    const xercesc_3_2::DOMNode* const node = children->item(i);
    const std::string nodeName = XmlCharsToStdString(node->getNodeName());

    if (nodeName == XERCESC_EMPTY_NODE_NAME) {
      continue;
    }
    if (xercesc_3_2::XMLString::equals(nodeName.c_str(), "entry")) {
      AddEntryToList(node);
    } else {
      const std::string textContent =
          XmlCharsToStdString(node->getTextContent());
      m_feedElements[nodeName] = textContent;
    }
  }
}

void Feed::AddEntryToList(const Entry& entry) {
  const Entries::iterator findResult =
      std::find_if(m_entries.begin(), m_entries.end(),
                   EntryUniqueIdPredicate(entry.UniqueId));
  if (findResult == m_entries.end()) {
    m_entries.push_back(entry);
  } else {
    *findResult = entry;
  }
}

void Feed::Initialize() {
  boost::recursive_mutex::scoped_lock lock(m_stateMutex);
  if (!Feed::m_initialized) {

//auto_ptr<cURL::GlobalState>' is deprecated
    // static std::auto_ptr<cURL::GlobalState> curlGlobal(new cURL::GlobalState());
    // static std::auto_ptr<XmlGlobalState> xmlGlobal(new XmlGlobalState());
    static std::unique_ptr<cURL::GlobalState> curlGlobal(new cURL::GlobalState());
    static std::unique_ptr<XmlGlobalState> xmlGlobal(new XmlGlobalState());


    Feed::m_initialized = true;
  }
}

void Feed::SetValidity(bool valid) { m_valid = valid; }

void Feed::SetFeedFormat(const FeedFormat& format) { m_format = format; }
}
