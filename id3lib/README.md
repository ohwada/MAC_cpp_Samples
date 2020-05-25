id3lib
===============

id3lib Sample <br/>
show id3tag in mp3 file <br/>

id3lib  <br/>
development library for reading, writing, and manipulating ID3v1 and ID3v2 tags. <br/>
http://id3lib.sourceforge.net/  <br/>

### Note :
id3lib NOT support id3 v2.4.0 <br/>
https://sourceforge.net/p/id3lib/bugs/203/ <br/>

### install id3lib
% brew install id3lib <br/>
https://formulae.brew.sh/formula/id3lib <br/>

### get c_wrapper.cpp
https://github.com/jmckaskill/qsmp/blob/master/id3lib/src/c_wrapper.cpp <br/>

## show_id3tags.cpp <br/>
show id3 tags of mp3 file with libiconv <br/>

### build sample code
- reqire libiconv  <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/libiconv <br/>

% g++ show_id3tags.cpp id3tags.cpp c_wrapper.cpp  TextEncodeConverter.cpp -o show   -std=c++11 -I/usr/local/Cellar/id3lib/3.8.3_1/include -L/usr/local/Cellar/id3lib/3.8.3_1/lib  -lid3 -I/usr/local/Cellar/libiconv/1.16/include -L/usr/local/Cellar/libiconv/1.16/lib -liconv  <br/>

### run sample code 
Usage: " <<  ./show  << " \< mp3File \>  [debug] <br/>
ex)  <br/>
%  ./show ./media/Beethoven-Symphony-No5-1st.mp3 <br/>  

display as below <br/>
id3lib Version: 3.8.3
Title: ベートーヴェン：交響曲第5番 ハ短調 Op.67 「運命」 第1楽章 [ 新録音2012 ]

## get_picture.cpp <br/>
get album picture in mp3 file <br/>

### build sample code
% g++ get_picture.cpp  id3tags.cpp c_wrapper.cpp parse_filename.cpp   -o get   -std=c++11 -I/usr/local/Cellar/id3lib/3.8.3_1/include -L/usr/local/Cellar/id3lib/3.8.3_1/lib  -lid3

### run sample code 
Usage: " <<  ./get  << " \< mp3File \> <br/>
ex)  <br/>
%  ./get ./media/Mozart-EineKleine-1st.mp3 <br/>  

saved: Mozart-EineKleine-1st.jpg  <br/>
<img src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/id3lib/result/Mozart-EineKleine-1st.jpg" width="300" /> <br/>

### Reference <br/>
- http://id3lib.sourceforge.net/

