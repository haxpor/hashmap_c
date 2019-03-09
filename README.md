# hashmap_c

Hashmap with [MurmurHash3](https://github.com/aappleby/smhasher) (specifically `MurmurHash3_x64_128` variant) as hahsing function in C implementation.

# Technical Note

It will expand by doubling memory space preparing for future addition of key-value item when the current number of key-value items reaches 75% of its capacity which is initially set to be 16.

# License
MIT, Wasin Thonkaew
