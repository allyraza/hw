<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Homework_4_l337_h4xx0r_5killz_cr"></a> Homework 4: l337 h4xx0r 5killz - cracking a protected binary </h2>
<p>
In this homework, we learn about the structure of binary programs by practicing our reverse-engineering skills. A binary program is provided (unique to each student). The program is meant to accept a license key on the command line, verify the key locally, and then call in to a server for activation, after which point the program runs.
</p><p>
Unfortunately, you seem to have misplaced your license key. Thus....
</p><p>
<iframe width="280" height="100" src="//www.youtube.com/embed/tGSUjuSBt1A" frameborder="0"></iframe>
</p><p>
<em>Your mission, should you choose to accept it, is to subvert this program into running correctly without a correct license key, and to do so without calling in to the activation server, revealing your top-secret location.</em>
</p><p>
More specifically, you are to modify this binary executable and library, changing only a few bytes of the provided binary, to make it appear to work normally, except that it accepts any license key, and does not contact the activation server when run.
</p><p>
</p><h2><a name="Getting_Started_Cracking"></a> Getting Started Cracking </h2>
<p>
There is no source code provided, nor are you expected to turn in source code for this homework. Instead, we analyze and modify an existing binary. Our main tools for this job: <code>gdb</code>, <code>objdump --disassemble</code>, and <code>readelf -a</code> to analyze and reverse-engineer the program. To edit the program, you may use your hexadecimal editor of choice.
</p><p>
One nice hex editing solution is this: convert the binary to an editable ASCII file with <code>xxd</code>. Edit the file with any editor. Convert back to binary with <code>xxd -r</code>. Don't forget to <code>chmod +x</code> the final file if you want to run it, xxd doesn't do that by default.
</p><p>
<strong>One or more of the protection mechanisms in this homework are incompatible with the new address space randomization system in Linux. This makes the template binary crash. Always run your program like this:</strong>
</p><p>
</p><pre>LD_LIBRARY_PATH=. setarch `uname -m` -R ./hw4
</pre>
<p>
<strong>Note:</strong> you are expected to edit the binary executable and library, not produce a binaries by reverse-engineering and re-writing in C, nor by disassembling and reassembling. We'll compare the turned-in binary to the original with <code>cmp</code>, and we expect to see only several modified bytes.
</p><p>
</p><h2><a name="A_bit_of_help_along_the_way"></a> A bit of help along the way </h2>
<p>
The supplied program contains four protection mechanisms that you need to subvert. After you have subverted the first one (a simple key check), the program outputs
</p><p>
<code>License key valid, thank you.</code>
</p><p>
The second one dynamically updates a GOT entry to make the program call real_server_license_validation, which is what you want, instead of what the entry points to in the binary. After you have subverted the second one (this could happen in one step, depending on your approach), it outputs:
</p><p>
<code>Everything seems to be in order. Moving along to server license key validation.</code>
</p><p>
Your program then "activates" with the license server, which reports activations on this page: <a href="http://bits.cs.uic.edu/cs361/activations.txt" target="_top">http://bits.cs.uic.edu/cs361/activations.txt</a> 
</p><p>
You'll note that the server accepts any license key. However, the most insidious aspect of the report is the IP address, which identifies you as the license violator, and which is not within your control to change. You must stop this activation from happening. Important function calls for the network activation are <code>connect()</code> and <code>send()</code>.
</p><p>
However, you'll find that simply skipping the network activation step results in a broken program: the server sends back binary code with crucial functionality as part of the activation process. You need to capture this binary code, and store it permanently in your program so it can run without activation.
</p><p>
Without the code from the server, the program crashes or doesn't do anything. With the code, it displays a little ASCII animation.
</p><p>
The cracked binaries differ in roughly 20 bytes total, and the program runs without activating with the server. 
</p><p>
</p><h2><a name="New_checkout_and_turn_in_instruc"></a> New checkout and turn-in instructions </h2>
<p>
For this homework, a new directory has already been created in your turn-in folder, called hw4. To retrieve it, go to your turn-in folder and type <code>svn up</code>. The folder contains a binarie (hw4) and a shared library (lib.so). It may be a good idea to keep a copy of the original files around for reference, though if you misplace them, it's always available through svn. 
</p><p>
Make your changes to hw4, and lib.so and <code>svn commit</code> when finished. In addition, create a new file called "patches_applied.txt", where you describe each change you made briefly, in the format <range of="" bytes=""> <purpose or="" intent="" of="" modification="">, like this:
</purpose></range></p><p>
<code>hw4: 0af8-0b70 replaced foo with bar to make a better foobar</code> </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>