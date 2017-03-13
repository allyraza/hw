<div id="patternMainContents"><div class="twikiContentHeader"></div><div class="patternContent"><div class="patternTopic"> <h1><a name="Homework_6_elevator_scheduling"></a> Homework 6 - elevator scheduling </h1>
<p>
<em>This is our first 10 point, 2 week homework. Compared to our previous (5 point) homeworks, there will be less emphasis on basic programming skills (which it is hoped you have acquired enough of by now), and more on algorithmic or system particulars. While the homework is due 2 weeks from now, you are encouraged to start early, so you can take full advantage of office hours.</em>
</p><p>
This time, we continue our work with the elevator controller, based on the solution for hw5. 
</p><p>
However, this time, the multithreaded/concurrent programming aspects are less of a concern (they are mostly taken care of by the hw5 solution), and scheduling is our focus. A few things have changed, to make things a little more interesting:
</p><p> </p><ul>
<li> like in a normal building, passengers are more likely to travel to or from the bottom floor.
</li> <li> passengers take several trips on the elevator, separated by a short delay. Except for part 4, this delay grows linearly with the passenger number. 
</li> <li> each run has a fixed duration, rather than a fixed number of trips
</li> <li> our goal is to maximize throughput (number of trips), under different sets of constraints.
</li></ul> 
The provided homework template does a reasonable job of maximizing "throughput". However, it does this at the expense of fairness.
<p>
There are three test scenarios: <code>make highload</code>, <code>make mediumload</code>, and <code>make lowload</code>. Make sure your solution provides the desired performance on all three scenarios. The total number of trips should remain above 200, 450 and 1000 respectively.
</p><p>
<strong>HINT:</strong> for all of these, the complexity (as in run-time CPU consumption) of your solution is not of great importance: my solutions are quite inefficient, but still only use less than 15% of the CPU.
</p><p>
</p><h2><a name="Trip_Time_Fairness"></a> Trip Time Fairness </h2>
<p>
With the template solution, some trip requests take a long time to complete (from request to exiting at the requested floor), and others go quickly. The difference between min and max is often more than 20x. Provide a solution where the max trip duration is no more than 100% over the mean trip duration, over all passengers.
</p><p>
<strong>HINT:</strong> a FIFO solution would probably work well here.
</p><p>
<strong>Turn-in requirement:</strong> put your entire solution in a file called hw6i1.c
</p><p>
</p><h2><a name="Passenger_Service_fairness"></a> Passenger Service fairness </h2>
<p>
With the above solution, the more aggressive passengers (those with lower numbers), get more trips <strong>and</strong> quicker trips. Provide a solution where the more aggressive passengers may get more trips, but on average need to wait longer for their trips (unless there are so many elevators that nobody needs to wait long!).
</p><p>
<strong>HINT:</strong> a round-robin scheduler solution would work well here.
</p><p>
<strong>Turn-in requirement:</strong> put your entire solution in a file called hw6i2.c
</p><p>
</p><h2><a name="Static_passenger_prioritization"></a> Static passenger prioritization </h2>
<p>
The passengers that wait the longest between elevator trips happen to be the most important passengers, and should get priority service. Here, you may assume that a higher-numbered passenger (as provided in passenger_request) is a higher-priority passenger. Provide a solution where higher-priority passengers reliably receive better service (shorter mean and max trip times) than lower-priority passengers, but make sure that no passenger completes less than 1/3 of the number of trips of the highest-priority passenger.
</p><p>
<strong>HINT:</strong> here, a weighted round-robin solution may be a good idea.
</p><p>
<strong>Turn-in requirement:</strong> put your entire solution in a file called hw6i3.c
</p><p>
</p><h2><a name="Dynamic_passenger_prioritization"></a> Dynamic passenger prioritization </h2>
<p>
Here, do the same thing as in static passenger prioritization, but do not assume that the passenger number corresponds to their priority (we will use a modified main.c). Instead, have your solution base priority on inter-request time: passengers that issue frequent requests have lower priority than those that issue infrequent requests.
</p><p>
<strong>HINT</strong>: You'll need to determine priority based on the timing of requests, not the passenger ID. Use gettimeofday() to get the current time. A scheduler like CFS from linux would be a good choice here.
</p><p>
<strong>Turn-in requirement:</strong> put your entire solution in a file called hw6i4.c </p></div><!-- /patternTopic-->
<div class="twikiContentFooter"></div></div><!-- /patternContent-->
<a name="topic-actions"></a><div class="patternTopicActions"><div class="patternTopicAction"><span class="patternActionButtons"></span></div><!--/patternTopicAction--></div><!--/patternTopicActions-->
</div>