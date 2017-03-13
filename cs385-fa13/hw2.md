<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_2_functions_calls_and_m"></a> Homework 2 - functions calls and memory management </h1>
<p>
In this homework, we study how parameters are passed and memory is allocated throughout the execution of a program through a variety of mechanisms. 
</p><p>
</p><h2><a name="1_Pass_by_value_vs_pass_by_refer"></a> 1. Pass by value vs. pass by reference </h2>
<p>
Function parameters (and return values) in C can be passed in two fundamentally different ways: </p><ul>
<li> <strong>By value</strong>, the parameter value is copied into a new variable for use by the callee. Since the value is copied into a new variable, changes to the parameter value by the callee have no effect on the callers variable. 
</li> <li> <strong>By reference</strong>, where a pointer to the intended parameter value is provided to the callee. Since caller and callee operate on the same variable, any changes made by the callee are seen by the caller. 
</li></ul> 
<p>
Passing by value results in a pure and easy to understand program from a mathematical perspective. However, in programs that <em>do something, rather than calculate something</em>, passing by reference is sometimes necessary. Let us explore this distinction through a few exercises.   
</p><p>
</p><h3><a name="a_From_call_by_reference_to_call"></a> a. From call-by-reference to call-by-value </h3>
<p>
The following program unnecessarily uses the call-by-reference method for the function <code>addfive</code>. Change the function <code>addfive()</code> and parts of <code>main()</code> to use call-by-value instead.
</p><p>
</p><pre>#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
void addfive(int *value) {
  *value=(*value)+5;
}

int main(int argc, char **argv) {
  if(argc!=2) { printf("Usage: hw2i1a &lt;integer&gt;\n"); exit(1); }
  int times = atoi(argv[1]);
  int accumulator=0;
  while(times--) {
    printf("Accumulator = %d\n",accumulator);
    addfive(&amp;accumulator);
  }
}
</pre>
<p>
<strong>Turn-in requirement:</strong> submit your program as a file called <code>hw2i1a.c</code> in your hw2 directory, and add <code>hw2i1a</code> as a target to the Makefile. 
</p><p>
</p><h3><a name="b_From_call_by_value_to_call_by"></a> b. From call-by-value to call-by-reference </h3>
<p>
This program crashes with a stack overflow error when we try to pass a very large struct by value. To see the program work, try changing the size of the largearray field to something much smaller. It should break when the size exceeds 4090  kilobytes or so. 
</p><p>
Change the function <code>incrementCharAtOffset()</code> (and part of <code>main()</code>) to use call-by-reference for this call instead.  
</p><p>
</p><pre>#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;string.h&gt;
struct LargeStruct {
  char largearray[4096*1024];
};

struct LargeStruct 
incrementCharAtOffset(struct LargeStruct s, int offset)
{
  s.largearray[offset]++;
  return s;
}

struct LargeStruct myLargeStruct;
main() {
  int incrementOffset = 10;
  printf("Value at offset %d before incrementing %d\n",
          incrementOffset,
          myLargeStruct.largearray[incrementOffset]);

  myLargeStruct=incrementCharAtOffset(myLargeStruct,incrementOffset);

  printf("Value at offset %d after incrementing %d\n",
           incrementOffset,
           myLargeStruct.largearray[incrementOffset]);  
}
</pre>
<p>
<strong>Turn-in requirement:</strong> submit your program as a file called <code>hw2i1b.c</code> in your hw2 directory, and add <code>hw2i1b</code> as a target to the Makefile. 
</p><p>
</p><h2><a name="Dynamic_memory_allocation"></a> Dynamic memory allocation </h2>
<p>
Memory is allocated in C in three primary ways.
</p><p> </p><ul>
<li> Static allocation, which is used for global variables. Static memory allocation is determined at compile time, and is the same for every execution of a program. This memory is released only upon program exit.
</li> <li> Stack allocation, which is used for local variables, function parameters and return values. Space for these variables is allocated from the stack on each function call, and thus depends on the execution flow of a program. The maximum size of the stack is typically set externally. Memory allocated from the stack is released upon function return.
</li> <li> Dynamic allocation, often referred to as the 'heap'. Dynamic memory allocation is done using the malloc() or mmap() calls in C. Dynamically allocated memory is released upon program exit, or using the functions free() or munmap(). 
</li></ul> 
<p>
</p><h3><a name="a_Use_dynamic_memory_allocation"></a> a. Use dynamic memory allocation instead of static </h3>
<p>
The program below reverses a word provided on the command line. Unfortunately, we don't know how long the word might be. To be on the safe side, the current program statically allocates one megabyte to hold the reversed version of the string before printing it out. Try compiling the code, to see the size of the binary: over one megabyte!
</p><p>
Change the code to instead allocate only the required amount of memory at runtime, using malloc(), and don't forget to free() the memory at the end!
</p><p>
</p><pre>#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;string.h&gt;

