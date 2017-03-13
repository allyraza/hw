<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Homework_2_a_high_performance_ma"></a> Homework 2: a high-performance malloc (DRAFT) </h2>
<p>
In this homework, we take a naive malloc implementation and add optimizations to significantly improve the performance of a sample application.
</p><p>
The homework template in svn://bits.cs.uic.edu/cs361/pub/homeworks/hw2 holds the application, as well as a basic malloc implementation in basic.c, and a libc malloc wrapper in libcmalloc.c. <strong>export</strong> this template to your turn-in directory, then <code>svn add</code> it.
</p><p>
The Makefile includes targets for both the original <code>basic.c</code> malloc, your improved <code>hw2.c</code> malloc, and a wrapper for the libc malloc. Running <code>make test</code> on the command line executes the target program compiled with all three mallocs, to compare their relative performance.
</p><p>
The basic solution takes about 25-30 seconds to run, whereas the libc malloc wrapper takes about 1-1.5 seconds, or a 20x speedup. For full points on this homework, get to below 2 seconds on Amazon, or a 15x speedup over the basic solution. <strong>exact cutoff liable to change until Wednesday Sept 4.</strong>
</p><p>
</p><h2><a name="Turn_in_instructions"></a> Turn-in instructions </h2>
<p>
As in hw1, turn in your homework by committing your latest version to your turn-in repository before the turn-in deadline. Your hw2 turn-in should be in a folder called hw2 directly under the root folder of your repository. Simply committing the hw2 template is a good start, and highly recommended to do early on.
</p><p>
Put all of your solution code in the file hw2.c, and do not modify the other files.
</p><p>
</p><h2><a name="Libc_Malloc_Reference"></a> Libc Malloc Reference </h2>
<p>
In contrast with most homework, this time you're allowed to look at the solution ahead of time! The link below leads to the source code for malloc in libc, which is very fast. Feel free to read as much or as little of this code as you want, it is very well written and documented. Just don't copy-paste anything.
</p><p>
<a href="http://sourceware.org/git/?p=glibc.git;a=blob_plain;f=malloc/malloc.c;hb=3b813b29653a3ebfd78c2529127a9967d8f2857d" target="_top">libc malloc link</a>
</p><p>
This <a href="http://www.cs.princeton.edu/courses/archive/fall07/cos217/lectures/15Memory-2x2.pdf" target="_top">nice malloc presentation</a> describes some of the standard features implemented in malloc, such as boundary tags, coalescing free chunks, and multiple free-lists. It might be a good complement to Section 9.9 in the textbook.
</p><p>
</p><h2><a name="Competition_Aspect"></a> Competition Aspect </h2>
<p>
To make things a little more interesting, we periodically check for committed solutions, run them, and publish the results <a href="http://bits.cs.uic.edu/hw2results.txt" target="_top">here</a>.  </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>