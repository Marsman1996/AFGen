#!/bin/bash
. ../../common.sh $1

# fetch source code
wget https://github.com/appneta/tcpreplay/archive/refs/tags/v4.2.6.tar.gz 
tar -xf v4.2.6.tar.gz && mv tcpreplay-4.2.6 code
patch code/src/config.h.in < config.h.in.patch
patch code/src/tcpedit/tcpedit.c < tcpedit.c.patch
patch code/configure.ac < configure.ac.patch

# compile 
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE
pushd build_$MODE

./autogen.sh
./configure --prefix=$PWD/../bin_$MODE --disable-local-libopts --disable-libopts-install --enable-static --disable-shared
make -j $JOBS || exit 1

make install || exit 1

popd

echo "end compiling $PWD with $MODE"