<div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_1_First_Steps"></a> Homework 1 - First Steps </h1>
<p>
In this homework we set up the class environment, and practice some C programming. There are many things to do in this homework, and some things can take a lot of time to download or install, so make sure you start early.
</p><p>
</p><h2><a name="Install_VirtualBox_and_Ubuntu_11"></a> Install <a href="/bin/view/CS385spring12/VirtualBox" class="twikiLink">VirtualBox</a> and Ubuntu 11.10 32-bit </h2>
<p>
All homeworks in this class will be done in C under Linux, and homeworks will be tested and graded on a Linux machine. To make sure your program runs the same on Tim's machine as it does on yours, you need to run the latest version of Ubuntu on a 32-bit x86 PC. To make sure everyone has the same environment, we will use a virtual machine under <a href="/bin/view/CS385spring12/VirtualBox" class="twikiLink">VirtualBox</a>. If you prefer, you may also use VMWare or Parallels, at your own risk.
</p><p>
Download <a href="/bin/view/CS385spring12/VirtualBox" class="twikiLink">VirtualBox</a> from <a href="http://www.virtualbox.org" target="_top">here</a>.
</p><p>
You can download the lastest version of Ubuntu from <a href="http://www.ubuntu.com/desktop/get-ubuntu/download" target="_top">here</a>
</p><p>
<strong>TURN-IN REQUIREMENT:</strong> When the installation is complete take a snapshot from the <strong>host machine</strong>. Save the image as hw1i1.png, to be turned in together with the rest of this homework.
</p><p>
</p><h2><a name="Check_out_your_turn_in_directory"></a> Check out your turn-in directory using subversion </h2>
<p>
Every registered student has their own directory in the course subversion repository. To check out a copy of your directory, use the following command <strong>in your virtual machine</strong>:
</p><p>
<code>svn co svn://bits.cs.uic.edu/cs385/s12/YOURID --username YOURID</code>
</p><p>
then copy the template for homework 1 to your submission directory, and change to this directory to start working on the programming assignment:
</p><p>
<code>cd YOURID</code>
</p><p>
<code>svn export svn://bits.cs.uic.edu/cs385/pub/homeworks/hw1</code>
</p><p>
<code>svn add hw1</code>
</p><p>
<code>svn commit hw1 -m "first commit"</code>
</p><p>
<code>cd hw1</code>
</p><p>
<a href="/bin/view/CS385spring12/Subversion" class="twikiLink">Here are additional instructions on using svn.</a> When you are done with the assignment, all required files should be committed to the repository.
</p><p>
If you have added any files (such as the screenshot), you need to first add this for svn tracking thus:
</p><p>
<code>svn add THEFILE</code>
</p><p>
files that aren't added with an explicit "add" are not managed by svn, and will not be "turned in". Then, to commit a version, do
</p><p>
<code>svn commit -m "An short but informative description of this revision"</code>
</p><p>
Note that you can commit any number of revisions, only the most recent one before the submission deadline will be used for grading. To check the status of your files, use 
</p><p>
<code>svn status</code>
</p><p>
the letter in the left column indicates whether a file is being managed, and if so what it's current status is (updated in the repository, updated on your current machine, just added, etc). 
</p><p>
<strong>TURN-IN REQUIREMENT:</strong> When you're done with the homework, make sure you did it right by following the instructions in the last section below.
</p><p>
</p><h2><a name="C_Program_processing_student_rec"></a> C Program: processing student records </h2>
<p>
The there will be several files already in the hw1 directory when you check out from svn. The header file hw1.h contains prototypes for the functions you will implement and should not be edited. The hw1.c file is where you will provide the implementations for each required function. For each part below, a separate file (hw1i2a through d.c) contains the main() function that calls your code. 
</p><p>
All of the questions will operate on the Student type defined in hw1.h. The type definition looks like this:
</p><p>
</p><pre>typedef struct {
   int identifier;
   char grade;
   char name[30];
} Student;
</pre>
<p>
<strong>NOTE:</strong> For this homework only, DO NOT use any built-in functions like: strlen, memcpy, strcpy, sprintf, sscanf etc. except where noted. 
</p><p>
</p><h3><a name="a_Writing_to_the_Screen_Using_pr"></a> a. Writing to the Screen Using printf </h3>
 Implement the function <code>printStudent(Student s)</code>. Using printf, write out the entire structure out byte by byte in hexadecimal format. Next, write to the screen each field of the Student structure in the format described below. 
