# Compiling

1. Install Raylib

2. Run
~~~
g++ -g main.cpp TiledParser/TiledParser.cpp TiledParser/TiledMap.cpp lib/tinyxml2/tinyxml2.o -Ilib/tinyxml2 -ITiledParser -lraylib
~~~
