TESTING for words.c

### Test for stdin

[moose:word] 430) ./word
asfd asfd asdf asdf cat a123 d31a
asfd
asfd
asdf
asdf
cat
a
da

### Test multiple files

[moose:word] 431) ./word test1.txt test2.txt
The
quick
fox
jumped
over
the
lazy
dog
This
is
a
two
line
file
test

### Test empty file

[moose:word] 432) ./word empty.txt

### Test - for stdin

[moose:word] 433) ./word empty.txt - test1.txt

asfasd asdf 123asda31 3 2a 
asfasd
asdf
asda
a
The
quick
fox
jumped
over
the
lazy
dog 
