### Results from running counterstest.c

[moose:counters] 117) ./counterstest 
Count (should be zero): 0
testing counters_add...
The counters:
{5=1,4=1,3=1,2=1,1=3,}
Count (should be 5): 5
Test counter_set, set 1:6, 3:6. 20:4
The counters:
{20=4,5=1,4=1,3=6,2=1,1=6,}
Count (should be 6): 6
testing counters_get..., 
find count for key 3: 6
find count for key that doesn't exist 35: 0
test counters_add with null counters...
0
test with negative key...
0
test with null counters, negativel key...
0
test counters_get with null counters...
0
test with negative key...
0
test with null counters, negativel key...
0
test counters_set with null counters...
0
test with negative key...
0
test with negative count...
0
The counters:
{20=4,5=1,4=1,3=6,2=1,1=6,}
Count (should be 6): 6
delete the counters...
