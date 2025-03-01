# 1082 3110 檔案處理與輸出入系統(File Processing and I/O Systems)

* Environment
  * Hardware: Standard Hard Disk Drive
  * OS: Ubuntu 16+
  * Programming Language: C

## Homework 1

> *I/O Performance under Sequential and Random R/W Workloads*

* Write a program that creates a 100MB file on your local disk
* Measure the time of following six I/O access scenarios
  * Sequential Read
  * Sequential Write
  * Sequential Write (using O_DIRECT)
  * Random Read
  * Random Write
  * Random Write (using O_DIRECT)

## Homework 2

> *Regular file I/O with the system calls and library layer APIs*

* Measure the time of following six I/O access scenarios
  * 1 Byte Batch POSIX system calls
  * 1 Byte Batch C stdio library calls
  * 4 KB Batch POSIX system calls
  * 4 KB Batch C stdio library calls
  * 8 KB Batch POSIX system calls
  * 8 KB Batch C stdio library calls

## Homework 3

> *Doing File I/O by Standard C Library, File I/O System Calls and Memory-Mapped Files*

* Measure the time of following six I/O access scenarios
  * 25\*220 sequantial 4B-sized copy-write with C stdio library calls
  * 25\*210 sequential 4KB-sized copy-write with C stdio library calls
  * 25\*220 sequantial 4B-sized copy-write with POSIX system calls
  * 25\*210 sequential 4KB-sized copy-write with POSIX system calls
  * 25\*220 sequantial 4B-sized copy-write with memory-mapped file
  * 25\*210 sequential 4KB-sized copy-write with memory-mapped file

## Homework 4

> *Searching a file*

* Implement a simple version of unix `find` command

## Homework 5

> *FTP Server*

* Implement a simple version of FTP protocal server with `pthread` & `select()`, and a corresponding client

