<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Homework_3_a_garbage_collector_f"></a> Homework 3: a garbage collector for C </h2>
<p>
In this homework, we build a basic, conservative garbage collector for C programs. Starting from the set of root pointers present in the stack and global variables, we traverse the "object graph" (in the case of malloc, a chunk graph) to find all chunks reachable from the root. These are marked using the third lowest order bit in the size field of each chunk.
</p><p>
Your template provides supporting code for finding the limits of the global variable area in memory, as well as for the stack and heap areas. It also demonstrates very basic marking and sweeping. Your task is to complete the garbage collector, so that it frees all garbage, and leaves every other chunk intact.
</p><p>
To compile the template, type "make", and run it with <code>./hw3</code>.
</p><p>
</p><h3><a name="Performance_requirements"></a> Performance requirements </h3>
<p>
For full points, your program should pass all tests in main.c. At present, these are not coded as actual tests, they simply output the heap size and number of free and in-use chunks. Nevertheless, your program should produce the correct values.
</p><p>
Runtime performance is not a major goal for this homework. However, the program should finish well within 2 seconds.
</p><p>
</p><h3><a name="Turn_in_instructions"></a> Turn-in instructions </h3>
<p>
Make all your changes to hw3.c. As in previous homeworks, <em>export</em> the hw3 template to your turn-in directory, add it and commit. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>