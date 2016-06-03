#! /bin/bash

mkdir -p lib/bin
#cp -r lib/irrlicht/bin/libIrrlicht.so.1.8.3 lib/lua/liblua53.so lib/SFML/lib/libsfml-system.so.2.2.0 lib/SFML/lib/libsfml-audio.so.2.2.0 `pwd`/lib/bin
ln -s ../irrlicht/bin/libIrrlicht.so.1.8.3 libIrrlicht.so.1.8.3
ln -s ../irrlicht/bin/libIrrlicht.so.1.8.3 libIrrlicht.so.1.8
ln -s ../irrlicht/bin/libIrrlicht.so.1.8.3 libIrrlicht.so
ln -s ../lua/liblua53.so liblua53.so
ln -s ../lua/liblua53.so liblua.so
ln -s ../SFML/lib/libsfml-system.so.2.2.0 libsfml-system.so.2.2.0
ln -s ../SFML/lib/libsfml-audio.so.2.2.0 libsfml-audio.so.2.2.0
export LD_LIBRARY_PATH="$(pwd)/lib/bin"
