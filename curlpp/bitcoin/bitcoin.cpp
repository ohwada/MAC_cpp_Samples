/**
 * bitcoin.cpp
 * 2022-06-01 K.OHWADA
 */

// Bitcoin exchange rates

#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <map>
#include "https_write.hpp"
#include "json.hpp"

using json = nlohmann::json;


/**
 * struct exchange_info
 */
struct exchange_info
{
   double delay_15m_price;
   double latest_price;
   double buying_price;
   double selling_price;
   std::string symbol;
};


/**
 * from_json
 */
void from_json(const json& jdata, exchange_info& info)
{
   info.delay_15m_price = jdata.at("15m").get<double>();
   info.latest_price = jdata.at("last").get<double>();
   info.buying_price = jdata.at("buy").get<double>();
   info.selling_price = jdata.at("sell").get<double>();
   info.symbol = jdata.at("symbol").get<std::string>();
}


using blockchain_rates = std::map<std::string, exchange_info>;

using namespace std;


/**
 * main
 */
int main() 
{
    string url("https://blockchain.info/ticker");

	string response;
	string error;
    bool is_verify = true;
    bool is_verbose = false;

	bool ret = https_to_memory(url, response,  error,  is_verify, is_verbose);
    if(!ret){	
		cout << error << endl;
	    return EXIT_FAILURE;
    }	

    json jdata = json::parse(response);

   blockchain_rates rates = jdata;

   for (auto const & kvp : rates)
   {
      std::cout << "1BPI = " << kvp.second.latest_price 
                << " " << kvp.first << std::endl;
   } // for

    return 0;
}
