Lab 2.5 - Depth-limiting Web Crawler
===================

To compile
---------------------------------------
```
go build crawl3.go 
```

To run
---------------------------------------
```
# Test 1
./crawl3 -depth=2 https://google.com/

# Test 2
./crawl3.go -depth=3 http://www.gopl.io/

# Test 3
./crawl3.go -depth=1  http://www.gopl.io/
```