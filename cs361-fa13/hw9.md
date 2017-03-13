<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Synchronization_using_Semaphores"></a> Synchronization using Semaphores </h2>
<p>
In this homework, we solve several synchronization problems using standard semaphores. The homework template, available at <code>svn://bits.cs.uic.edu/cs361/pub/homeworks/hw9</code> contains skeleton solutions, as well as a number of test-cases. A correct solution passes every test case. Plus, except where noted, your solution must have no loops: for, while, goto <em>or</em> recursive!
</p><p>
To run the tests, type <code>make test</code> in your turn-in folder.
</p><p>
</p><h3><a name="Mutual_exclusion_mutex_c"></a> Mutual exclusion (mutex.c) </h3>
<p>
This is a warm-up exercise.
</p><p>
</p><h3><a name="Reusable_Barrier_barrier_c"></a> Reusable Barrier (barrier.c) </h3>
<p>
This is the problem we discussed in class at some length. Implement first a disposable barrier, then a reusable barrier using semaphores.
</p><p>
</p><h3><a name="Worker_Threads_1_worker1_c"></a> Worker Threads 1 (worker1.c) </h3>
<p>
Here the scenario is a multi-threaded web server. To avoid the overhead of thread creation, and the risk of overloading the CPU, threads are created on startup only. As requests come in, they are served by existing threads as they become available.
</p><p>
Implement the functions <code>wait_for_service()</code> and <code>wait_for_request()</code>. Each function should call <code>pair()</code> once, and synchronize with the other threads such that for every two calls to <code>pair()</code>, there is one worker and one browser. Ordering between the two is not important.
</p><p>
</p><h3><a name="Worker_Threads_2_worker2_c"></a> Worker Threads 2 (worker2.c) </h3>
<p>
In this version, the server has two types of threads - front-end threads that communicate with the remote browser and apply templates to produce the final HTML document, and back-end threads that perform computational tasks and deliver raw content to the front-end thread.
</p><p>
Threads call the functions <code>front_ready()</code> and <code>back_ready()</code> when they have finished processing the last request. These in turn call <code>group()</code> to create a grouping of front/back end threads for the next request.
</p><p>
Every request requires two back-end threads and one front-end. A correct solution must make sure that every group has two back-ends and one front-end. That is, if we print out the thread type for every call to <code>group()</code> and divide the resulting list into groups of three, every group should have two back-ends and one front-end.
</p><p>
</p><h3><a name="Alternating_workloads_alternatin"></a> Alternating workloads (alternating.c) <strong>(5 bonus points)</strong> </h3>
<p>
A new type of storage has been released that offers very fast read and write speeds. However, switching between reading and writing is somewhat slow. Your application has two types of threads - readers and writers. When they are ready to read or write, the call, <code>read_ready()</code> and <code>write_ready()</code>, which in turn call <code>do_read()</code> or <code>do_write()</code>. To make the best use of this new technology, design a synchronization scheme that obeys the following rules:
</p><p> </p><ul>
<li> no concurrent mixing of read()/write() operations 
</li> <li> switch from writing to reading when the number of waiting readers exceed the number of running writers, and vice versa. 
</li></ul> 
<p>
</p><h3><a name="Turn_in_instructions"></a> Turn-in instructions </h3>
<p>
Do not edit the files named *_test.c, and do not use any built-in synchronization operator other than semaphores. Feel free to build and use your own operators out of semaphores though.
</p><p>
This is the same as every previous homework. Make sure you run <code>make test</code> on your solution, on your Amazon EC2 VM, before committing your final version. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>