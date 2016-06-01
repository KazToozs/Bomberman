#! /bin/bash

mkdir -p lib/bin
# ln -s lib/irrlicht/bin/libIrrlicht.so.1.8.3 lib/lua/liblua53.so lib/SFML/lib/libsfml-system.so lib/SFML/lib/libsfml-audio.so `pwd`/lib/bin
cp -r lib/irrlicht/bin/libIrrlicht.so.1.8.3 lib/lua/liblua53.so lib/SFML/lib/libsfml-system.so.2.2.0 lib/SFML/lib/libsfml-audio.so.2.2.0 `pwd`/lib/bin
export LD_LIBRARY_PATH="$(pwd)/lib/bin"
#export LD_PRELOAD="$(pwd)/lib/bin/libIrrlicht.so.1.8.4"
#echo $LD_PRELOAD
# export LD_LIBRARY_PATH
# cd lib/irrlicht/source
# make -j4
# make clean
# make sharedlib -j4
# make clean
# sudo make install;
# make clean
# ls
# # cd ../../
# ls
# sudo cp -r SFML/lib/* /usr/lib
