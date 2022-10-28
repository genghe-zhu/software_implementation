### Results from running settest.c

[moose:set] 110) ./settest
Count (should be zero): 0
testing set_insert...
The set:
{"key5":"item5","key4":"item4","key3":"item3","key2":"item2","key1":"item1",}
Count (should be 5): 5
test insert duplicate key, set should not change.
The set:
{"key5":"item5","key4":"item4","key3":"item3","key2":"item2","key1":"item1",}
Count (should be 5): 5
testing set_find..., 
find key3 for key item3
find key6 for key (null)
testing set_find..., one key per line
key1
find item1 for key key1
key2
find item2 for key key2
k100 
find (null) for key k100
Count (should be 0): 5
test with null set, good item...
test with null key...
test with null set, null key...
The set:
{"key5":"item5","key4":"item4","key3":"item3","key2":"item2","key1":"item1",}
Count (should be 5): 5
delete the set...