char reversed[1024*1024]="Huge";
int main(int argc, char** argv) {
 if(argc != 2) { fprintf(stderr,"Usage: hw2i2a &lt;word&gt;\n"); exit(1); }

 memset(reversed,0,sizeof(reversed));
 int i;
 for(i=0;i&lt;strlen(argv[1]);i++) {
  reversed[i]=argv[1][strlen(argv[1])-i-1];
 }
  
 printf("%s = reversed(%s)\n",reversed,argv[1]);
 printf("The reversed string array is %ld bytes.\n",sizeof(reversed));
}
</pre>
<p>
<strong>Turn-in requirement:</strong> submit your program as a file called <code>hw2i2a.c</code> in your hw2 directory, and add <code>hw2i2a</code> as a target to the Makefile. 
</p><p>
</p><h3><a name="b_implement_a_leaky_string_conca"></a> b. implement a (leaky) string concatenation function </h3>
<p>
Change (only) the function <code>concatenate()</code>, so that it returns the result of concatenating strings a and b. For example, <code>concatenate("fire","cracker")</code> returns the string "firecracker". You'll need to use <code>malloc()</code> inside concatenate. However, since there are no calls to free(), this code is leaking memory. That's ok for now.
</p><p>
<strong>NOTE:</strong> as before, you may not use existing string library functions, such as sprintf, strcpy, etc for this homework. strlen() is ok. 
</p><p>
</p><pre>#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;string.h&gt;
char *concatenate(char* a, char* b) {
   return a; // replace this with your string concatenation code
}

int main(int argc, char** argv) {
  if(argc&lt;4) { printf("Usage: hw2i2b &lt;count&gt; &lt;firstword&gt; &lt;secondword&gt;\n");
              exit(1); }

  char *middle="cruel";
  char number[10];
  int i;
    
  for(i=0;i&lt;atoi(argv[1]);i++) {
    sprintf(number,"%d",i); // update the number string

    // begin leaky
    char *line = concatenate( // not leaked
                  concatenate(argv[2],number), // leaked
                  concatenate(middle, // leaked
                   concatenate(number, argv[3]))); // leaked
    if(i&gt;0)  // can't free the statically allocated "cruel" string above
      free(middle); 
    // end leaky      
    printf("%s\n",line);
    middle=line;
  }
  free(middle);
}

