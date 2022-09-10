/**
 * json_bitcoin_parser.h
 * 2022-06-01 K.OHWADA
 */

 // Bitcoin exchange rates  
 // parse response of https:/​/​blockchain.​info

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>

const size_t BUFSIZE = 256;
const size_t NUM = 30;


/**
 * struct exchange_info
 */
struct exchange_info
{
   double delay_15m_price;
   double latest_price;
   double buying_price;
   double selling_price;
   char symbol[BUFSIZE];
};

// prototype
void parse_response(char *data);
void parse_info( json_object* obj, struct exchange_info *info);
void print_latest( struct exchange_info info );

// global
int info_num;
struct exchange_info exchange_infos[NUM];


/**
 * parse_info
 */
void parse_info( json_object* obj, struct exchange_info *info)
{
    json_object* obj_15m = json_object_object_get(obj,"15m");
     if (json_object_get_type(obj_15m) == json_type_double) {
        double delay_15m = json_object_get_double(obj_15m);
        info->delay_15m_price = delay_15m;
    }

   json_object* obj_last = json_object_object_get(obj, "last");
     if (json_object_get_type(obj_last) == json_type_double) {
        double last = json_object_get_double(obj_last);
        info->latest_price = last;
    }

 json_object* obj_buy = json_object_object_get(obj, "buy");
     if (json_object_get_type(obj_buy) == json_type_double) {
        double buy = json_object_get_double(obj_buy);
        info->buying_price = buy;
    }

 json_object* obj_sell = json_object_object_get(obj, "sell");
     if (json_object_get_type(obj_sell) == json_type_double) {
        double sell = json_object_get_double(obj_sell);
        info->selling_price = sell;
    }

 json_object* obj_symbol = json_object_object_get(obj, "symbol");
     if (json_object_get_type(obj_symbol) == json_type_string) {
            char* symbol = (char*)json_object_get_string(obj_symbol);
            // printf("symbol: %s \n", symbol);
            strcpy(info->symbol, symbol);
    }
}


/**
 * parse_response
 */
void parse_response(char *data)
{
  json_object *root = json_tokener_parse(data);

    int cnt = 0;
    json_object_object_foreach(root, key, val) {
        // printf("key: %s \n", key);
        struct exchange_info info;
        parse_info(val, &info);
        exchange_infos[cnt] = info;
        cnt ++;
} // foreach
    info_num = cnt;

}


/**
 * print_info
 */
void print_info( struct exchange_info info )
{
    printf("\n %s \n", info.symbol);
    printf("15m: %f \n", info.delay_15m_price);
    printf("latest: %f \n", info. latest_price);
    printf("buying: %f \n", info.buying_price);
    printf("selling: %f \n", info.selling_price);
}


/**
 * print_latest
 */
void print_latest( struct exchange_info info )
{
    printf("%s %.3f \n", info.symbol, info. latest_price);
  }
