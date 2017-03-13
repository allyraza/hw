<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Homework_1_Getting_Started_and_A"></a> Homework 1: Getting Started, and Analyzing Dynamic Memory Usage </h2>
<p>
This homework has two main parts. Part one is making sure you are able to log into your Amazon EC2 virtual machine, as well as checking out the homework template from svn, and committing files to your turn-in repository.
</p><p>
In step 2, we do a little bit of analysis of dynamic memory usage by malloc and the stack.
</p><p>
</p><h3><a name="Getting_Started_with_Amazon_EC2"></a> Getting Started with Amazon EC2 </h3>
<p>
You should have received two emails by now, one with your Amazon AWS credentials, and one with your turn-in subversion repository credentials. If you did not receive these, check your spam folder. If it's not there either, contact Jakob immediately.
</p><p>
While you are free to use any linux machine for your homework projects, you have been provided with a free Amazon EC2 virtual machine, which provides a consistent and reliable environment to work with. All grading will be done using this platform, so to be safe, you'll probably want to use it to test your programs as well.
</p><p>
Follow <a href="https://jakob.signin.aws.amazon.com/console" target="_top">this link</a> and instructions provided in the Amazon credentials email to start your virtual machine. If you can't find your VM in the list, try switching the "zone" in the top right corner to "N.Virginia".
</p><p>
Then log into it using ssh from your computer. Attached to the email was a file named id_rsa, use that as the private key or identity file when logging into your VM. Your username for the ssh login is "ubuntu". There is no password (the id_rsa file is used instead of a password).
</p><p>
You'll want to install some programs on your VM. To get the essentials, run these commands:
</p><p>
<code>sudo apt-get install build-essential</code>
</p><p>
<code>sudo apt-get install subversion</code>
</p><p>
</p><h3><a name="Getting_Started_with_Subversion"></a> Getting Started with Subversion </h3>
<p>
For this class, we use the subversion revision control system to handle homework templates and turn-ins. Every student has their own individual turn-in repository, where you are expected to commit your homework solutions. There is also a shared repository, at svn://bits.cs.uic.edu/cs361/pub, which contains class materials such as homework templates, previous homework solutions, drawings from lecture, etc.
</p><p>
To check out your personal turn-in repository, which will be empty at this point, go to the directory where you would like the new repository folder to appear. Then type
</p><p>
<code>svn checkout svn://bits.cs.uic.edu/cs361/f13/USERNAME --username USERNAME</code>
</p><p>
where <code>USERNAME</code> obviously is your svn username. This creates a folder called <code>USERNAME</code>, with a hidden <code>.svn</code> folder inside it.
</p><p>
To check out the first homework template, cd to this folder, and type (pay attention!)
</p><p>
<code>svn export svn://bits.cs.uic.edu/cs361/pub/homeworks/hw1</code>
</p><p>
note that it says <code>export</code>, not <code>checkout</code>. This is a very important detail: <em>never</em> use checkout to get your homework template. It'll cause you (and us) all manner of headaches.
</p><p>
This creates a new folder called hw1. To commit the template as your homework solution (you actually get points for this, this time only!), type
</p><p>
<code>svn add hw1</code>
</p><p>
to tell subversion that hw1 is a folder (including its current contents) that svn should keep track of for you. Then, type
</p><p>
<code>svn commit -m "my very first commit"</code>
</p><p>
to tell svn that this version of the folder is something svn should remember. Note that every new file or folder that you want to have in your repository needs to be "added" once, and every version you want to store needs to be "committed". svn does not add files or commit versions for you automatically.
</p><p>
</p><h3><a name="Dynamic_Memory_Usage_Diagnostics"></a> Dynamic Memory Usage Diagnostics </h3>
<p>
The template provides a couple of small programs that allocate memory according to different patterns. These programs periodically call the function <code>check_memory()</code> which, at the moment, does nothing useful at all. Your job is to change <code>check_memory()</code> and <code>init_hw1()</code> in hw1.c so that both <code>iterative</code> and <code>recursive</code> produce the following output on <code>stderr</code>.
</p><p> </p><ul>
<li> heap segment size: total size of the current heap segment in bytes
</li> <li> number of allocated <code>malloc()</code> chunks on the heap.
</li> <li> number of free <code>malloc()</code> chunks on the heap.
</li> <li> total bytes in allocated chunks.
</li> <li> total bytes in free chunks.   
</li> <li> current stack size: total number of bytes used by the stack at present. Note: this is not the segment size, just the current stack size. 
</li></ul> 
<p>
To test your program, type <code>make</code> and then run either <code>./iterative</code> or <code>./recursive</code>.
</p><p>
The output format should be space-separated decimal numbers on a single line per call to <code>check_memory()</code>. You may estimate the location of the top of the stack, and the bottom of the heap, by recording the current bottom of the stack and top of the heap in   <code>init_hw1()</code>. 
</p><p>
<strong>hint:</strong> sbrk(0) tells you the current top of the heap. 
</p><p>
<strong>hint2:</strong> for compatibility across platforms, use the type size_t to represent the boundary tags, rather than manually choosing a 32-bit or 64-bit type. This is what malloc does anyway. 
</p><p>
</p><h3><a name="Turn_in_instructions"></a> Turn-in instructions </h3>
<p>
To prove that you got subversion working, you just have to commit the hw1 template to your personal turn-in repository following the instructions above. 
</p><p>
To prove that you got your EC2 instance up and running, and that you logged in successfully, copy-paste the output of the following two commands to a new file called "EC2.txt" in your hw1 directory. 
</p><p>
<code>uname -a</code>
</p><p>
<code>who</code>
</p><p>
Don't forget to <code>svn add EC2.txt</code> and <code>svn commit</code> with a message, to complete the turn-in. 
</p><p>
Finally, commit your updated homework template, producing the correct output, to receive the full score on this homework. 
</p><p>
<strong>Your final work must be committed to your turn-in repository by 11 am Tuesday, <em>before</em> the lab starts.</strong>
</p><p>
</p><h3><a name="Output_example"></a> Output example </h3>
<p>
This is an example of the exact format of output that should appear on stderr:
</p><p>
</p><pre>135160 1 0 144 0 108
135160 2 0 432 0 108
135160 3 0 848 0 108
135160 4 0 1408 0 108
135160 5 0 2096 0 108
135160 6 0 2928 0 108
135160 7 0 3888 0 108
135160 8 0 4992 0 108
135160 9 0 6224 0 108
135160 10 0 7600 0 108
</pre>
<p>
these are the first few lines from my solution running with the 'iterative' program. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>