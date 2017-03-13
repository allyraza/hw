<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h2><a name="Homework_7_A_Basic_Web_Proxy"></a> Homework 7: A Basic Web Proxy </h2>
<p>
In this homework, we create an HTTP proxy. HTTP proxies sit between a browser and a web server - they receive the browser's request, and perform it on behalf of the browser. In the standard setup, the browser is configured to use a certain proxy - this is what we'll do here as well.
</p><p>
HTTP proxies have several uses, such as caching, compression, and anonymization. A caching web proxy stores previously loaded contents, and sends the browser a cached copy rather than requesting the document again from the server. A compression proxy typically requests the document from the server, but makes some transparent modifications to the page to improve page load times on bandwidth-limited devices like mobile phones, including downsizing and or re-compressing images.
</p><p>
Finally, an anonymizing proxy receives a request from a browser, performs the request on behalf of the browser after removing or replacing identifying information, and delivers the response back to the user. This is a particularly important service in countries where censorship blocks access to certain websites, but has its elsewhere as well.
</p><p>
</p><h2><a name="Setup"></a> Setup </h2>
<p>
Most of our experiments will be done using <code>wget</code> on the command line. <code>wget</code> is a command line http client, which simply fetches the document pointed to by a supplied URL. For example, =wget <a href="http://www.google.com=" target="_top">http://www.google.com=</a> fetches Google's front page, and stores it in a local file.
</p><p>
To configure wget to use a proxy, simply set the environment variable <code>http_proxy</code> to point to your proxy, like this <code>export http_proxy=http://localhost:8080</code>, for example. This will redirect all wget requests to port 8080 on the local machine, which is then responsible for servicing the request however it sees fit. Try it out by starting an <code>nc</code> server listening on that port and then issuing a request with <code>wget</code>. You should see the HTTP request on the <code>nc</code> console. You can also type in a response on the <code>nc</code> console and hit <code>ctrl-d</code> if you'd like.
</p><p>
For browsers, proxy settings differ between browsers and OS'es. Look up the http proxy settings, and point it at localhost port 8080 to get the same effect in a browser. In OS X, I use Firefox, which allows me to use a "manual" proxy setting - there's something wrong with the system proxy settings on my machine.
</p><p>
Note, however, that browsers have fairly specific and complex requirements on proxy operations. In particular, browsers expect persistent connections to their proxies, which complicates things. For this homework, we focus on evaluation with <code>wget</code>.
</p><p>
</p><h2><a name="Assignment_Details"></a> Assignment Details </h2>
<p>
Your job for this assignment is to create a basic HTTP proxy, with some rudimentary anonymization services. One of the more challenging tasks is that the proxy needs to work well even if the server on the other end is being difficult.
</p><p> </p><ol>
<li> Handle a basic HTTP request with wget, forwarding the request and returning the full server response to the client.
</li> <li> Handle server failures: in cases where the server cannot be reached, return proper error pages rather than crashing, hanging, or otherwise misbehaving.
</li> <li> Handle concurrent HTTP sessions. While one (slow) HTTP request is being served, promptly serve several faster requests.
</li> <li> Anonymization: remove any Cookie headers, and replace the User-Agent with something non-identifying.
</li></ol> 
<p>
</p><h2><a name="Test_Cases"></a> Test Cases </h2>
<p>
This set of test cases will grow over the coming days.
</p><p>
1. Basic
</p><p>
</p><pre>wget http://www.google.com
</pre>
<p>
2. Server failures
</p><p>
</p><pre>wget http://hostdoesnotexist.cs.uic.edu/

wget http://words.cs.uic.edu/doesnothaveawebserver/
</pre>
<p>
3. Start a bogus web server on port 9090:
</p><p>
</p><pre>nc -l 9090

wget http://localhost:9090/ &amp;
sleep 1;
time wget http://www.google.com;
</pre>
<p>
This should report a very short time to fetch google.com, not block awaiting the response from the bogus server.
</p><p>
4. Anonymization (sort of):
</p><p>
Start a packet capture with Wireshark or tcpdump, then fetch <a href="http://www.google.com" target="_top">http://www.google.com</a> with a browser configured to use the proxy. There should be no Cookie: headers in the request going to google, and the User-Agent should contain the word CS361.
</p><p>
&lt;/verbatim&gt;
</p><p>
</p><h2><a name="Turn_in_Instructions"></a> Turn-in Instructions </h2>
<p>
Create and add a directory called hw7 in your turn-in folder, in which you place a file called hw7.c. Add a Makefile that compiles hw7.c into an executable called <code>hw7</code>. </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>