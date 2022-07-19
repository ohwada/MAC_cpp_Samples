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

#include <fstream>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "Utils.hpp"
#include "StdAfx.hpp"
#include "Validator.hpp"
#include "MemParseHandlers.hpp"

namespace FeedReader {
FeedValidator::FeedValidator(const std::string& feedData, Feed& feed)
    : m_feedData(feedData), m_feed(feed), m_validationValid(true) {}

void FeedValidator::Validate(std::string& results) {
  try {
    const FeedConfig& feedConfig = m_feed.GetFeedConfig();
    for (FeedTypes::const_iterator itr = feedConfig.m_feed_types.begin(),
                                   eitr = feedConfig.m_feed_types.end();
         itr != eitr; ++itr) {
      ValidateFeedFormat(itr->first, itr->second, results);
      if (!results.empty()) {
        return;
      }
    }
  }
  catch (const xercesc_3_2::XMLException& e) {
    std::stringstream msg;
    msg << "An error occurred during feed parsing: '"
        << XmlCharsToStdString(e.getMessage());
    throw feed_exception(msg.str());
  }
  catch (const xercesc_3_2::DOMException& e) {
    const unsigned int maxChars = 2047;
    XMLCh errText[maxChars + 1];

    std::stringstream msg;
    msg << "DOM Error occurred during feed parsing. Code is:  " << e.code
        << ".";

    if (xercesc_3_2::DOMImplementation::loadDOMExceptionMsg(e.code, errText,
                                                            maxChars))
      msg << " Message is: " << XmlCharsToStdString(errText) << ".";
    throw feed_exception(msg.str());
  }
  m_feed.SetValidity(false);
  m_feed.SetFeedFormat("Unknown");
}

void FeedValidator::ValidateFeedFormat(const std::string& xslPath,
                                       FeedFormat feedFormat,
                                       std::string& results) {
  boost::filesystem::path fullFileName(m_feed.GetFeedConfig().m_config_path);
  fullFileName /= xslPath;

  std::ifstream xslFile(fullFileName.string().c_str(),
                        std::ios_base::binary | std::ios_base::in);
  if (!xslFile) {
    std::stringstream msg;
    msg << "FeedValidator: Unable to open XSL file: '" << xslPath << "'";
    throw feed_exception(msg.str());
  }

  std::stringstream xslStream;
  xslFile.get(*xslStream.rdbuf(), '\0');
  xslStream.seekg(std::stringstream::beg);

  TransformFeed(xslStream, results);
  if (!results.empty() && ValidateFeed(results)) {
    m_feed.SetFeedFormat(feedFormat);
    m_feed.SetValidity(true);
    return;
  }

  return;
}

void FeedValidator::TransformFeed(std::stringstream& xslStream,
                                  std::string& results) {
  std::stringstream result;
  xalanc_1_12::XalanTransformer trans;
  std::stringstream xmlStream(m_feedData);
  const xalanc_1_12::XSLTInputSource xmlIn(xmlStream);
  const xalanc_1_12::XSLTInputSource xslIn(xslStream);
  const xalanc_1_12::XSLTResultTarget xmlOut(result);

  int theResult = -1;
  theResult = trans.transform(xmlIn, xslIn, xmlOut);
  if (theResult != 0) {
    std::stringstream msg;
    msg << "An error occurred while applying XSLT transformation to feed: "
        << trans.getLastError();
    throw feed_exception(msg.str());
  }

  results = result.str();
}

bool FeedValidator::ValidateFeed(const std::string& feed) const {
  MemParseHandlers handler;
  const xercesc_3_2::MemBufInputSource input(
      reinterpret_cast<const XMLByte*>(feed.c_str()), feed.size(), "c:/");

  xercesc_3_2::XercesDOMParser parser;
  parser.setValidationScheme(xercesc_3_2::XercesDOMParser::Val_Never);
  parser.setErrorHandler(&handler);

  parser.parse(input);

  return handler.GetSuccess();
}
}
