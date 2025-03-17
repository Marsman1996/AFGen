# clang -g -fsanitize=address,fuzzer ./AFG-ffjpeg.c-main-jfif_encode.c ../build_asan/liblibffjpeg.a  -I../code -I../build_normal    -Wno-all -o ./AFG-ffjpeg.c-main-jfif_encode

clang -g -fsanitize=address,fuzzer ./AFG-jfif.c-AFG_default-jfif_encode.c ../build_asan/liblibffjpeg.a  -I../code -I../build_normal    -Wno-all -o ./harness

