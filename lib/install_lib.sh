#! /bin/bash

cd lib/irrlicht/source
make -j4
make clean
make sharedlib -j4
make clean
sudo make install;
make clean
ls
# cd ../../
# ls
sudo chmod 755 irrKlang/bin/linux-gcc-64/ikpFlac.so irrKlang/bin/linux-gcc-64/ikpMP3.so irrKlang/bin/linux-gcc-64/libIrrKlang.so
sudo cp -r irrKlang/bin/linux-gcc-64/ikpFlac.so irrKlang/bin/linux-gcc-64/ikpMP3.so irrKlang/bin/linux-gcc-64/libIrrKlang.so /usr/local/lib
