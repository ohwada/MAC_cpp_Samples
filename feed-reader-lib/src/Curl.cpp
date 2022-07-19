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

#include "Curl.hpp"

#include <cstdlib>
#include <boost/algorithm/string.hpp>

namespace cURL {
GlobalState::GlobalState() { curl_global_init(CURL_GLOBAL_ALL); }

GlobalState::~GlobalState() { curl_global_cleanup(); }

EasyInterface::EasyInterface(const std::string& url, const std::string& etag,
                             bool compress)
    : m_curlHandle(curl_easy_init()),
      m_url(url),
      m_requestHeaders(nullptr),
      m_responseData(),
      m_responseHeaders() {
  m_responseHeaders.reserve(20);

  curl_easy_setopt(m_curlHandle, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(m_curlHandle, CURLOPT_NOPROGRESS, 1);
  curl_easy_setopt(m_curlHandle, CURLOPT_URL, m_url.c_str());
  curl_easy_setopt(m_curlHandle, CURLOPT_SSL_VERIFYPEER,
                   0);  // disable certificates
  curl_easy_setopt(m_curlHandle, CURLOPT_ERRORBUFFER,
                   m_errorBuffer);  // error buffer
  curl_easy_setopt(m_curlHandle, CURLOPT_FOLLOWLOCATION,
                   1);  // follow redirects
  curl_easy_setopt(m_curlHandle, CURLOPT_MAXREDIRS,
                   CURL_MAX_REDIRECTS);  // number of redirects to follow
  // curl_easy_setopt(m_curlHandle, CURLOPT_VERBOSE, 1);					//
  // VERBROSE

  if (compress) {
    curl_easy_setopt(m_curlHandle, CURLOPT_ENCODING,
                     "deflate");  // request zlib  compression
  }

  // set up a minimum transfer rate - less then a 100 bytes in 5 minutes is a
  // failure
  curl_easy_setopt(m_curlHandle, CURLOPT_LOW_SPEED_LIMIT, 100);
  curl_easy_setopt(m_curlHandle, CURLOPT_LOW_SPEED_TIME, 300);

  if (!etag.empty()) {
    std::string etagHeader("If-None-Match: ");
    etagHeader += etag;
    m_requestHeaders = curl_slist_append(m_requestHeaders, etagHeader.c_str());
    curl_easy_setopt(m_curlHandle, CURLOPT_HTTPHEADER, m_requestHeaders);
  }

  curl_easy_setopt(m_curlHandle, CURLOPT_HEADERFUNCTION,
                   &EasyInterface::HeaderFunction);
  curl_easy_setopt(m_curlHandle, CURLOPT_HEADERDATA, this);

  curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION,
                   &EasyInterface::WriteFunction);
  curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, this);
}

EasyInterface::~EasyInterface() {
  if (m_requestHeaders) curl_slist_free_all(m_requestHeaders);
  curl_easy_cleanup(m_curlHandle);
}

void EasyInterface::SetProgressOn() {
  curl_easy_setopt(m_curlHandle, CURLOPT_NOPROGRESS, 0);
}

const std::string& EasyInterface::GetResponseData() const {
  return m_responseData;
}

const std::vector<std::string>& EasyInterface::GetResponseHeaders() const {
  return m_responseHeaders;
}

long EasyInterface::PerformRequest() {
  return curl_easy_perform(m_curlHandle) == CURLE_OK ? GetResponseCode() : 0;
}

std::string EasyInterface::GetResponseEtag() const {
  for (std::vector<std::string>::const_iterator i = m_responseHeaders.begin();
       i != m_responseHeaders.end(); ++i)
    if (boost::algorithm::istarts_with(*i, "etag:"))
      return i->substr(
          6, i->size() - 8);  // subtract 2 extra bytes for the trailing CRLF
  return std::string();
}

size_t EasyInterface::WriteFunction(void* data, size_t mult, size_t size,
                                    void* state) {
  const size_t dataSize = size * mult;
  if (dataSize && state)
    reinterpret_cast<EasyInterface*>(state)
        ->HandleWriteData(reinterpret_cast<char*>(data), dataSize);
  return dataSize;
}

size_t EasyInterface::HeaderFunction(void* data, size_t mult, size_t size,
                                     void* state) {
  const size_t dataSize = size * mult;
  if (dataSize && state)
    reinterpret_cast<EasyInterface*>(state)
        ->HandleHeaderData(reinterpret_cast<char*>(data), dataSize);
  return dataSize;
}

long EasyInterface::GetResponseCode() const {
  long code = 0;
  return curl_easy_getinfo(m_curlHandle, CURLINFO_RESPONSE_CODE, &code) ==
                 CURLE_OK
             ? code
             : 0;
}

void EasyInterface::HandleWriteData(const char* data, const size_t dataSize) {
  m_responseData.append(data, dataSize);
}

void EasyInterface::HandleHeaderData(const char* data, const size_t dataSize) {
  m_responseHeaders.push_back(std::string(data, dataSize));

  data = m_responseHeaders.back().c_str();
  if (!boost::algorithm::istarts_with(data, "content-length:")) return;

  int contentLength = std::atoi(data + 16);
  if (contentLength) m_responseData.reserve(contentLength);
}
}
