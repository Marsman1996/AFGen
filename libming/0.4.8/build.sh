#!/bin/bash
. ../../common.sh $1

# fetch source code
wget https://github.com/libming/libming/archive/refs/tags/ming-0_4_8.tar.gz
tar -xf ming-0_4_8.tar.gz && mv libming-ming-0_4_8 code

# compile
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE
pushd build_$MODE

CFLAGS+=" -fcommon"
export CFLAGS=$CFLAGS

./autogen.sh
./configure --prefix=$PWD/../bin_$MODE --enable-static --disable-shared --disable-freetype
make || exit 1

make install

popd

echo "end compiling $PWD with $MODE"