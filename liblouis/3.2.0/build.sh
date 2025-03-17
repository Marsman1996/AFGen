#!/bin/bash
. ../../common.sh $1

# fetch source code
wget https://github.com/liblouis/liblouis/releases/download/v3.2.0/liblouis-3.2.0.tar.gz
tar -xf liblouis-3.2.0.tar.gz && mv liblouis-3.2.0 code

# compile
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

../code/configure --prefix=$PWD/../bin_$MODE --enable-static --disable-shared
make || exit 1

make install || exit 1

popd

echo "end compiling $PWD with $MODE"