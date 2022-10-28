TESTING for regress.sh

### example output following directions

[moose:regress] 325) ls
covid.csv  query.sh  regress.sh  test0  test1  test2  test3

[moose:regress] 326) cat test?
cat query.sh
./query.sh
./query.sh Massachusetts

./query.sh "New Hampshire" "2020-06-26"


[moose:regress] 327) ./regress.sh base test?

saved test results in 20200713.212143 ...

[moose:regress] 328) ./regress.sh base test?

saved test results in 20200713.212154 ...
comparing 20200713.212154 base
no differences

[moose:regress] 328) echo ./query.sh Texas 2020-06-25 > test4

[moose:regress] 329) ls
20200713.212154  base  covid.csv  query.sh  regress.sh  test0  test1  test2  test3  test4

[moose:regress] 330) ./regress.sh base test?

saved test results in 20200713.212233 ...
comparing 20200713.212233 base
Only in 20200713.212233: test4.status
Only in 20200713.212233: test4.stdout
Only in 20200713.212233: test4.test

[moose:regress] 331) echo ./query.sh Florida > test2

[moose:regress] 332) cat test?
cat query.sh
./query.sh
./query.sh Florida
./query.sh "New Hampshire" "2020-06-26"

./query.sh Texas 2020-06-25

[moose:regress] 333) ./regress.sh base test?

saved test results in 20200713.212259 ...
comparing 20200713.212259 base
Files 20200713.212259/test2.stdout and base/test2.stdout differ
Files 20200713.212259/test2.test and base/test2.test differ
Only in 20200713.212259: test4.status
Only in 20200713.212259: test4.stdout
Only in 20200713.212259: test4.test

[moose:regress] 334) ls
20200713.212154  20200713.212233  20200713.212259  base  covid.csv  query.sh  regress.sh  test0  test1  test2  test3  test4

[moose:regress] 335) ###### now some error cases

[moose:regress] 336) ./regress.sh
incorrect number of arguments. Usage: ./regress.sh dirname testfilename...

[moose:regress] 337) ./regress.sh base
incorrect number of arguments. Usage: ./regress.sh dirname testfilename...

[moose:regress] 338) ./regress.sh test?
directory test0 is not a directory

[moose:regress] 400) ./regress.sh base base

test case 'base' is not a file (or not readable)

[moose:regress] 401) chmod -r test?

[moose:regress] 402) ./regress.sh base test?

test case 'test0' is not a file (or not readable)
