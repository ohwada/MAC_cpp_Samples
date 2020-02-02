FreeImage
===============

FreeImage Sample <br/>
read and write Image File using FreeImage  <br/>

### install FreeImage
% brew install freeimage <br/>

### build sample code 
% g++ read_write_image.cpp parse_filename.cpp -o read_write_image -std=c++11 -I/usr/local/Cellar/freeimage/3.18.0/include/ -L/usr/local/Cellar/freeimage/3.18.0/lib/ -lfreeimage <br/>

### run sample code 
% ./read_write_image ./images/vegetables.jpg <br/>

### result 
read image file <br/>  
ex ) vegetables.jpg <br/>
and write to output file  <br/>
 ex ) vegetables_gray.jpg <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/FreeImage/result/vegetables_gray.jpg" width="300" /><br/>

### Reference <br/>
- http://freeimage.sourceforge.net/  <br/>
- http://downloads.sourceforge.net/freeimage/FreeImage3180.pdf  <br/>


