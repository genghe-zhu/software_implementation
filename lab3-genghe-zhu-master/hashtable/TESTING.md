### TESTING.md for hashtable.c

[moose:hashtable] 241) ./hashtabletest 
Count (should be zero): 0
testing hashtable_insert...
The hashtable:
{}{}{}{}{"key4":"item4",}{}{}{"key3":"item3","key2":"item2",}{}{}{}{}{"key1":"item1",}{}{}{"key5":"item5",}{}{}{}{}
Count (should be 5): 5
test insert duplicate key, hashtable should not change.
The hashtable:
{}{}{}{}{"key4":"item4",}{}{}{"key3":"item3","key2":"item2",}{}{}{}{}{"key1":"item1",}{}{}{"key5":"item5",}{}{}{}{}
Count (should be 5): 5
testing hashtable_find..., 
find key3 for key item3
find key6 for key (null)
testing hashtable_find..., one key per line
key100
find (null) for key key100
key2
find item2 for key key2
key3
find item3 for key key3
Count (should be 0): 5
test with null hashtable, good item...
test with null key...
test with null hashtable, null key...
The hashtable:
{}{}{}{}{"key4":"item4",}{}{}{"key3":"item3","key2":"item2",}{}{}{}{}{"key1":"item1",}{}{}{"key5":"item5",}{}{}{}{}
Count (should be 5): 5
delete the hashtable...

