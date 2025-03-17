MODE="asan"

export CC="clang -fsanitize=address,fuzzer-no-link -g "
export CXX="clang++ -fsanitize=address,fuzzer-no-link -g "

JOBS=${JOBS:-"4"}