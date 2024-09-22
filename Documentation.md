# Vulimg documentation

Vultools is a small helper utility library for
[vulcmp](https://github.com/Doi6doi/vulcmp/blob/main/Documentation.md),
[vulimg](https://github.com/Doi6doi/vulimg/blob/main/Documentation.md)
and other similar (or different) libriaries.

- [Types](#types)
- [Functions](#functions)
- [Constant values](#constant-values)

## Types

- `VtlRect`: a rectangular area on an image or other 2D coordinate-system
- `VtlStreamOp`: stream read or write function. (like fread or fwrite)

## Functions

```c
uint32_t vtl_fread( void * stream, void * mem, uint32_t size )
```
A fast `VtlStreamOp` which calls 
[fread](https://en.cppreference.com/w/c/io/fread) on `stream`. 
It only returns 0 or `size`. (all or nothing)
- `stream`: the stream to read. Must be FILE *
- `mem`: address where data is read
- `size`: number of bytes to read
- *returns* number of bytes read 

---
```c
uint32_t vtl_fread_part( void * stream, void * mem, uint32_t size )
```
A not that fast `VtlStreamOp` which calls 
[fread](https://en.cppreference.com/w/c/io/fread) on `stream`. 
It can read less than `size`.
- `stream`: the stream to read. Must be FILE *
- `mem`: address where data is read
- `size`: number of bytes to read
- *returns* number of bytes read

---
```c
uint32_t vtl_fwrite( void * stream, void * mem, uint32_t size )
```
A fast `VtlStreamOp` which calls 
[fwrite](https://en.cppreference.com/w/c/io/fwrite) on `stream`. 
It only returns 0 or `size`. (all or nothing)
- `stream`: the stream to write. Must be FILE *
- `mem`: address of data to write
- `size`: number of bytes to write
- *returns* number of bytes written

---
```c
bool vtl_write_block( void * stream, VtlStreamOp write, void * mem, uint32_t size )
```
Function to write exactly `size` bytes to stream. It keeps calling
`write` function until all bytes are written or it returns 0.
- `stream`: the stream to write
- `write`: stream writer function
- `mem`: address of the data to write
- `size`: number of bytes to write
- *returns* true if all data is written. False if `write` returns 0.

---
```c
bool vtl_read_block( void * stream, VtlStreamOp read, void * mem, uint32_t size )
```
Function to read exactly `size` bytes from stream. It keeps calling
`read` function until all bytes are read or it returns 0.
- `stream`: the stream to read
- `read`: stream reader function
- `mem`: address where data is read
- `size`: number of bytes to read
- *returns* true if all data is read. False if `read` returns 0.

---
```c
bool vtl_read_skip( void * stream, VtlStreamOp read, uint32_t size )
```
Function to skip `size` bytes reading `stream`. It keeps calling
`read` function until all bytes are skipped or it returns 0.
- `stream`: the stream to skip
- `read`: stream reader function
- `size`: number of bytes to skip
- *returns* true if all bytes are skipped. False if `read` returns 0.

---
```c
void vtl_ewrite( VcpStr s )
```
Write a message to standard error with line terminator and flush it.
- `s`: the message to show

---
```c
void vtl_die( VcpStr s )
```
Write a message to standard error and terminate program. Terminates with error code 1.
- `s`: the message to show

---
```c
bool vtl_nat( VcpStr s, uint32_t * nat )
```
Tries to convert C string to a natural (>=0) number.
- `s`: the C string
- `nat`: the number which the string contained
- *returns* true if it could convert the string to number

---
```c
VcpStr vtl_cat( VcpStr a, VcpStr b )
```
Memory-safe concatenation of two C strings. 
Uses and reallocates an inner buffer for the result.
Additional calls will overwrite previous result.
Terminates whole program if cannot allocate memory.
- `a`: the left string
- `b`: the right string
- *returns* the concatenated string

---
```c
bool vtl_same( VcpStr a, VcpStr b )
```
NULL-proof string comparision. Returns true if both are NULL
or contain the same string.
- `a`: the first string
- `b`: the second string
- *returns* true if both are NULL or contain the same string

---
```c
bool vtl_rect_overlap( VtlRect a, VtlRect b )
```
Checks if the areas overlap.
- `a`: the first area
- `b`: the second area
- *returns* true if there is at least one point overlap of the areas

---
```c
void vtl_ewrite_stamp()
```
Writes and flushes to stderr how many milliseconds passed since last call of this function.
Can be used to measure how much time a program part needs to run.

---
```c
int vtl_physical_cpu( void * p )
```
vulcmp score function to choose CPU instead of GPU. Can be used in
`vcp_select_physical` call.

### Constant values

- `VTL_STREAMERR`: there was an error during stream read or write

