assimp
===============

assimp sample <br/>
draw 3D model from file <br/>

assimp : <br/>
Portable library for importing many well-known 3D model formats <br/>
https://www.assimp.org/ <br/>

###  install assimp
% brew install assimp <br/>
https://formulae.brew.sh/formula/assimp <br/>

## Sample_Simple_OpenGL.c <br/>
draw 3D model from file <br/>

build sample code
gcc   Sample_Simple_OpenGL.c  -framework OpenGL  -framework GLUT   `pkg-config --cflags --libs assimp` <br/>

run sample code 
Usage:  \< file \>  <br/>
file       The input model file to load. <br/>
ex) <br/>
./a.out models/OBJ/WusonOBJ.obj <br/>

display as below <br/>
AssimpVersion: 5.0.0  <br/>
Info,  T0: Load models/OBJ/WusonOBJ.obj <br/>

draw 3D model <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/assimp/result/screenshot_wusonobj.png" width="300" /><br/>

### Reference <br/>
- https://github.com/assimp/assimp

