glm
===============

glm Sample <br/>

OpenGL Mathematics (GLM) <br/>
header only C++ mathematics library <br/>
https://glm.g-truc.net/0.9.4/api/index.html <br/>

###  install glm
% brew install glm <br/>
https://formulae.brew.sh/formula/glm <br/>


## length.cpp <br/>
 vector length <br/>
https://glm.g-truc.net/0.9.4/api/a00131.html#ga282360c8bb80b80d3c7f5bc00766d873 <br/>

build sample code<br/>
g++ length.cpp -o length  -std=c++11  `pkg-config --cflags --libs glm` <br/>

run sample code <br/>
 ./length <br/>

display as below <br/>
glm version: GLM: version 0.9.9.5 <br/>
a: 3 , 4 <br/>
length(a): 5 <br/>


## arithmetic.cpp <br/>
arithmetic operations <br/>

build sample code<br/>
g++ arithmetic.cpp -o arithmetic  -std=c++11  `pkg-config --cflags --libs glm` <br/>

run sample code <br/> 
./arithmetic <br/>

display as below <br/>
p: 2 , 3 , 4 , 5 <br/>
q: 3 , 4 , 5 , 6 <br/>
n ( operator+ ): 5 , 7 , 9 , 11 <br/>
m ( operator* ): 6 , 12 , 20 , 30 <br/>


## simplex_noise.cpp <br/>
simplex noise <br/>
https://glm.g-truc.net/0.9.4/api/a00152.html#ga5fa44c45d9b0cf67559b705c95b5dcd7 <br/>

build sample code<br/>
g++ simplex_noise.cpp -o simplex  -std=c++11  `pkg-config --cflags --libs glm` <br/>

run sample code <br/> 
./simplex <br/>

saved: simplex.pgm <br/>


## perlin_noise.cpp <br/>
perlin noise <br/>
https://glm.g-truc.net/0.9.4/api/a00152.html#gaa9f3e905afe771551512322edcec001b <br/>

build sample code<br/>
g++ perlin_noise.cpp -o perlin  -std=c++11  `pkg-config --cflags --libs glm` <br/>

run sample code <br/> 
./perlin <br/>


saved: perlin.pgm <br/>


### Reference <br/>
- https://glm.g-truc.net/0.9.4/api/index.html

