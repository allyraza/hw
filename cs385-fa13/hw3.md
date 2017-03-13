<div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_3_Data_structures_in_C"></a> Homework 3 - Data structures in C </h1>
<p>
In this homework, we practice our C skills by implementing a String data structure, and testing our implementations against each other. An implementation of the String data structure consists of a .o file that provides the following set of functions:
</p><p>
</p><pre>// hw3_string.h
struct String;
struct String* string_new(char* str);
void string_free(struct String* s);
struct String* string_clone(struct String* s);

int string_length(struct String* s);
void string_append(struct String* a, char* b);
char string_charAtIndex(struct String* s, int index);
char* string_range(struct String* s, int start, int length);
char* string_chars(struct String* s);
</pre>
<p>
The template for hw3 is available at <code>svn://bits.cs.uic.edu/cs385/pub/homeworks/hw3</code>. This contains the <code>hw3_string.h</code> above, an implementation of the String data structure called <code>simple_string.c</code>, and programs that use String data structures and tests their correctness and runtime performance.
</p><p>
</p><h2><a name="A_faster_representation_of_Strin"></a> A faster representation of Strings </h2>
<p>
Your task is to create an alternative implementation of the String data structure, in a file called <code>fast_string.c</code>. You may implement your data structure whichever way you please, as long as the following conditions hold:
</p><p> </p><ul>
<li> it uses <code>dmalloc()</code> and <code>dfree()</code> instead of <code>malloc()</code> and <code>free()</code>. Also uses no other functions (like mmap() or remalloc()) for dynamic memory allocation.
</li> <li> it passes all tests run by <code>make testunit</code> without warnings
</li> <li> it outputs the correct characters and excerpts when running <code>make testspeed</code>
</li> <li> it conforms to the performance expectations described below
</li></ul> 
Do not change the .c and .h files in the template. Instead, copy <code>simple_string.c</code> to a new file <code>fast_string.c</code>, and edit the first line of the <code>Makefile</code> to use <code>fast_string.c</code> instead. Make and commit your changes to fast_string.c.
<p>
</p><h2><a name="Design_suggestions"></a> Design suggestions </h2>
<p>
While you are free to implement the String data structure in any way you please, here are some suggestions.
</p><p> </p><ul>
<li> simple_string.c is slow because it keeps copying an ever-growing string to new places. You need to stop it from making these copies.
</li> <li> if you use a linked-list, you'll end up dereferencing a crazy number of pointers when indexing into a large file, making the index operation slow
</li> <li> a binary tree is a natural representation. Note, however, that it will only be fast if it is somewhat balanced.
</li></ul> 
<p>
</p><h2><a name="Testing_correctness_and_performa"></a> Testing correctness and performance </h2>
<p>
To test the correctness of your code, run <code>make testunit</code>. This performs several unit tests on the String functions declared above. Try running <code>make testunit</code> with <code>STRING_CODE</code> in the <code>Makefile</code> set to <code>simple_string.c</code> to see the expected output.
</p><p>
To test the performance of your code, run <code>make testspeed</code>. This downloads a large book, concatenates the entire book into one large string, line by line, and applies the string functions on the resulting string. <code>make testspeed</code> also outputs a series of "Found characters" and "Excerpts". These outputs are identical for all correct solutions - if your output differs, it will be deemed incorrect.
</p><p>
</p><h2><a name="Performance_expectations"></a> Performance expectations </h2>
<p>
The template directory contains three alternative versions of "speed", the binary run by <code>make testspeed</code>. <code>original_speed</code> runs the code provided in the template. <code>unbalanced_speed</code> runs an early solution I wrote, and <code>balanced_speed</code> runs my best solution.
</p><p>
To try one, run (for example) <code>./balanced_speed pg2554.txt</code>. Your solution is expected to either finish in at most 10 times the total time of <code>balanced_speed</code>, or finish the "reading book" part in at most 2 times that of <code>unbalanced_speed</code>, and the lookup in at most 1.5x that of <code>unbalanced_speed</code>.
</p><p>
</p><h2><a name="Performance_competition_and_bonu"></a> Performance competition and bonus points </h2>
<p>
All turn-ins will be automatically entered into a performance competition, pitting your solution against those of your classmates, as well as against my solutions. As soon as you commit a revision (does not have to be your final submission), it will be automatically tested for correctness and speed. The results will be posted on the <a href="http://bits.cs.uic.edu/cs385/scoreboard.txt" target="_top">hw3 scoreboard</a>.
</p><p>
As an added bonus, the author of any solution that consistently beats mine in total execution time will receive 5 bonus points toward the final grade. Also, author of the highest-performing student solution will receive 5 bonus points toward the final grade. These bonuses are not stackable, so the max bonus possible is 5 points, but there's always the glory. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div>