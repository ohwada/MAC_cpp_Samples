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

#ifndef _FEEDREADER_FEED_
#define _FEEDREADER_FEED_

#include <vector>
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include "Curl.hpp"
#include "XmlGlobalState.hpp"
#include "Entry.hpp"
#include "FeedConfig.hpp"

namespace FeedReader {
typedef std::vector<Entry> Entries;

// exception
class FEED_EXPORT feed_exception : public std::runtime_error {
 public:
  explicit feed_exception(const std::string& what) : std::runtime_error(what) {}
  virtual ~feed_exception() throw() {}
};

class FEED_EXPORT Feed {
 public:
  typedef std::map<std::string, std::string> FeedElements;
  explicit Feed(const std::string& url = std::string(),
                const FeedConfig& feedConfig = FeedConfig());
  ~Feed();

 public:
  const std::string& operator[](const std::string& node) const;
  const std::string& GetUrl() const;
  const Entries& GetEntries() const;
  const ::boost::posix_time::ptime& GetLastChecked() const;
  void SetValidity(bool valid);
  void SetFeedFormat(const FeedFormat& format);
  void CheckFeed();
  const FeedConfig& GetFeedConfig() { return m_feedConfig; }

  // iterator interface to entries
  typedef Entries::const_iterator entry_iterator;
  typedef Entries::const_reverse_iterator reverse_entry_iterator;

  entry_iterator begin_entries() const { return m_entries.begin(); }
  entry_iterator end_entries() const { return m_entries.end(); }
  reverse_entry_iterator rbegin_entries() const { return m_entries.rbegin(); }
  reverse_entry_iterator rend_entries() const { return m_entries.rend(); }

  int num_entries() const { return (int)m_entries.size(); }

  // iterator interface to feed elements
  typedef FeedElements::const_iterator feed_element_iterator;
  typedef FeedElements::const_reverse_iterator reverse_feed_element_iterator;

  feed_element_iterator begin_feed_elements() const {
    return m_feedElements.begin();
  }
  feed_element_iterator end_feed_elements() const {
    return m_feedElements.end();
  }
  reverse_feed_element_iterator rbegin_feed_elements() const {
    return m_feedElements.rbegin();
  }
  reverse_feed_element_iterator rend_feed_elements() const {
    return m_feedElements.rend();
  }

  int num_feed_elements() const { return (int)m_feedElements.size(); }

  // control
  static void Initialize();

 private:
  void CreateEntries(const std::string& feedData);
  void AddEntryToList(const Entry& entry);

 private:
  FeedElements m_feedElements;
  std::string m_etag;
  std::string m_url;
  std::string m_feedData;
  Entries m_entries;
  boost::posix_time::ptime m_lastChecked;
  static bool m_initialized;
  static boost::recursive_mutex m_stateMutex;
  FeedFormat m_format;
  bool m_valid;
  FeedConfig m_feedConfig;
};
}
#endif
