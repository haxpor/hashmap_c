# hashmap_c

Hashmap with [MurmurHash3](https://github.com/aappleby/smhasher) (specifically `MurmurHash3_x32_32` variant) as hashing function in C implementation which is suitable for low latency hash table lookup.

# Build

* `make` - to build the library as object files and test program. Result `.obj` and `hashmapc_test` will be produced at `build/` directory.
* `make lib` - to build a static library `libhashmapc.a` will be produced at `build/` directory.
* `make test` - to build test program
* `make clean` - to clean generated files

# Compile Flags

If you want to see more debugging log as spit out from hashmap itself, use `make CFLAGS=-DHASHMAPC_DEBUG`. This will make it prints out debugging log whenever we call its function.

# Technical Note

It will expand by doubling memory space preparing for future addition of key-value item when the current number of key-value items reaches 75% of its capacity which is initially set to be 16.

There's no mechanism to shrink down memory usage, so capacity will be double each time according to description above.

# License
MIT, Wasin Thonkaew
