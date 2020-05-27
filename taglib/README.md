taglib
===============

taglib Sample <br/>
show id3tag in mp3 file <br/>

taglib  <br/>
a library for reading and editing the meta-data of several popular audio formats. Currently it supports both ID3v1 and ID3v2 for MP3 files <br/>
https://taglib.org/  <br/>

### install taglib
% brew install taglib <br/>
https://libraries.io/homebrew/taglib <br/>

## show_tags.cpp <br/>
show id3 tags of mp3 file <br/>

### build sample code
% g++ show_tags.cpp -o show `pkg-config --cflags --libs taglib_c`  <br/>

### run sample code 
Usage: " <<  ./show  << " \< mp3File \> <br/>
ex)  <br/>
%  ./show ./media/Beethoven-Symphony-No5-1st.mp3 <br/>  

display as below <br/>
Title: ベートーヴェン：交響曲第5番 ハ短調 Op.67 「運命」 第1楽章 [ 新録音2012 ]
Artist: クラシック名曲サウンドライブラリー

## get_picture.cpp <br/>
get album picture in mp3 file <br/>

### build sample code
% g++ get_picture.cpp parse_filename.cpp -o get `pkg-config --cflags --libs taglib_c` <br/>

### run sample code 
Usage: " <<  ./get  << " \< mp3File \> <br/>
ex)  <br/>
./get ./media/Nathaniel_Wyvern_Infiltrators.mp3 
 <br/>  

saved: Nathaniel_Wyvern_Infiltrators.jpg  <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/taglib/result/Nathaniel_Wyvern_Infiltrators.jpg" width="300" /> <br/>

### Reference <br/>
- https://taglib.org/

