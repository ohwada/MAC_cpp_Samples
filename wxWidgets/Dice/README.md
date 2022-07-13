# wxwidgets: Dice

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/wxwidgets/Dice/scrrenshots/dice.png" width="300" /> <br/>

shows how to create a wxGLCanvas and wxGLContext. <br/>

original : https://github.com/gammasoft71/Examples_wxWidgets/tree/master/src/OpenGL/Dice <br/>

## Source

[Dice.cpp](Dice.cpp)

[CMakeLists.txt](CMakeLists.txt)

## Build and run

To build this project, open "Terminal" and type following lines:

### Windows :

``` shell
mkdir build && cd build
cmake .. 
start Dice.sln
```

Select Dice project and type Ctrl+F5 to build and run it.

### macOS :

``` shell
mkdir build && cd build
cmake .. -G "Xcode"
open ./Dice.xcodeproj
```

Select Dice project and type Cmd+R to build and run it.

### Linux with Code::Blocks :

``` shell
mkdir build && cd build
cmake .. -G "CodeBlocks - Unix Makefiles"
xdg-open ./Dice.cbp > /dev/null 2>&1
```

Select Dice project and type F9 to build and run it.

### Linux :

``` shell
mkdir build && cd build
cmake .. 
cmake --build . --config Debug
./Dice
```
