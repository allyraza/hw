<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h1><a name="Homebrew_file_system"></a> Homebrew file system </h1>
<p>
In this homework, we create our own filesystem kernel module. The template code provides a "skeleton" file system module, which can be loaded and mounted. However, although it has all the pieces you need, it doesn't do what we want, and that's where you come in.
</p><p>
To try out the template code, you will need the virtual machine and custom kernel that you set up in homeworks 1 and 2. Check out the template, and run <code>make</code> to build the module. Assuming that worked, you can now run:
</p><p>
<code>sudo insmod ./hw9fs.ko</code>
</p><p>
to load the module. To see if the module is loaded, take a look in <code>/proc/filesystems</code> and look for <code>hw9fs</code>. Also, try running <code>tail /var/log/messages</code>, to see some debug output. With the module loaded, we can now use our filesystem. Run
</p><p>
<code>sudo mount -t hw9fs -o ro,loop test.img mnt</code>
</p><p>
to mount the disk image <code>test.img</code> in read-only mode, using our filesystem <code>hw9fs</code>, and
</p><p>
<code>sudo mount -t hw9fs -o loop test.img mnt</code>
</p><p>
for read-write access (the last several parts below). Read-only access is less demanding, you might want to try that first.
</p><p>
The directory <code>mnt</code>, which used to be a regular directory, now contains our mounted filesystem. See if your output looks like mine:
</p><p>
</p><pre>jakob@ubuntu:~/hw9$ ls mnt
ls: cannot access mnt/nonexisting_file: No such file or directory
existing_file  nonexisting_file
</pre>
<p>
Clearly, there is something wrong with <code>nonexisting_file</code>, but let's not worry about it. Let's see what's in <code>existing_file</code>.
</p><p>
</p><pre>jakob@ubuntu:~/hw9$ cat mnt/existing_file
File 3 comes second to last, and it is a long file.
File 3 comes second to last, and it is a long file.
File 3 comes second to last, and it is a long file.
...
File 3 comes second to last, and it is a long file.
File 3 comes second to last, and it jakob@ubuntu:~/hw9$
</pre>
<p>
If you got this far, you're ready to get started. To remove the module, first unmount the filesystem:
</p><p>
<code>sudo umount mnt</code>
</p><p>
then unload the module
</p><p>
<code>sudo rmmod hw9fs</code>
</p><p>
</p><h2><a name="Disk_Format"></a> Disk Format </h2>
<p>
Let's take a peek at the disk image <code>hexdump -C test.img</code>. It consists of two types of 1024-byte blocks: a single disk header block (superblock) which comes first, followed by a number of data blocks. The header consists of up to 30 adjacent structs like this:
</p><p>
</p><table cellspacing="0" id="table1" cellpadding="0" class="twikiTable" rules="all" border="1">
        <tbody><tr class="twikiTableOdd twikiTableRowdataBgSorted0 twikiTableRowdataBg0">
            <th bgcolor="#687684" valign="top" class="twikiTableCol0 twikiFirstCol"> <a rel="nofollow" href="/bin/view/CS385spring12/Homework9?sortcol=0;table=1;up=0#sorted_table" title="Sort by this column"><font color="#ffffff">Filename</font></a> </th>
            <th bgcolor="#687684" valign="top" class="twikiTableCol1 twikiLastCol"> <a rel="nofollow" href="/bin/view/CS385spring12/Homework9?sortcol=1;table=1;up=0#sorted_table" title="Sort by this column"><font color="#ffffff">Size</font></a> </th>
        </tr>
        <tr class="twikiTableEven twikiTableRowdataBgSorted0 twikiTableRowdataBg0">
            <td bgcolor="#ffffff" valign="top" class="twikiTableCol0 twikiFirstCol twikiLast"> char[26] </td>
            <td bgcolor="#ffffff" valign="top" class="twikiTableCol1 twikiLastCol twikiLast"> int </td>
        </tr></tbody></table>
