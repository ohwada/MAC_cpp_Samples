/**
 * 3des.cpp
 * 2022-06-01 K.OHWADA
 */


// encryption and decryption with triple DES
// reference : https://yut.hatenablog.com/entry/20131115/1384471222

#include <iostream>
#include "modes.h"
#include "filters.h"
#include "hex.h"
#include "des.h"

using namespace std;
using namespace CryptoPP;


/**
 * main
 */
int main(int argc, char* argv[]) 
{
const string PLAIN("the quick brown fox jumps over the lazy dog");

	string cipher, encoded, decoded, recovered;
	ECB_Mode<DES>::Encryption encctx;
        byte key[DES::DEFAULT_KEYLENGTH];
	memcpy( key, "Soul Gem", DES::DEFAULT_KEYLENGTH );
	encctx.SetKey( key, DES::DEFAULT_KEYLENGTH );

	// ciper
	StringSource( PLAIN, true, 
        new StreamTransformationFilter( encctx,
            new StringSink( cipher )
			//StreamTransformationFilter::PKCS_PADDING
                       //StreamTransformationFilter::ZEROS_PADDING
        )      
        ); 
	//cout << "cipher text: " << cipher << endl;	

	// hex encode
	StringSource( cipher, true,
    	new HexEncoder( 
        	new StringSink( encoded )
    	)
	);

	// cout << "encode text: " << encoded << endl;	
	
        // hex decode
	StringSource( encoded, true,
    	new HexDecoder( 
        	new StringSink( decoded )
    	)
	);

	// cout << "decode text: " <<  decoded << endl;	

	// ciper decode
	ECB_Mode<DES>::Decryption decctx;
	decctx.SetKey( key, DES::DEFAULT_KEYLENGTH );
	StringSource( decoded, true, 
        new StreamTransformationFilter( decctx,
            new StringSink( recovered )
			//StreamTransformationFilter::PKCS_PADDING
			//StreamTransformationFilter::ZEROS_PADDING
        )
        );

	cout <<  PLAIN << endl;
	cout << "recovered: " << recovered << endl;

if(PLAIN == recovered){
	cout << "successful" << endl;
} else {
	cout << "unmtch" << endl;
}

	return 0;
}

// the quick brown fox jumps over the lazy dog
// recovered: the quick brown fox jumps over the lazy dog
// successful