</pre>
<p>
Example program output:
</p><p>
</p><pre>~&gt; ./hw2i2b 10 hello world
hello0cruel0world
hello1hello0cruel0world1world
hello2hello1hello0cruel0world1world2world
hello3hello2hello1hello0cruel0world1world2world3world
hello4hello3hello2hello1hello0cruel0world1world2world3world4world
hello5hello4hello3hello2hello1hello0cruel0world1world2world3world4world5world
hello6hello5hello4hello3hello2hello1hello0cruel0world1world2world3world4world5world6world
hello7hello6hello5hello4hello3hello2hello1hello0cruel0world1world2world3world4world5world6world7world
hello8hello7hello6hello5hello4hello3hello2hello1hello0cruel0world1world2world3world4world5world6world7world8world
hello9hello8hello7hello6hello5hello4hello3hello2hello1hello0cruel0world1world2world3world4world5world6world7world8world9world
</pre>
<strong>Turn-in requirement:</strong> submit your program as a file called <code>hw2i2b.c</code> in your hw2 directory, and add <code>hw2i2b</code> as a target to the Makefile. 
<p>
</p><h3><a name="c_manual_garbage_collection"></a> c. manual garbage collection </h3>
<p>
Without garbage collection, it's difficult to write the above program both elegantly and leak-free at the same time: all those nested concatenate calls are forgetting the pointers to the <code>malloc()ed</code>  strings before we get a chance to <code>free()</code> them. 
</p><p>
Without resorting to much stronger measures, the only way to fix these leaks is to keep a pointer to each string until we don't need the string any more, and then <code>free()</code> it. Make a copy of your hw2i2b.c, calling it hw2i2c.c. Changing only the lines between the "begin leaky" and "end leaky" comments, make sure to plug every memory leak in this program. 
</p><p>
To help with the debugging, add the following before <code>concatenate()</code>, change the <code>malloc()</code> call in concatenate to <code>mymalloc()</code>, and use <code>myfree()</code> instead of <code>free()</code> (yes, you're allowed to make those changes).
</p><p>
</p><pre>
void* mymalloc(int size) {
  void* ptr = malloc(size);
  fprintf(stderr,"malloc: %p\n",ptr);
  return ptr;
}
void myfree(void* ptr) {
  fprintf(stderr,"free: %p\n",ptr);
  free(ptr);
}
</pre>
<p>
example output: 
</p><p>
</p><pre>./a.out 2 hello world
malloc: 100080
malloc: 100090
malloc: 1000a0
malloc: 1000b0
free: 100080
free: 100090
free: 1000a0
hello0cruel0world
malloc: 1000a0
malloc: 100080
malloc: 1000d0
malloc: 1000e0
free: 1000a0
free: 100080
free: 1000d0
free: 1000b0
hello1hello0cruel0world1world
free: 1000e0
</pre>
<p>
<strong>Turn-in requirements:</strong> hw2i2c.c and a hw2i2c Makefile target, you know the drill.
</p><p>
</p><h2><a name="3_Three_reverse_Fibonaccis"></a> 3. Three reverse Fibonaccis </h2>
<p>
The fibonacci series ought to be familiar to you by now: 1,1,2,3,5,8,13.... or f(x)=f(x-1)+f(x-2), f(0)=1, f(1)=1. Here is a typical implementation using recursion:
</p><p>
</p><pre>long long fib(x) {
 if(x&lt;2) return 1;
 else return fib(x-1)+fib(x-2);
}
</pre>
<p>
and an iterative implementation
</p><pre>main() {
 long long back1=1,back2=1;
 printf("1, 1, ");
 int i;
 for(i=2;i&lt;75;i++) {
  long long fib=back1+back2;
  printf("%lld, ",fib);
  back2=back1;
  back1=fib;
 }
}
</pre>
<p>
Both solutions use the 64-bit type "long long" to support large integers. You are to implement a "reverse fibonacci series" program, in three different ways. All three programs take the same input and produce the same output:
</p><p>
</p><pre>./hw2i3a 6
8,5,3,2,1,1
./hw2i3b 3
2,1,1
./hw2i3c 9
34,21,13,8,5,3,2,1,1
./hw2i3a 70
190392490709135,117669030460994,72723460248141,44945570212853,27777890035288,17167680177565,10610209857723,6557470319842,4052739537881,2504730781961,1548008755920,956722026041,591286729879,365435296162,225851433717,139583862445,86267571272,53316291173,32951280099,20365011074,12586269025,7778742049,4807526976,2971215073,1836311903,1134903170,701408733,433494437,267914296,165580141,102334155,63245986,39088169,24157817,14930352,9227465,5702887,3524578,2178309,1346269,832040,514229,317811,196418,121393,75025,46368,28657,17711,10946,6765,4181,2584,1597,987,610,377,233,144,89,55,34,21,13,8,5,3,2,1,1
</pre>
<p>
In our tests, the input number will always be below 75 and above 2.
</p><p>
</p><h3><a name="a_Functional_No_loops_no_global"></a> a. Functional: No loops, no global variables, no arrays </h3>
Use recursive function calls instead of loops. 
<p>
<strong>HINT:</strong> your recursive function will probably need several arguments to make this work.
</p><p>
</p><h3><a name="b_Iterative_No_functions_no_arra"></a> b. Iterative: No functions, no arrays </h3>
Do not declare any functions of your own, and use no arrays or pointers. 
<p>
<strong>HINT:</strong> use an outer loop to count down from the input number to 0, and an inner loop to compute the appropriate fibonacci number.
</p><p>
</p><h3><a name="c_Efficient_No_functions_and_no"></a> c. Efficient: No functions, and no nested loops </h3>
You may have several loops, but no loops within loops, or any functions of your own.
<p>
<strong>HINT:</strong> use a first loop to compute and store the appropriate fibonacci sequence in an array. Use a second loop to print the numbers in the array in reverse order. 
</p><p>
<strong>Turn-in requirement:</strong> submit your programs as files called <code>hw2i3a.c</code>, <code>hw2i3b.c</code> and <code>hw2i3c.c</code> in your hw2 directory, and add the corresponding targets to the Makefile.  </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>