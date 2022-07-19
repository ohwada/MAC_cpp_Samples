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

#ifndef _CURL_
#define _CURL_

#include <vector>
#include <string>

#include <curl/curl.h>
#include "export_cfg.hpp"
#define nullptr 0

namespace cURL {
static const int CURL_MAX_REDIRECTS = 10;

class GlobalState {
 public:
  GlobalState();
  ~GlobalState();

 private:
  GlobalState(const GlobalState& globalState) {}  // disallow copying
};

class EasyInterface {
 public:
  EasyInterface(const std::string& url, const std::string& etag,
                bool compress = false);
  ~EasyInterface();

  const std::string& GetResponseData() const;
  const std::vector<std::string>& GetResponseHeaders() const;
  long PerformRequest();
  std::string GetResponseEtag() const;
  void SetProgressOn();
  const char* GetErrors() {
    return m_errorBuffer;
  };

 private:
  EasyInterface(const EasyInterface& easy)
      : m_curlHandle(nullptr) {}  // disallow copying
  static size_t WriteFunction(void* data, size_t mult, size_t size,
                              void* state);
  static size_t HeaderFunction(void* data, size_t mult, size_t size,
                               void* state);
  long GetResponseCode() const;
  void HandleWriteData(const char* data, const size_t dataSize);
  void HandleHeaderData(const char* data, const size_t dataSize);

 private:
  CURL* const m_curlHandle;
  const std::string m_url;
  curl_slist* m_requestHeaders;
  std::string m_responseData;
  std::vector<std::string> m_responseHeaders;
  char m_errorBuffer[CURL_ERROR_SIZE];
};
}
#endif
