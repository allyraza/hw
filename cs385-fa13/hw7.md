<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_7_DIY_Memory_Allocator"></a> Homework 7: DIY Memory Allocator </h1>
<p>
User programs typically allocate memory using the standard library functions <code>malloc()</code> and <code>free()</code>. These are userspace functions, which both use the <code>sbrk()</code> system call to request and release memory allocated to the process.
</p><p>
In this homework, we create an alternative memory allocator, which provides the functions <code>myalloc()</code>, and <code>myfree()</code>. The performance of your allocator will be measured in terms of program runtime and fragmentation.
</p><p>
<strong>NOTE:</strong> The template makefile tells gcc to compile in 32-bit mode, even if you're on a 64-bit system. If you get a complaint about missing stubs-32.h, just run <code>sudo apt-get install libc6-dev-i386</code>.
</p><p>
<strong>Turn-in requirements:</strong> make your changes to hw7.c only.Your solution should use only <code>sbrk()</code> to request and release memory. This means you cannot use other built-in memory allocation functions like <code>malloc()</code>, <code>calloc()</code> or <code>mmap()</code>. Your solution will be graded based on performance in a variety of scenarios, some or all of which are already present in main.c. 
</p><p>
</p><h2><a name="Basic_mymalloc_and_myfree"></a> Basic mymalloc() and myfree() </h2>
<p>
Based on the homework template, support the re-use of free()'d allocations in subsequent calls to mymalloc(). You may want to use a linked list to represent free allocations here, as we don't worry too much about performance.
</p><p>
Like in malloc, make sure you use the free memory to represent the linked list.
</p><p>
</p><h2><a name="Coalescing_myfree"></a> Coalescing myfree() </h2>
<p>
Improve your myfree() implementation to support the coalescing of two or more small free()'d allocations, so that a subsequent larger mymalloc() can re-use the freed memory.
</p><p>
For example, say I free 4 consecutive allocations of 4 bytes each. A later mymalloc(16) should be able to reuse the free'd memory. To implement this, use the boundary tag method used by the standard malloc.
</p><p>
</p><h2><a name="Faster_mymalloc"></a> Faster mymalloc() </h2>
<p>
When the number of free allocations is large, every call to malloc potentially takes a long time. Change the way you represent free allocations to speed up the process. For this, use an array of free lists for various sizes.
</p><p>
</p><h2><a name="Some_hints"></a> Some hints </h2>
<p> </p><ul>
<li> <strong>WARNING:</strong> this will not work on OS X. the brk() system call does not exist on OS X, and is emulated in userspace. This creates a 4 Mb limit on the break size.
</li> <li> Sometimes, the "best fit" from the free list is still not a very good fit (could be several megabytes off if you're unlucky, especially with a coalescing solution). In that case, simply split your best fit chunk into a great fit, and a newly initialized leftover chunk, that you then add back to the free list.
</li> <li> When you have a free chunk adjacent to the break, call sbrk with a negative argument to lower the break. Be careful to remove the "adjacent" chunk from your free list!
</li> <li> Use gdb to debug your segmentation faults!
</li> <li> If you get a segfault that only happens on the console, and not in gdb, turn on "core dumps" with the command "ulimit -c unlimited". You can then do a retrospective debugging session with gdb thus: "gdb hw7 core", which shows you the status of the program as it crashed.
</li></ul> 
<p>
</p><h2><a name="Example_of_good_performance_full"></a> Example of "good performance", full hw7 implementation output </h2>
<p>
</p><pre>./hw7 987987
Simple alloc/free, alloc/free cycle: 0, timediff:237
Coalescing free and splitting mymalloc: 0, timediff:29
After freeing coalesced blocks: -10320000, timediff:7
Random malloc and free sequence: 0, timediff: 698
</pre>
<p>
with 1000 16-byte spaced lists:
</p><p>
</p><pre>Simple alloc/free, alloc/free cycle: 0, timediff:291
Coalescing free and splitting mymalloc: 0, timediff:67
After freeing coalesced blocks: -10320000, timediff:7
Random malloc and free sequence: 0, timediff: 822
</pre>
<p>
with a single list:
</p><p>
</p><pre>Simple alloc/free, alloc/free cycle: 0, timediff:239
Coalescing free and splitting mymalloc: 0, timediff:29
After freeing coalesced blocks: -10320000, timediff:7
Random malloc and free sequence: 0, timediff: 2491
</pre>
<p>
without coalescing or lowering the break:
</p><p>
</p><pre>Simple alloc/free, alloc/free cycle: 100080000, timediff:332
Coalescing free and splitting mymalloc: 9216072, timediff:33
After freeing coalesced blocks: 8192064, timediff:0
Random malloc and free sequence: 497408, timediff: 2535
</pre>
<p>
with coalescing, but without splitting:
</p><p>
</p><pre>Simple alloc/free, alloc/free cycle: 0, timediff:230
Coalescing free and splitting mymalloc: 8192064, timediff:29
After freeing coalesced blocks: -10320000, timediff:7
Random malloc and free sequence: 0, timediff: 666
</pre> </div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>