<p>
<strong>Example usage:</strong>
</p><pre>Student st = {1, 'A', "Dennis Ritchie"};
printStudent(st);
</pre> 
<p>
<strong>example output from hw1i2a:</strong> 
</p><pre>01 00 00 00 41 44 65 6e 6e 69 73 20 52 69 74 63 68 69 65 00 00 00 00 00 00 00 00 00 ...
ID: 1
Name: Dennis Ritchie
Grade: A
</pre>
<p>
</p><h3><a name="b_Rename_a_student"></a> b.  Rename a student </h3>
<p>
Implement the function <code>renameStudent(Student s, char* newName)</code>. Replace the name in the Student record, and return the record. 
</p><p>
<strong>Example hw1i2b output:</strong>
</p><pre>Original record:

01 00 00 00 41 44 65 6e 6e 69 73 20 52 69 74 63 68 69 65 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ID: 1
Name: Dennis Ritchie
Grade: A

Renaming to "Hu Li"

01 00 00 00 41 48 75 20 4c 69 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
ID: 1
Name: Hu Li
Grade: A

Renaming to "Balakrishnan Radhakrishnan"

01 00 00 00 41 42 61 6c 61 6b 72 69 73 68 6e 61 6e 20 52 61 64 68 61 6b 72 69 73 68 6e 61 6e 00 00 00 00 00
ID: 1
Name: Balakrishnan Radhakrishnan
Grade: A


</pre>
<p>
<strong>HINT:</strong> Every C string is (and must be) terminated by a zero byte. 
</p><p>
</p><h3><a name="c_Print_a_compact_description_of"></a> c.  Print a compact description of a student record </h3>
<p>
Implement the function <code>printStudentShort(Student s)</code>, to print a shorter description of the student. You can expect all student names to be structured have the format <code>"<first> <last>"</last></first></code>.
</p><p>
<strong>Example output from hw1i2c</strong>:
</p><pre>1. D. Ritchie: A
2. T. Merrifield: B
3. J. Eriksson: C
</pre>
<p>
</p><h3><a name="d_Sort_student_records_by_grade"></a> d. Sort student records by grade </h3>
<p>
Implement the function <code>sortStudentRecords(Student *students, int count)</code>, which sorts the <code>count</code> records in the students array by grade, with A first, and F last. 
</p><p>
<strong>HINT</strong>: The list won't be very long, so a simple bubble sort will do just fine.
</p><p>
</p><h2><a name="Know_the_size_of_things"></a> Know the size of things </h2>
<p>
For this assignment, turn in a text file called hw1i3.txt. For each of the following types list the size of the type (in bytes), and the size of a pointer to that type.
</p><p>
</p><pre>char
char*
unsigned char
short
int
unsigned int
struct coordinate {int x,y; };
struct pair { struct coordinate from, to; };
union { int a; short b; char c; }
enum { ONE=1; TWO=2; THREE=3; }
</pre>
<p>
For example, your answer should contain the line:
</p><pre>char 1 4
</pre> because the size of a char is 1 byte, and the size of a pointer to a char, on a 32-bit machine, is 4 bytes.
<p>
<strong>HINT</strong>: You can have gcc help you with this homework. The C operator sizeof(x) returns the size of a variable or type passed to it. For example, sizeof(signed char)==1. Be sure you understand <em>why</em> a certain type has a certain size though. 
</p><p>
<strong>TURN-IN REQUIREMENT:</strong> For this assignment, write your answers in a text file called hw1i3.txt.
</p><p>
</p><h2><a name="A_peek_into_the_inner_bowels_of"></a> A peek into the inner bowels of C </h2>
<p>
Given the following program.
</p><p>
</p><pre>int i=257;
int *ip=&amp;i;

main() {
 char c = (char)i;
 char *cp = (char*)ip;
}
</pre>
<p>
what is the assembly code corresponding to the line:
</p><p>
</p><pre> char c = (char)i;
</pre>
<p>
what is the assembly code corresponding to the line:
</p><p>
</p><pre> char *cp = (char*)ip;
</pre>
<p>
There is a difference in the opcodes used for these two assignments. What is the difference, and how does this difference affect the resulting value in the destination variable?
</p><p>
<strong>HINT:</strong> use gcc -S like we did in class.
</p><p>
<strong>TURN-IN REQUIREMENT:</strong> For this assignment, supply your answers in a text file called hw1i4.txt.
</p><p>
</p><h2><a name="To_check_that_your_turn_in_is_pr"></a> To check that your turn-in is properly turned-in </h2>
<p>
"cd" to an empty directory, and re-check-out your homework submission:
</p><p>
<code>svn co svn://bits.cs.uic.edu/cs385/s12/YOURID/hw1</code>
</p><p>
once you're satisfied that all your submission files are in the hw1 directory, you can delete this directory: it is forever preserved in the svn. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div>