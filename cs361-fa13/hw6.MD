<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic">   <link href="http://alexgorbatchev.com/pub/sh/current/styles/shCore.css" rel="stylesheet" type="text/css">
  <link href="http://alexgorbatchev.com/pub/sh/current/styles/shThemeDefault.css" rel="stylesheet" type="text/css">
<script src="http://alexgorbatchev.com/pub/sh/current/scripts/shCore.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shAutoloader.js" type="text/javascript"></script>
<p>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/XRegExp.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shCore.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shAutoloader.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shBrushXml.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shBrushJScript.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shBrushCss.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shBrushCpp.js" type="text/javascript"></script>
  <script src="http://alexgorbatchev.com/pub/sh/current/scripts/shBrushBash.js" type="text/javascript"></script>
</p><p>
</p><p>
<script type="text/javascript">
     SyntaxHighlighter.all()
</script>
</p><p>
</p><p>
</p><h1><a name="Homework_6_Build_your_own_debugg"></a> Homework 6 - Build your own debugger </h1>
<p>
In this homework we'll be building a stripped down version of gdb. The template solution comes with a library for reading debugging symbols (dwarf_symbol_reader) and for processing user input (debugger_interface), allowing you to focus on developing the features.
</p><p>
</p><h3><a name="Initial_Setup"></a> Initial Setup </h3>
<p>
You'll need a few libraries first. Run the following command before trying to compile the template...
</p><p>
</p><pre name="code" class="brush: bash">    sudo apt-get install libelf-dev libdwarf-dev dwarfdump libncurses5-dev </pre>
<p>
dwarfdump is a program that displays the dwarf debugging symbols for a program. It may be helpful to you for this assignment.
</p><p>
</p><h2><a name="API_Info"></a> API Info </h2>
<p>
You'll have to use the ptrace API for this assignment along with a couple of libraries that I wrote. Familiarize yourself with these things <strong>BEFORE</strong> starting the assignment! I suggest you peek at the .c and .h files also, just to get a flavor of what is going on.
</p><p>
</p><h3><a name="Debugger_Interface_debugger_inte"></a> Debugger Interface (debugger_interface.h) </h3>
<p>
This module handles the user input to the debugger. Each command from the user has a command type and a value associated with it. For instance, if the user types "b 7" then the command type is CMD_TYPE_BREAKPOINT and the value is the line number where we want to set the breakpoint.
</p><p>
Values can be strings (for instance the name of a variable for printing) or integers so we use a union type to represent it. The union type in the user_command struct is called value. Below is an example of how to access the line_number from a user_command.
</p><p>
</p><pre name="code" class="brush: cpp">      user_command * cmd = debugger_interface_get_cmd();
      //now handle the input
      switch(cmd-&gt;command_type){
          case CMD_TYPE_BREAKPOINT:
            set_breakpoint_from_line_number(cmd-&gt;value.line_number);
            break;
          case CMD_TYPE_PRINT:
            printf("printing not implemented yet\n");
            break;
          case CMD_TYPE_CONTINUE:
            //tell the child to keep going          
            break;
        }
</pre>
<p>
</p><h3><a name="dwarf_symbol_reader_h"></a> dwarf_symbol_reader.h </h3>
<p>
This module allows you to get info about the program that you are debugging (assuming that program was compiled with dwarf debugging symbols). This includes such info as function names, function starting and ending addresses, variable names and locations, etc... The dwarf_symbol_reader.h file has lots of comments so make sure to take a look in there. <strong>For all of the parts of the assignment you will need to utilize this library!</strong>.
</p><p>
Dwarf considers each object file a "compilation unit". For this assignment we'll only have a single compilation unit because the programs we will be using are very simple. Many of the functions in dwarf_symbol_reader.h take a compilation unit, so you'll want to grab the compilation unit at the beginning of the debugging process using the function <strong>dwarf_get_compilation_unit</strong>.
</p><p>
A <strong>die</strong> (debugging information entries) contains the debugging information for a given entity in a program. So a function would have a die, a variable would have a die, and so forth. In fact, the whole compilation unit also has a die and is available in the <strong>struct dwarf_compilation_unit</strong> type as <strong>root_die</strong>. The dies are organized into a tree with the compilation unit as a root. So, if variable x is in function fun1, then x's die is a child of fun1 . Most of the functions in dwarf_symbol_reader.h take a die as a parameter.
</p><p>
One of the main things that you can do with these functions is iterate through a bunch of dies. So lets say you wanted to loop through all the function dies in your program. You would do the following
</p><p>
</p><pre name="code" class="brush: cpp;">    //start with the first child of the root die
    Dwarf_Die func_die =  dwarf_get_next_function(compilation_unit-&gt;root_die, compilation_unit);

    while(func_die){
        //do something with the function die
        //...
        //now get the next one
        func_die =  dwarf_get_next_function(func_die, compilation_unit);
    }
