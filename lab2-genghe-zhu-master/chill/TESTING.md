### Testing no argument input
[moose:chill] 241) ./chill
 Temp    Wind    Chill
-----    ----    -----
-10.0     5.0    -16.2
-10.0    10.0    -21.5
-10.0    15.0    -25.0

 0.0     5.0    -10.0
 0.0    10.0    -15.3
 0.0    15.0    -18.7

10.0     5.0     -3.7
10.0    10.0     -9.1
10.0    15.0    -12.5

20.0     5.0      2.5
20.0    10.0     -2.9
20.0    15.0     -6.3

30.0     5.0      8.7
30.0    10.0      3.3
30.0    15.0     -0.1

40.0     5.0     14.9
40.0    10.0      9.5
40.0    15.0      6.1

### Testing 1 argument input
[moose:chill] 242) ./chill 10
 Temp    Wind    Chill
-----    ----    -----
10.0     5.0     -3.7
10.0    10.0     -9.1
10.0    15.0    -12.5

### Testing 2 argument input
[moose:chill] 243) ./chill 10 5
 Temp    Wind    Chill
-----    ----    -----
10.0     5.0     -3.7

### Testing temp range out of bounds input
[moose:chill] 244) ./chill 1000
Temperature must be less than 50 degrees fahrenheit

### Testing temp range out of bounds input
[moose:chill] 245) ./chill -1000
Temperature must be greater than -99 degrees fahrenheit

### Testing wind velocity out of bounds input
[moose:chill] 247) ./chill 10 0
Wind velocity must be greater than or equal to 0.5 MPH

### Testing float argument input
[moose:chill] 248) ./chill 10.5 10.5
 Temp    Wind    Chill
-----    ----    -----
10.5    10.5     -9.2

