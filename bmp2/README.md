bmp2
===============

bmp Sample <br/>
read and write bmp format Image File <br/>

### supported format
 - 8 bit index
 - 16 bit uncompressed
 - 24 bit uncompressed
 - 32 bit uncompressed


## test_copy.cpp
read image file <br/>
write image file as copy <br/>

### build sample code 
% g++ test_copy.cpp bmp.c  image.c parse_filename.cpp -o copy  -std=c++11 <br/>

### run sample code 
Usage: copy \< inputImageFilename \>  <br/>
ex)
% ./copy ./images/vegitables.bmp <br/>

### result 
display as below <br/>
bmp : copy <br/>
bmp header: biBitCount = 32 , biCompression= 0  <br/>
width:  512 <br/>
height: 512 <br/>
type:   2 <br/>
pnum:   0 <br/>
palette:0x0 <br/>
saved Image : vegitables_copy.bmp <br/>
saved Image : vegitables_gray.bmp <br/>

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp2/result/vegitables_gray.bmp" width="300" /><br/>

## test_gtk.cpp
read image file <br/>
show image in GTK window <br/>

### build sample code
- require gtk <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/GTK

 % g++ test_gtk.cpp bmp.c  image.c parse_filename.cpp -o gtk -std=c++11  `pkg-config --cflags --libs gtk+-2.0`

### run sample code 
Usage: gtk \< inputImageFilename \>  <br/>
ex)
% ./gtk ./images/vegitables.bmp <br/>

### result 
display as below <br/>
bmp : gtk <br/>
bmp header: biBitCount = 32 , biCompression= 0  <br/>
color type: RGB  <br/>
loadImage: ./images/vegitables.bmp ( 512 x 512 ) <br/>


read image file <br/>
show image in GTK window <br/>  
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp2/result/screenshot_vegitables.png" width="300" /><br/>


## test_write.cpp
write test pattern to image file <br/>

### build sample code
% g++ test_write.cpp bmp.c  image.c pixels.c  -o write -std=c++11


### run sample code 
Usage: write [size] [scale] [alpha]
ex)
 ./write 2 256 0


### result 
display as below <br/>
bmp : write <br/>
saved Image : test_2_256_b24.bmp <br/>

write test pattern to image file <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/bmp/result/test_2_256_b24.bmp" width="300" /><br/>

### Reference <br/>
- https://github.com/ohmae/ImageIO

