#! /bin/bash

cd lib/irrlicht/source
make -j4; make clean; make sharedlib -j4; make clean; sudo make install;
cd -
