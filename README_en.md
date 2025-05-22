# Toolib
Some tool libs used by myself.

## Write before
This project is coded, checked and pulled all in VS. And it used the module which is add in C++23, so check your settings. Its document encoding is GB 2312, so some annotations are displayed abnormally.

**I can't promise it is safe.**

## modules

### bitIO
`bitarry` is a class which can change data by bit.

#### init
`bitarry()` -> Creat a null obj that don't have anything.

`bitarry(const size_t size)` -> Creat a array that have \<size\> bits(8-bit alignment). Now uses `explicit` to prevent it from being called implicitly.

`bitarry(const unsigned char* arry, const size_t len)` -> Creat a array from a unsigned char array, \<len\> is how many chars in the char array.

#### funcs
`bool setSize(const size_t bitsize)` -> Set the size of array. (Only work when the obj is a null obj)

`bitarry read(const size_t v, const int len)` -> Read \<len\> bits and beging from the bit \<v\>.

`bool write(const size_t v, const int len, wood::bitarry bdata)` -> Write \<len\> bits (from data bit 0) and beging from the bit \<v\>.**Waring: This func don't check if the data has enough bits.**

`void Print(unsigned short CHD)` -> Print array data to stdout. Modoul 0: Char, Modoul 1: Hex, Modoul 2: Decimal number.

`const unsigned char* c_str()const` -> return the data pointer.Now the null object returns a pointer pointing to "\0".

`const size_t resize()const` -> return size of array.

`bitarry setMermey(const unsigned char data)` -> Set array by data.

`bool good()const` -> Check if any error happend.

`const char* err()` -> Get the information of err. And reset the err flag.

* `bitarry setMemModel(int model)` -> Set the memory model for reading, 0 is the normal large end-order model (default), 1 is the local small end-order model (single unsigned char) internal.

For example: 0x64 (0110 0100) is considered as 0010 0110 from low to high bits in mode 0, while mode 1 recognizes it as 0110 0100. However, this does not affect the overall storage, for instance, char str={'a','b'} would still result in str\[0\]='a', str\[1\]='b' in both modes.

* `[]`Support subscript index to read data.

### EDcode
Some encoded functions.

* `ToBase2X` and `FromBase2X`, these functions can customize the number of bits and character tables of the grouping, which is equivalent to $Base2^x$, e.g. passing in 5 is equivalent to Base32 (in the case of the same character table).

**Warning: Please make sure the character table is long enough, these functions will not check if the character table is long enough.**

* Implementations of `ToBase64` and `FromBase64`.
* Implementations of `ToBase32` and `FromBase32`.

Note: implementations will not complement the “=” at the end, except for `ToBase64(const char* str, unsigned char* buffer, int MaxLen)`.

### toolfunc
Some functional functions

* 'HowLongUtf8' -> to see how many bytes a utf-8 character is counted.

Note: The common Chinese Windows environment is not encoded as UTF-8, it is recommended to use PWSH (code page: 65001) to check the health status, such as "a" is long 1, "α" is long 2, "我" is long 3, and "🍑" is long 4. Note that this function does not have the ability to check ligatures.