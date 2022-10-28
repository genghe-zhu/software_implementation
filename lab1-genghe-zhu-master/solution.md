## A:

`grep 'New Hampshire' covid.csv | grep 2020-05-`

## B:

`cut -d , -f 2,5,6 covid.csv`

## C: 

`sed -n '/2020-02-14.*/,/2020-03-15.*/p' covid.csv`

## D: 

`grep "New Hampshire" covid.csv |  cut -d , -f 1,2,3,6 | sort -t ',' -k2,2 -k1,1r |  sort -um -t ',' -k 2.1,2.0 | grep ",0$" | cut -d ',' -f 2,3`

## E: 

`cut -d , -f 1,2,3,6 covid.csv | sort -t ',' -k2,2  -k3,3 -k1,1r | sed 's/,/=/2' |  sort -um -t ',' -k 2.1,2.0 | grep ",0$" |  sed 's/=/,/' | cut -d , -f 3 | sort | uniq -c | sort -nr`

## F: 

`cut -d , -f 1,2,3,5 covid.csv | sort -t ',' -k2,2  -k3,3 -k1,1r | sed 's/,/=/2' |  sort -um -t ',' -k 2.1,2.0 | sort -t ',' -k3,3rn | head -n 10 | sed 's/=/,/' | cut -d ',' -f 2,3,4`

## G: 
`cut -d , -f 1,2,3,5 covid.csv | sort -t ',' -k2,2  -k3,3 -k1,1r | sed 's/,/-/2' |  sort -um -t ',' -k 2.1,2.0 | sort -t ',' -k3,3rn | head -n 10 | sed 's/-/,/3' | cut -d ',' -f 2,3,4 | sed 's/,/|/g' | sed 's/^/|/' | sed 's/$/|/'`

|County|State|Cases|
|-------------|-------------|-----|
|New York City|New York|220143|
|Los Angeles|California|105507|
|Cook|Illinois|90911|
|Maricopa|Arizona|52266|
|Nassau|New York|41853|
|Suffolk|New York|41427|
|Miami|Dade-Florida|37960|
|Westchester|New York|34865|
|Harris|Texas|32859|
|Philadelphia|Pennsylvania|26257|
