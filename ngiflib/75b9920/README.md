# ngiflib 75b9920
0. Clone the source code of the `ngiflib`:
```
$ git clone https://github.com/miniupnp/ngiflib.git code
$ git -C code checkout 75b99202e4e57acab399ed07b4e8f94eddf1648a
```
1. Compile the source code with AddressSanitizer:
```
$ build.sh
```
2. Compile the corresponding fuzz drivers