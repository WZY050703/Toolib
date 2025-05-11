# Toolib
Some tool libs used by myself.

## Write before
This project is coded, checked and pulled all in VS. And it used the module which is add in C++23, so check your settings.

**I can't promise it is safe.**

## modules

### bitIO
`bitarry` is a class which can change data by bit.

#### init
`bitarry()` -> Creat a null obj that don't have anything.

`bitarry(const size_t size)` -> Creat a array that have \<size\> bits(8-bit alignment).

`bitarry(const unsigned char* arry, const size_t len)` -> Creat a array from a unsigned char array, \<len\> is how many chars in the char array.

#### funcs
`bool setSize(const size_t bitsize)` -> Set the size of array. (Only work when the obj is a null obj)

`bitarry read(const size_t v, const int len)` -> Read \<len\> bits and beging from the bit \<v\>.

`bool write(const size_t v, const int len, wood::bitarry bdata)` -> Write \<len\> bits (from data bit 0) and beging from the bit \<v\>.**Waring: This func don't check if the data has enough bits.**

`void Print(unsigned short CHD)` -> Print array data to stdout. Modoul 0: Char, Modoul 1: Hex, Modoul 2: Decimal number.

`const unsigned char* c_str()const` -> return the data pointer.

`const size_t resize()const` -> return size of array.

`void setMermey(const unsigned char data)` -> Set array by data.

`bool good()const` -> Check if any error happend.

`const char* err()` -> Get the information of err. And reset the err flag.

### EDcode
Some funcs do code. Now there just have `ToBase64`.

**Warning**: For some problem, the func `ToCBace64()` is not work in the way of Base64, but a new way.
(It read data streamly from low bit to high bit, not as the true Base64.)