Griefly
===========

[![Build Status](https://travis-ci.org/kremius/karya-valya.svg?branch=master)](https://travis-ci.org/kremius/karya-valya)

It used to be Karya &amp; Valya Rogue-like, but now it is Griefly: Yet Another Space Station Remake

Dependencies
-------------
1. Some C++ compiler (mine is the compiler from **Visual Studio 2012**)
2. Qt5 (mine version is **Desktop Qt 5.4.0 MSVC2012 OpenGL 32bit**). Qt Creator is optional, but desired
3. SFML 2.3
4. libpng
5. Python 2.7
6. Go
7. Git
8. CMake 2.8 
9. SDL 1.2 _(will be removed soon)_
10. SDL_image 1.2 _(will be removed soon)_

How to build everything on Windows
-----------------------------------
_It is not tested guide, so if you have any issues during the process please report them_

1. All tools and libs from the depencies list should be available on your machine
2. Open CMakeLists.txt in Qt Creator
3. Environment variables  
   Projects _(left column in Qt Creator)_ -> Build Environment  
   It is needed to set environment variables for libs and tools.
   Mine setted as:  
  `Set GIT_PATH to C:\Program Files (x86)\Git\bin\git.exe`  
  `Set GOFMT_PATH to C:\Go\bin\gofmt.exe`  
  `Set GO_PATH to C:\Go\bin\go.exe`  
  `Set PNG_INCLUDE_DIR to C:\Users\Kremius\Documents\ExternalLibs\lpng1612`    
  `Set PNG_LIBRARY to C:\Users\Kremius\Documents\ExternalLibs\lpng1612\projects\vstudio\Release\libpng16.lib`    
  `Set PYTHON_PATH to C:\Python27\python.exe`    
  `Set SDLDIR to C:\Users\Kremius\Documents\ExternalLibs\SDL-1.2.15`    
  `Set SDLIMAGEDIR to C:\Users\Kremius\Documents\ExternalLibs\SDL_image-1.2.12`  
  `Set SFML_AUDIO_LIBRARY to C:\Users\Kremius\Documents\ExternalLibs\SFML-2.3\lib\sfml-audio.lib`  
  `Set SFML_INCLUDE_DIR to C:\Users\Kremius\Documents\ExternalLibs\SFML-2.3\include`  
  `Set SFML_LIBRARY to C:\Users\Kremius\Documents\ExternalLibs\SFML-2.3\lib\sfml-main.lib`  
4. Run CMake with param `-DCMAKE_BUILD_TYPE=Release` for Release verison.
5. Build the project. Client executables will appear in the Exec folder, and the server executable will appear in the knv-server-go folder.

How to build everything on Linux
--------------------------------

1. Install dependencies. Look at `travis-get-deps` rule in Makefile for clues. Also you will need go (https://golang.org/dl/).
2. `make`. Built project will be placed under `Exec` directory.
3. `./build_go_server.sh`

How to start server
-------------------

Just run the executable from directory `knv-server-go`.

How to run game without launcher
--------------------------------

Pass those command line parameters to `KVEngine` or `KVEngine.exe`:
`mapgen_name=brig_small.gen -autogen_reports -auto_connect login=Guest -unsync_generation`
You can also specify game host by parameter `ip=game_host_address`. By default it connects to localhost.
