/* feed_reader_tester.cpp */

#include <iostream>
#include "export_cfg.hpp"
#include "Feed.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	string feed_url;

	// validate arguments
	if (argc == 2) 
	{
		feed_url = argv[1];
	}
	else
	{
		cerr << "usage: FeedReaderTester.exe <feed_url>\n";
		return 1;
	}

	try
	{
		// init once per process, needed by xerces and curl
		FeedReader::Feed::Initialize();

		// create custom FeedConfig with the path of the xsl files
		// it is possible no to pass a FeedConfig instance to FeedReader,
		// in such a case xsl files will be searched for in the working dir.
		FeedReader::FeedConfig feedConfig("../xsl");

		// optionally, customize the list of xsl files and feed types 
		// in this commented case we extend support for one nonstandard feed type.
		// feedConfig.m_feed_types.clear();
		// feedConfig.m_feed_types.push_back(std::make_pair("BroadCatching_02_xsl.txt", "BroadCatching02"));

		// create feed reader instance
		// it takes a URL of the feed we wish to fetch, 
		// and optionaly a FeedConfig instance.
		FeedReader::Feed feedReader(feed_url,feedConfig);

		// check feed - retrieves and parses results.
		// we can repeat this step as often as we wish to
		// update feed results, but it is recommended to 
		// take the value of the TTL feed element into account.
		// when available, the TTL element is a way for the server
		// to tall us the minimal recommended refresh interval.
		feedReader.CheckFeed();

		// get results
		cout << "----------Feed---------" << endl
		     << "URL: '" << feedReader.GetUrl() << "'" << endl;
		// print elements (feed level information)
		for (FeedReader::Feed::feed_element_iterator fitr = feedReader.begin_feed_elements();
			fitr != feedReader.end_feed_elements(); fitr++)
		{
			std::cout << fitr->first << ":	'" <<  fitr->second << "'" << endl;
		}

		// print items(post level information)
		for (FeedReader::Feed::entry_iterator itr = feedReader.begin_entries();
			itr != feedReader.end_entries(); itr++)
		{
			std::cout << "Item ID: '"	<< itr->UniqueId	<< "'" << endl
				<< "IsLive: '"	<< itr->IsLive		<< "'" << endl;
			itr->Print(cout);
		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << "\n";
	}
	catch (...)
	{
		cout << "Unknown exception." << "\n";
	}

	return 0;
}