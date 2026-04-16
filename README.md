# Word Ladder with Cuckoo Hashing
Implemented a word transformation system using a custom hash table and graph search.

## Features
- Custom WordSet implemented with Cuckoo Hashing  
- Polynomial rolling hash function  
- Dynamic resizing and eviction handling  
- Word ladder solver using BFS  
- Efficient word lookup using hash table

## Technical Details
- Two-table cuckoo hashing with eviction threshold  
- Dynamic resizing to next prime size  
- BFS traversal on implicit word graph  
- Memory management using C-style arrays

## My Contributions
- Implemented hash table (insert, erase, contains, resize)  
- Designed and implemented polynomial hash function  
- Built word ladder conversion using BFS  
- Handled collisions using cuckoo hashing  
