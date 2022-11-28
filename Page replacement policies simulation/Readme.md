# page replacement algorithm simulation
## overview and conditions ##
- Code can simulate hit ratio for a single page replacement algorithm. Input for this is framesize. page sequence is taken from a file
- Code can simulate hit ratio for all page replacement algorithms. Input for this is range of framesizes we need to check upon. page sequence is taken from the file .
- #pagenumber means the page is modified
- modified pages are used only in NRU 
- page sequence is given in input.txt
- images folder is required to store hit-ratio plot for every folder.

## NRU ##
- If a page is not in the memory and appears now. We consider it as referenced page and kept in class_2.
- Modified pages only comes if the page is in the memory.
- referenced bits are cleard for every four iterations.

## how to run ##
- compilation : g++ main2.cpp
- execution : ./a.out

## AGING ##
- Right shift counter of every frame after every three page references

## WS_Clock ##
- Threshold is taken as 80.


