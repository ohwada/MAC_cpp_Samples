/**
 * Gmail API Sample
 * 2020-07-01 K.OHWADA
 */

// get message list with Google API
// display one message

// reference : https://qiita.com/ryurock/items/4b063372ede81780c3c8


// this app runs in 4 steps
// 1.  obtain Authorization Code with user consent 
// 2. get Refresh Token using Authorization Code
// 3. get a new Access Token using a Refresh Token
// 4. access Gmail API server using Access Token
// https://developers.google.com/identity/protocols/OAuth2


#include <iostream>
#include <string>
#include <vector>
#include "access_token.hpp"
#include "gmail_fetch.hpp"
#include "gmail_attchment.hpp"
#include "menu.hpp"
#include "msg_part.hpp"



using namespace std;


/**
 * main
 */
int main(int argc, char* argv[])
{

    const string FILE_REFRESH( "refresh_token_readonly.json" );

    int mode = 2; // online
    int limit = 10;
    int mode_verbose = 1; // list

   if(argc == 4){
       mode =  stoi( argv[1] );
        limit =  stoi( argv[2] );
       mode_verbose =  stoi( argv[3] );
    } else {
        cout << "usage: " << argv[0] << " [mode ][limit] [verbose]" << endl;
    }


    bool is_new_access_token = false;
    bool is_new_list = false;
    bool is_new_msg = false;

    bool verbose_access_token = false;
    bool verbose_list = false;
    bool verbose_msg = false;

    bool verbose_parse = false;


    switch(mode){
        case 0:
            cout << "mode : offline" << endl;
            is_new_access_token = false;
            is_new_list = false;
            is_new_msg = false;
            break;
        case 1:
            cout << "mode : cache" << endl;
            is_new_access_token = true;
            is_new_list = false;
            is_new_msg = false;
            break;
        case 2:
            cout << "mode : online" << endl;
            is_new_access_token = true;
            is_new_list = true;
            is_new_msg = true;
            break;
      default:
            cout << "verbose must e 0, 1,or 2" << endl;
    }
 

    switch(mode_verbose){
        case 0:
            cout << "verbose : all off" << endl;
            verbose_access_token = false;
            verbose_list = false;
            verbose_msg = false;
            break;
      case 1:
            cout << "verbose : list" << endl;
          verbose_access_token = false;
            verbose_list = true;
            verbose_msg = false;
            break;
      case 2:
            cout << "verbose : all on" << endl;
          verbose_access_token = true;
            verbose_list = true;
            verbose_msg = true;
            break;
      default:
            cout << "verbose must e 0, 1,or 2" << endl;
    }



// get access token

    string access_token;
    string error;
    bool is_access_save = true;
    
if(is_new_access_token){

    bool ret1 = getNewAccessToken( 
    SCOPE_READONLY, 
    FILE_REFRESH,
    access_token, 
    error,
    is_access_save, verbose_access_token);

    if( ret1 ){
        cout <<  "access_token: " << access_token << endl;
    } else {
        cout << "getNewAccessToken: " << error << endl;
        return EXIT_FAILURE;
    }

}

// get message list

    std::string list_response;
    bool ret2 = getListResponse(is_new_list, access_token, list_response, verbose_list);

    if( !ret2 ) {
            cout << "getListResponse faild" << endl;
            return EXIT_FAILURE;
    }

// get  id list

    vector<string> vec_list;

    bool ret3 = 
    parseListResponseJson( list_response, vec_list, error, verbose_parse); 

    if( !ret3 ){
        cout << error << endl;
        return EXIT_FAILURE;
    }

    int msg_total = vec_list.size();  
    cout << "You have " << msg_total << " mails" << endl;


// fetch message

    vector<string> msg_json_list;
    vector<struct MailMessage> msg_list;

    int fetch_num = (msg_total > limit)? limit: msg_total;

for(int i=0; i<fetch_num; i++)
{
    string id = vec_list[i];
    cout << i << " ) id: " << id << endl;

    std::string msg_response;
    bool ret4 = getMsgResponse(is_new_msg, id, access_token, msg_response, verbose_msg);

    if(ret4) {
        msg_json_list.push_back(msg_response);
    } else {
        continue;
    }

    struct MailMessage msg;

    bool ret5 = parseMessageResponseJson( msg_response, 
msg, error, verbose_parse) ;

    if( ret5 ){
        msg_list.push_back(msg);
    } else {
        cout << error << endl;
    }

} // for

    cout << endl;

 int msg_size = msg_list.size();

while(true)
{
    bool is_download = false;
    std::string msg_id;
    struct MailPart part;

    int choice = printHeaderMenu( msg_list );
    if(choice == 0){
        cout << "goodby" << endl;
        break;
    }

    int index = choice -1;
    if( (index >= 0) && (index < msg_size) ){
        auto msg = msg_list[index];
        printMailMessage(msg);

        msg_id = msg.id;
        vector<struct MailPart> parts = msg.parts;
        int part_size = parts.size();
        if (part_size >0) {
            cout << endl;
            cout << "this mail has " << part_size << " parts" << endl;
            int part_choice = printMailPartMenu( parts );
            if (part_choice == 0) {
                continue;
            }

            int part_index = part_choice -1;
            if( (part_index >= 0) && (part_index < part_size) ){
                part = parts[part_index];
 
                if ( hasAttachmentId(part) ) {
                        is_download = true;
                } else if ( isTextPlain(part) ) {
                        printMailPartBody(part);
                }

            }
        }
    }

    if(is_download){
        bool is_verbose_attach = true;
        downloadAttachment(  access_token, msg_id, part, is_verbose_attach );

    }

    enterReturnKey();

} // while

	return EXIT_SUCCESS;
}



// Connected to www.googleapis.com
// saved to: list_response.json
// You have 100 mails
// Connected to www.googleapis.com
// saved to: mail_1753fc0c1147.json
// id: 1753fc0c1147
// subject: hoge


