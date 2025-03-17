#!/bin/bash
. ../../common.sh $1

# fetch source code
wget https://github.com/appneta/tcpreplay/releases/download/v4.3.4/tcpreplay-4.3.4.tar.gz
tar -xf tcpreplay-4.3.4.tar.gz && mv tcpreplay-4.3.4 code

CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE
pushd build_$MODE

./autogen.sh
./configure --prefix=$PWD/../bin_$MODE --disable-local-libopts --disable-libopts-install
make -j $JOBS || exit 1

make install || exit 1

popd

echo "end compiling $PWD with $MODE"