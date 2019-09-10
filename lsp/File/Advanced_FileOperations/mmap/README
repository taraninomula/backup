The contents of a file mapping are initialized using length bytes starting at offset offset in the file referred  to by the file descriptor fd.  offset must be a multiple of the page size as returned by sysconf(_SC_PAGE_SIZE).

mmap Examples: map files or devices into memory
----------------------------------------------
file examples:
-------------
1. mmap1.c: This is simple mmap example. In this example all the mmap parameters are hard coded, for example file name is "test.file" , length of the file is 10, off set of the file is 0.

This example doesn't work if the file size is 0. We can face segmentation problem.

2. mmap2.c: This example implements comamnd line arugments & also gives proper error when ever file size is 0. 
Drawback: This example doesn't compare offset and file size.

3. mmap3.c: This example compares offset and file size also. 
Drawback: This example doesn't check page boundary.

4. mmap4.c: This is perfect mmap generic example. Here, proper ERROR handling is implemented & also user can give any file name, length & offset values using command line arguments.

Device examples:
---------------
Display Example:

"fbset" command shows display information.

The below display examples shows how to use ioctl(), mmap() system calls in display application. 
1. fb.c : This example shows differenr colurs in screen. 
2. fb_clear.c: This exmaple clear the screen.
3. fb_center.c: This example enable center pixel. 

-----------------------------------------------------------------------------------------------------
NAME
       mmap, munmap - map or unmap files or devices into memory

SYNOPSIS
       #include <sys/mman.h>

       void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
       int munmap(void *addr, size_t length);

--------------------------------------------------------------------------------------------------------------------------------------
The page size:
-------------
The page is the smallest unit of memory that can have distinct permissions and behavior. Consequently, the page is the building 
block of memory mappings, which in turn are the building blocks of the process address space.
The mmap( ) system call operates on pages. Both the addr and offset parameters must be aligned on a page-sized boundary. 
That is, they must be integer multiples of the page size.

Mappings are, therefore, integer multiples of pages. If the len parameter provided by the caller is not aligned on a 
page boundary—perhaps because the underlying file’s size is not a multiple of the page size—the mapping is rounded up to the next full
page. The bytes inside this added memory, between the last valid byte and the end of the mapping, are zero-filled. 
Any read from that region will return zeros. Any writes to that memory will not affect the backing file, even if it is mapped as 
MAP_SHARED. Only the original len bytes are ever written back to the file.

1.sysconf( ). The standard POSIX method of obtaining the page size is with sysconf( ),
----------
which can retrieve a variety of system-specific information:
#include <unistd.h>
long sysconf (int name);

A call to sysconf( ) returns the value of the configuration item name, or -1 if name is
:invalid. On error, the call sets errno to EINVAL. Because -1 may be a valid value for
some items (e.g., limits, where -1 means no limit), it may be wise to clear errno
before invocation, and check its value after.
POSIX defines _SC_PAGESIZE (and a synonym, _SC_PAGE_SIZE) to be the size of a page,
in bytes. Therefore, getting the page size is simple:
long page_size = sysconf (_SC_PAGESIZE);

2. getpagesize( ). Linux also provides the getpagesize( ) function:
-----------------
#include <unistd.h>
int getpagesize (void);

A call to getpagesize( ) will likewise return the size of a page, in bytes. Usage is even
simpler than sysconf( ):
int page_size = getpagesize ( );
Not all Unix systems support this function; it’s been dropped from the 1003.1-2001
revision of the POSIX standard. It is included here for completeness.

3. PAGE_SIZE. 
------------
The page size is also stored statically in the macro PAGE_SIZE, which is defined in <asm/page.h>. 
Thus, a third possible way to retrieve the page size is:
int page_size = PAGE_SIZE;


Advantages of mmap( ):
---------------------
1. Manipulating files via mmap( ) has a handful of advantages over the standard read( ) and write( ) system calls. Among them are:
2. Reading from and writing to a memory-mapped file avoids the extraneous copy that occurs when using the read( ) or write( ) 
system calls, where the data must be copied to and from a user-space buffer.
3. Aside from any potential page faults, reading from and writing to a memory-mapped file does not incur any system call or context 
switch overhead. It is as simple as accessing memory.
4. When multiple processes map the same object into memory, the data is shared among all the processes. Read-only and shared writable mappings are shared in their entirety; private writable mappings have their not-yet-COW (copy-on-write) pages shared.
5. Seeking around the mapping involves trivial pointer manipulations. There is no need for the lseek( ) system call.
For these reasons, mmap( ) is a smart choice for many applications.

Disadvantages of mmap( ):
-------------------------
There are a few points to keep in mind when using mmap( ):
1. Memory mappings are always an integer number of pages in size. Thus, the difference between the size of the backing file and an 
integer number of pages is “wasted” as slack space. For small files, a significant percentage of the mapping
may be wasted. For example, with 4 KB pages, a 7 byte mapping wastes 4,089 bytes.
2. The memory mappings must fit into the process’ address space. With a 32-bit address space, a very large number of various-sized 
mappings can result in fragmentation of the address space, making it hard to find large free contiguousregions. 
This problem, of course, is much less apparent with a 64-bit address space.
3. There is overhead in creating and maintaining the memory mappings and associated data structures inside the kernel. This overhead is generally obviated by the elimination of the double copy mentioned in the previous section, particularly
for larger and frequently accessed files.

For these reasons, the benefits of mmap( ) are most greatly realized when the mapped file is large (and thus any wasted space is a 
small percentage of the total mapping), or when the total size of the mapped file is evenly divisible by the page size (and thus
there is no wasted space).

