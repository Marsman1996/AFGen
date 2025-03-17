#!/bin/bash
. ../../common.sh $1

# fetch source code
git clone https://github.com/rockcarry/ffjpeg.git code
git -C code checkout 23dffdfd2507b4de7b9f292ac1a791d68f4fd9a3
patch code/src/Makefile < make.patch

# compile
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE
pushd build_$MODE

# cmake ../code -DCMAKE_INSTALL_PREFIX=$PWD/../bin_$MODE -DCMAKE_C_FLAGS="$CFLAGS" -DCMAKE_CXX_FLAGS="$CXXFLAGS"
make || exit 1

popd
mkdir -p bin_$MODE/bin
cp build_$MODE/src/ffjpeg bin_$MODE/bin


echo "end compiling $PWD with $MODE"