<p>
The header is then followed by the file contents. Each file uses one or more consecutive, full blocks. Though the file may be smaller than a 1024-byte block, the block is zero-padded so that the next file starts on an even block boundary. This filesystem does not support subdirectories.
</p><p>
You can create your own disk images using the included mkcs385fs tool. For example, <code>mkcs385fs test_directory/ test.img</code> creates the supplied disk image.
</p><p>
<strong>HINT:</strong> check your logs in a separate window, using <code>tail -f var/log/kern.log</code>. You will be docked points for kernel warning messages appearing in this file (not your debug output).
</p><p>
</p><h2><a name="1_Directory_Listing_3_pts"></a> 1. Directory Listing (3 pts) </h2>
<p>
Update the module to show a correct file listing. The order is not important, but both <code>ls mnt</code> and <code>ls -l</code> mnt should show no error messages or question marks. For an example output, try <code>ls -l test_directory</code>. Filename and size must be correct, and the files must be readable, the rest is not important, but no question marks or error messages are allowed.
</p><p>
</p><h2><a name="2_File_contents_2_pts"></a> 2. File contents (2 pts) </h2>
<p>
Update the module to support correct listing of file contents with <code>cat</code>. To do this, you will mostly need a way to map a "file block" into a disk block. The output of <code>cat mnt/*</code> should be identical to <code>cat test_directory/*</code>.
</p><p>
</p><h2><a name="3_File_creation_2_pts"></a> 3. File creation (2 pts) </h2>
<p>
Support the creation of new files in the mounted directory. Again, our filesystem does not support directories, so all you need to handle is regular file creation. Test it like this:
</p><p>
</p><pre>touch mnt/mynewfile
ls -l mnt
</pre>
<p>
you should now see "mynewfile" appear in the listing, with a size of zero.
</p><p>
<strong>hint:</strong> you'll need to add a function pointer to your inode_operations struct.
</p><p>
</p><h2><a name="4_Persistent_file_creation_4_pts"></a> 4. Persistent file creation (4 pts) </h2>
<p>
Make sure your file still exists after unmounting and re-mounting your image. To do this, you'll need to write out your updated superblock to disk.
</p><p>
<strong>hint:</strong> This template does not memcpy the superblock to a kmalloced bit of memory. Instead, it holds on to the buffer_head* from sb_bread. See how other filesystems (fat or ext2) use <code>sync_dirty_buffer</code> to write this out to disk in an easy way. Double-check your updated disk image with <code>hexdump -C test.img | less</code>
</p><p>
</p><h2><a name="5_Writing_to_files_2_pts"></a> 5. Writing to files (2 pts) </h2>
<p>
Support writing data to files. Test this as follows:
</p><p>
</p><pre>echo my test &gt; mnt/testfile
ls -l mnt
cat mnt/testfile
</pre>
<p>
the <code>ls -l</code> should show the new file with size 8, and the <code>cat</code> should output "my test". Make sure that your written output survives an unmount/mount.
</p><p>
<strong>hint:</strong> you'll need to add several function pointers to your address_space_operations and file_operations. Look at the <code>fat</code> implementation to get some ideas.
</p><p>
</p><h2><a name="6_Writing_large_files_2_pts"></a> 6. Writing large files (2 pts) </h2>
<p>
Make sure you can handle writes of more than one block correctly. Try <code>cat hw10fs.c &gt; mnt/testfile</code> to try with a large file.
</p><p>
</p><h2><a name="7_Handle_out_of_space_errors_cor"></a> 7. Handle "out of space" errors correctly (1 pts) </h2>
<p>
Our filesystem does not support growing files that are "wedged" between other files (we use contiguous allocation without any support for moving files around). Make sure writing to a "wedged" file does not overwrite the contents of other files, and instead makes the terminal display "out of space" or some other user-friendly error.
</p><p>
</p><h2><a name="HINTS"></a> HINTS </h2>
<p>
Kernel programming is a different beast. There is no printf, no malloc, no math library, etc. Sometimes there are alternatives: printk and kmalloc, for example, but library support is limited within the kernel.
</p><p>
If you make a mistake in a kernel module, you may crash the kernel, hang your program (permanently, unkillably), get the kernel into a funky state, wipe your whole disk, or get pleasantly kicked out by the kernel with no ill effects, all depending on how unlucky you get. Use VMWare's "Snapshot" facility regularly, and consider editing your code outside of the VM, and copying it into the VM for each test (using scp or rsync). You'll likely get to restart your VM a bunch of times even if you take the precautions.
</p><p> </p><ul>
<li> Excellent intro document here: <a href="http://thecoffeedesk.com/geocities/rkfs.html" target="_top">simple file system</a>
</li> <li> The <a href="http://lxr.linux.no/linux+v2.6.38/include/linux/fs.h" target="_top">fs.h - all the main filesystem structs are in here</a>
</li> <li> <a href="http://lxr.linux.no/linux+v2.6.38/fs/befs/linuxvfs.c" target="_top">BeFS implementation - I used this to learn how to do things</a>
</li> <li> <a href="http://lxr.gwbnsh.net.cn/linux+linux-2.6.38/fs/befs/linuxvfs.c" target="_top">alternative link for the above</a>
</li></ul> 
<strong>This homework requires very little coding:</strong> However, it will take a lot of looking at other kernel code, and probably a bunch of reboots, before you get it right.
<p>
</p><h2><a name="Debugging_Kernel_Code"></a> Debugging Kernel Code </h2>
<p>
A first great step is to increase the kernel log level:
</p><p>
<code>sudo sysctl kernel.printk=7</code>
</p><p>
Next, switch your virtual machine to a text console, by hitting ctrl-alt-f1, or cmd-ctrl-fn-f1 on a mac. This is for monitoring kernel output only: do not use this console for running things or editing text.  </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>