</pre>
<p>
There are similar iterator functions available for variables.
</p><p>
</p><h3><a name="Using_Ptrace"></a> Using Ptrace </h3>
<p>
The Ptrace library allows a debugging program to have total control over the debuggee. Using Ptrace, our debugger (via the operating system) can modify a program's instructions, read a program's memory, stop it, start it, single step it, etc... The man page for Ptrace is great and is linked below in the references. <strong>You will need to make at least 1 Ptrace call for every part of this homework</strong>.
</p><p>
</p><h3><a name="a_Setting_a_breakpoint"></a> a. Setting a breakpoint </h3>
<p>
The first thing you will need to do is set a breakpoint and have the program stop at that line. To do this you will have to modify the right instruction by replacing the low order byte with an int3 (0xCC) op code. Make sure to store away the old instruction so that you can put it back once the breakpoint has been hit. The users interaction with this functionality should look like this...
</p><p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; b 7
    breakpoint 1 set at line 7
    361db&gt;&gt; c
    continuing...
    breakpoint 1 hit
    361db&gt;&gt;
</pre>
<p>
</p><h3><a name="b_Where_am_I"></a> b. Where am I? </h3>
<p>
When debugging it is always helpful to know where you are in a certain file. For part 1 you will print out the line you are currently on and the file name. (HINT: use the instruction pointer from ptrace to figure out the line). Here is the intended output...
</p><p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; where
    line 1 in prog1.c
</pre>
<p>
</p><h3><a name="c_Persistent_breakpoints"></a> c. Persistent breakpoints </h3>
<p>
When you hit a breakpoint you must take the original instruction and put it back, thus removing your breakpoint. For part b we now make our breakpoints persistent so that they stick around. (Hint: take a look at single stepping with ptrace). The user should be able to hit the same breakpoint multiple times without having to set it more than once.
</p><p>
</p><h3><a name="d_Multiple_breakpoints"></a> d. Multiple breakpoints </h3>
<p>
Its not very fun for the user to only be able to set one breakpoint at a time. Now allow the user to have multiple breakpoints set concurrently. Here's an example of the expected output.
</p><p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; b 7
    breakpoint 1 set at line 7
    361db&gt;&gt; b 8
    breakpoint 2 set at line 8
    361db&gt;&gt;c
    hit breakpoint 1
    361db&gt;&gt;c
    hit breakpoint 2
</pre>
<p>
</p><h3><a name="e_Printing_Variables"></a> e. Printing Variables </h3>
<p>
Being able to inspect the value of a variable is an important part of debugging. For part e we will now implement the printing of variables. The p command will take two arguments: the first is the format specifier (/d for integer in decimal, /c for character, etc...) and the second is the variable name. <strong>I will only test that your program can print integers and characters</strong>. Here's the expected output.
</p><p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; b 7
    breakpoint 1 set at line 7
    361db&gt;&gt; p /d x
    101
    361db&gt;&gt; c
</pre>
<p>
</p><h3><a name="f_Printing_out_strings_15_bonus"></a> f. Printing out strings (15 % bonus) </h3>
<p>
If you can print out a single value it should be too hard to also print out a string of characters. Modify your program to do just that.
</p><p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; p /s trueStr
    "CS 361 is so much fun!"
    361db&gt;&gt; c
</pre>
<p>
</p><p>
</p><h3><a name="i_WEEK_2_Printing_out_the_stack"></a> i. (WEEK 2) Printing out the stack trace (15% Bonus) </h3>
<p>
This one should be fun. Now allow the users to see a simple stack trace after typing "bt". This should work for any number of function calls, including recursive ones. You will print the source file, line number and the input parameters. You can just assume that all input parameters are integers. Here's the output we should see given the following debuggee program...
</p><p>
</p><pre name="code" class="brush: cpp;">   
   void h(int y){
        printf("hello there: %d", y);
   }

   void g(int x){
         h(x);
   }

   int main(){
        g(10);
   }
</pre>
<p>
</p><pre name="code" class="brush: bash">    361db&gt;&gt; b 2
    breakpoint 0 set at line 2
    361db&gt;&gt; c
    hit breakpoint 0
    361db&gt;&gt; bt
    #0 h(y=10) at tests/prog5.c:2
    #1 g(x=10) at tests/prog5.c:6
    #2 main() at tests/prog5.c:10
</pre>
<p>
</p><p>
</p><h3><a name="References"></a> References </h3>
<p>
1.) Take a look at this blog entry...it should take you a long way <a href="http://www.alexonlinux.com/how-debugger-works">How a Debugger Works</a>
</p><p>
2.) <a href="http://linux.die.net/man/2/ptrace">The Ptrace man page</a>
</p><p>
3.) An in depth look into dwarf <a href="http://www.ibm.com/developerworks/opensource/library/os-debugging/index.html?ca=drs-">Debugging formats DWARF and STAB</a>
</p><p>
4.) <a href="http://www2.cs.uic.edu/~jakob/cs385s12/HW8addendum/">Walk-through of the template code</a>
</p><p>
5.) <a href="http://www2.cs.uic.edu/~jakob/cs385s12/DebuggingLecture/">Debugging Lecture</a>
</p><p>
</p><p> </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>