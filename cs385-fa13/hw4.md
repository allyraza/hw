<div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_4_homebrew_command_line"></a> Homework 4 - homebrew command line interpreter </h1>
<p>
The command line interpreter, or "shell" in Unix is an incredibly powerful tool in the hands of an experienced user. Its main function is to providing an intuitive and efficient way to combine many small commands to create new functionality. 
</p><p>
In this homework, we will create our own shell, supporting many of the basic functions available in <code>bash</code> and other popular shells. 
</p><p>
Copy the hw4 template to your turn-in directory thus:
</p><p>
<code>svn export svn://bits.cs.uic.edu/cs385/pub/homeworks/hw4</code>
</p><p>
<code>svn add hw4</code>
</p><p>
You will also need to install the readline developer files:
</p><p>
<code>sudo apt-get install libreadline-dev</code>
</p><p>
</p><p>
</p><h2><a name="PATH_support"></a> PATH support </h2>
<p>
The template code requires the absolute path of the binary you want it to run. Change it to automatically look for the program in all of the directories indicated by PATH, except for filenames that contain a '/'. Thus, make <code>ls</code> do the same thing as <code>/bin/ls</code>, but also make sure that <code>mydir/mybinary</code> still works correctly.
</p><p>
<strong>HINT</strong>: <code>getenv()</code> to get the environment variable, then <code>strsep()</code> to split it into multiple path strings. Finally, <code>sprintf()</code> to compose a full path out of its components. 
</p><p>
</p><h2><a name="Commands_with_command_line_argum"></a> Commands with command-line arguments </h2>
<p>
Support up to 10 command line arguments. For example <code>echo hello world</code>, should produce <code>hello world</code>.
</p><p>
<strong>HINT</strong>: you could use <code>strsep()</code> to split the arguments into an array, which you then pass to <code>execve()</code>.
</p><p>
</p><h2><a name="Redirection_to_and_from_files"></a> Redirection to and from files </h2>
<p>
Support stdin and stdout redirection to and from files. For example, <code>ls &gt; /tmp/templ</code> should create a file (with correct permissions) containing the output of ls. Similarly <code>wc &lt; /tmp/templ</code> should use the file as input, and <code>wc &lt; /tmp/templ &gt; /tmp/count</code> uses both input and output redirection.
</p><p>
<strong>HINT</strong>: use <code>open()</code> to open a file, and <code>dup2()</code> to change where stdin(0) or stdout(1) points to.
</p><p>
</p><h2><a name="Piping"></a> Piping </h2>
<p>
Support piping of the stdout from one command to stdin to another. For example:
</p><p>
<code>ls -l | sort -n -k 5 | cut -c 27-34 &gt; /tmp/sizes</code>
</p><p>
produces a file containing a sorted list of file sizes. 
</p><p>
<strong>HINT</strong>: this is by far the most challenging part of the homework. Use <code>fork()</code> as in the template code to start up multiple concurrent processes, <code>pipe()</code> to create pipes through which processes communicate, and <code>dup2()</code> to redirect output into and out of pipes. Finally, use <code>waitpid()</code> to wait for child processes to finish.
</p><p>
</p><h2><a name="Variable_substitution"></a> Variable substitution </h2>
<p>
The template code already supports interpreted scripts. There are a couple of examples in the template directory, ending with .hw4. Add support for command line arguments to such scripts. For example, 
</p><p>
</p><pre>./echo.hw4 hello world
hello world hello
</pre>
<p>
Replace any occurrence of $1,$2,$3 etc with the first, second, third command line argument respectively.
</p><p>
<strong>HINT</strong>: this one will require some manual string manipulation, but <code>strchr()</code> to find each "$", and <code>strncpy()</code> to copy part or all of strings is a good start.
</p><p>
</p><h2><a name="Testing_your_code"></a> Testing your code </h2>
<p>
Try running ./test.hw4. Below is the expected output. Of course, the results from "ls" and the number of files will vary depending on what's in your directory.
</p><p>
</p><pre>./test.hw4
* Echo seems to work
* Now the directory contents:
Makefile   echo.hw4   hw4      hw4.c      hw4.dSYM   hw4.sh~      test.hw4
* Now the number of files:
       7
* Now we should see "Hello World":
Hello World
* And now the contents of /tmp/countfile
       2
* Now a list of file sizes

     25 
     81 
    102 
    157 
    630 
   3377 
  15336 
* And finally "hello world hello world"
hello world hello world
</pre> </div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div>