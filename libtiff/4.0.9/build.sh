#!/bin/bash
. ../../common.sh $1

# fetch source code
wget https://gitlab.com/libtiff/libtiff/-/archive/v4.0.9/libtiff-v4.0.9.tar.gz
tar -xf libtiff-v4.0.9.tar.gz && mv libtiff-v4.0.9 code

# compile
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

../code/configure --prefix=$PWD/../bin_$MODE --enable-static --disable-shared
make -j $JOBS || exit 1

make install || exit 1

popd

echo "end compiling $PWD with $MODE"