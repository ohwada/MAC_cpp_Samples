# wxwidgets: MessageDialog

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/wxwidgets/MessageDialog/scrrenshots/messageDialog.png" width="300" /> <br/>

Shows how to create a MessageDialog dialog with wxMessageDialog. <br/>

original: https://github.com/gammasoft71/Examples_wxWidgets/tree/master/src/Dialogs/MessageDialog <br/>

## Source

[MessageDialog.cpp](MessageDialog.cpp)

[CMakeLists.txt](CMakeLists.txt)

## Build and run

To build this project, open "Terminal" and type following lines:

### Windows :

``` shell
mkdir build && cd build
cmake .. 
start MessageDialog.sln
```

Select MessageDialog project and type Ctrl+F5 to build and run it.

### macOS :

``` shell
mkdir build && cd build
cmake .. -G "Xcode"
open ./MessageDialog.xcodeproj
```

Select MessageDialog project and type Cmd+R to build and run it.

### Linux with Code::Blocks :

``` shell
mkdir build && cd build
cmake .. -G "CodeBlocks - Unix Makefiles"
xdg-open ./MessageDialog.cbp > /dev/null 2>&1
```

Select MessageDialog project and type F9 to build and run it.

### Linux :

``` shell
mkdir build && cd build
cmake .. 
cmake --build . --config Debug
./MessageDialog
```
