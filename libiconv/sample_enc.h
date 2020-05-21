/**
 * iconv Sample
 * 2020-03-01 K.OHWADA
 */

// reference : http://ash.jp/code/unitbl21.htm

    const char EXPECT_UTF8[] = 
    { (char)0xE3, (char)0x81, (char)0x82,  //あ
    (char)0xE3, (char)0x81, (char)0x84,  // い
    (char)0xE3, (char)0x81, (char)0x86, // う
    (char)0xE3, (char)0x81, (char)0x88,  // え
    (char)0xE3, (char)0x81, (char)0x8A,  // お
    0 };  // string end 

    const char SAMPLE_SJIS[] = 
    { (char)0x82, (char)0xA0, //あ
    (char)0x82, (char)0xA2,  // い
    (char)0x82, (char)0xA4,  // う
    (char)0x82, (char)0xA6, // え
    (char)0x82, (char)0xA8, }; // お
     const int SAMPLE_SJIS_SIZE = 10;

    const char SAMPLE_EUCJP[] = 
    { (char)0xA4, (char)0xA2,//あ
    (char)0xA4, (char)0xA4, // い
    (char)0xA4, (char)0xA6, // う
    (char)0xA4, (char)0xA8, // え
    (char)0xA4, (char)0xAA }; // お
     const int SAMPLE_EUCJP_SIZE = 10;

    const char SAMPLE_UTF16BOM[] = 
    { (char)0xFF,(char)0xFE,(char)0x42,(char)0x30, //  あ
    (char)0xFF,(char)0xFE,(char)0x44,(char)0x30, //  い
    (char)0xFF,(char)0xFE,(char)0x46,(char)0x30, //  う
    (char)0xFF,(char)0xFE,(char)0x48,(char)0x30, //  え
    (char)0xFF,(char)0xFE,(char)0x4A,(char)0x30 };  //  お
     const int SAMPLE_UTF16BOM_SIZE = 20;

    const char SAMPLE_UTF16BE[] = 
    { (char)0x30, (char)0x42, //あ
    (char)0x30, (char)0x44, // い
    (char)0x30, (char)0x46, // う
    (char)0x30, (char)0x48, // え
    (char)0x30, (char)0x4A }; // お
     const int SAMPLE_UTF16BE_SIZE = 10;

 const char SAMPLE_UTF16LE[] = 
    { (char)0x42,(char)0x30, //  あ
    (char)0x44,(char)0x30, //  い
    (char)0x46,(char)0x30, //  う
    (char)0x48,(char)0x30, //  え
    (char)0x4A,(char)0x30 };  //  お
    const int SAMPLE_UTF16LE_SIZE = 10;

    const char SAMPLE_UTF32BE[] = 
    { (char)0x0,(char)0x0,(char)0x30,(char)0x42, //  あ
    (char)0x0,(char)0x0,(char)0x30,(char)0x44, //  い
    (char)0x0,(char)0x0,(char)0x30,(char)0x46, //  う
    (char)0x0,(char)0x0,(char)0x30,(char)0x48, //  え
    (char)0x0,(char)0x0,(char)0x30,(char)0x4A };  //  お
    const int SAMPLE_UTF32BE_SIZE = 20;

// sample : include 0
 const char SAMPLE_UTF16BE_2[] = 
    { (char) 0 , (char) 75 ,  //  u
    (char) 0 , (char) 74 ,  //  t
    (char) 0 , (char) 66 ,  //  f
    (char) 0 , (char) 31 ,  //  1
    (char) 0 , (char) 36 }; //  6
const int SAMPLE_UTF16BE_2_SIZE = 10;

// sample : include 0
 const char SAMPLE_UTF16LE_2[] = 
    { (char) 75 , (char) 0 ,  //  u
    (char) 74 , (char) 0 ,  //  t
    (char) 66 , (char) 0 ,  //  f
    (char) 31 , (char) 0 ,  //  1
    (char) 36 , (char) 0  };  //  6
  const int SAMPLE_UTF16LE_2_SIZE = 10;