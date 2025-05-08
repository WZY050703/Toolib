# Toolib
Some tool libs used by myself.

## Wright before
This project is coded, checked and pulled all in VS. And it used the module which is add in C++23, so check your settings.
**I can't promise it is safe.**

## modules

### bitIO
`bitarry` is a class which can change data by bit.

### EDcode
Some funcs do code. Now there just have `ToBase64`.

**Warning**: For some problem, the func `ToCBace64()` is not work in the way of Base64, but a new way.
(It read data streamly from low bit to high bit, not as the true Base64.)