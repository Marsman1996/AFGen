# clang -g -fsanitize=address,fuzzer ./AFG-ffjpeg.c-main-jfif_decode.c ../build_asan/src/libffjpeg.a  -I../code/src -I../code    -Wno-all -o ./AFG-ffjpeg.c-main-jfif_decode

clang -g -fsanitize=address,fuzzer ./AFG-jfif.c-AFG_default-jfif_decode.c ../build_asan/src/libffjpeg.a  -I../code/src -I../code    -Wno-all -o ./harness

