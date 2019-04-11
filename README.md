# hashmap_c

Hashmap with [MurmurHash3](https://github.com/aappleby/smhasher) (specifically `MurmurHash3_x32_32` variant) as hashing function in C implementation which is suitable for low latency hash table lookup.

# Build

Based on autotools.

* `./autogen.sh`
* `./configure`
* `make`
* (optional) `make check`
* `make install`

## ndk-build suport for Android

This project has support for building library for Android.

It has `Android.mk` file at the root directory of this project. You can use the following command for example

```
ndk-build NDK_PROJECT_PATH=null NDK_OUT=build/objs NDK_LIBS_OUT=build/libs APP_BUILD_SCRIPT=Android.mk APP_PLATFORM=android-18 APP_MODULES="hashmap_c hashmap_c_static" NDK_DEBUG=1
```

That will generate obj and library (shared and static one) files at build/objs and build/libs (static library is at build/objs/local for minimum sdk support of api level 18 with debugging symbols also generated. `APP_MODULES` tells to build for both shared and static library.

# Compile Flags

If you want to see more debugging log as spit out from hashmap itself, use `make CFLAGS=-DHASHMAPC_DEBUG`. This will make it prints out debugging log whenever we call its function.

# Technical Note

It will expand by doubling memory space preparing for future addition of key-value item when the current number of key-value items reaches 75% of its capacity which is initially set to be 16.

There's no mechanism to shrink down memory usage, so capacity will be double each time according to description above.

# License
MIT, Wasin Thonkaew
