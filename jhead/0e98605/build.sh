#!/bin/bash
. ../../common.sh $1

# fetch source code
git clone https://github.com/Matthias-Wandel/jhead.git code
git -C code checkout 0e98605

# compile
CXXFLAGS="${CXXFLAGS}"

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
cp -r code build_$MODE || ( echo "[ERROR]: No code folder find!" && exit 1 )
pushd build_$MODE

make || exit 1

popd
mkdir -p bin_$MODE/bin
cp build_$MODE/jhead bin_$MODE/bin
ar cru bin_$MODE/libjhead.a build_$MODE/obj/*.o

echo "end compiling $PWD with $MODE"