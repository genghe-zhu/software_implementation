TESTING for histo.c

### Test for stdin

[moose:histo] 419) ./histo 
16 bins of size 1 for range [0,16)
12 3311 41 2 1 41 2 6 8
16 bins of size 2 for range [0,32)
16 bins of size 4 for range [0,64)
16 bins of size 8 for range [0,128)
16 bins of size 16 for range [0,256)
16 bins of size 32 for range [0,512)
16 bins of size 64 for range [0,1024)
16 bins of size 128 for range [0,2048)
16 bins of size 256 for range [0,4096)
[    0:  255] 8
[  256:  511] 
[  512:  767] 
[  768: 1023] 
[ 1024: 1279] 
[ 1280: 1535] 
[ 1536: 1791] 
[ 1792: 2047] 
[ 2048: 2303] 
[ 2304: 2559] 
[ 2560: 2815] 
[ 2816: 3071] 
[ 3072: 3327] 1
[ 3328: 3583] 
[ 3584: 3839] 
[ 3840: 4095] 


### Testing for pipeline

[moose:histo] 421) echo {1..16} 150 | ./histo
16 bins of size 1 for range [0,16)
16 bins of size 2 for range [0,32)
16 bins of size 4 for range [0,64)
16 bins of size 8 for range [0,128)
16 bins of size 16 for range [0,256)
[   0:  15] 15
[  16:  31] 1
[  32:  47] 
[  48:  63] 
[  64:  79] 
[  80:  95] 
[  96: 111] 
[ 112: 127] 
[ 128: 143] 
[ 144: 159] 1
[ 160: 175] 
[ 176: 191] 
[ 192: 207] 
[ 208: 223] 
[ 224: 239] 
[ 240: 255] 
