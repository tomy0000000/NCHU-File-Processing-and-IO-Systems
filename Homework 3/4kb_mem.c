//
//  main.c
//  4K Byte Memory-mapped file
//
//  Created by Tomy Hsieh on 2020/5/20.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU 1
#include <fcntl.h>  // open()
#include <unistd.h>  // write(), close(), ftruncate()
#include <sys/time.h>  // gettimeofday()
#include <sys/mman.h>  // mmap(), munmap()

int main(int argc, const char * argv[]) {
  
  // Initialization
  const int BATCH_SIZE = 4096;  // in Byte
  const int BATCH_NUM = 25*210;
  struct timeval t_begin, t_end;
  char *buffer = valloc(sizeof(char) * BATCH_SIZE * BATCH_NUM);
  
  // Open File Descriptor
  int src_descriptor = open("testfile-src", O_RDONLY, S_IWUSR);
  if (src_descriptor == -1) {
    printf("File Open Error\n");
    exit(1);
  }
  char *src_map = mmap(NULL, BATCH_SIZE * BATCH_NUM, PROT_READ, MAP_SHARED, src_descriptor, 0);
  if (src_map == MAP_FAILED) {
    printf("Memory-mapped File Error\n");
    exit(1);
  }
  int dst_descriptor = open("testfile-dst", O_RDWR | O_CREAT, S_IWUSR);
  if (dst_descriptor == -1) {
    printf("File Open Error\n");
    exit(1);
  }
  if (ftruncate(dst_descriptor, BATCH_SIZE * BATCH_NUM)) {  // Truncte File Size
    printf("File Truncate Error\n");
    exit(1);
  }
  char *dst_map = mmap(NULL, BATCH_SIZE * BATCH_NUM, PROT_READ | PROT_WRITE, MAP_SHARED, dst_descriptor, 0);
  if (dst_map == MAP_FAILED) {
    printf("Memory-mapped File Error\n");
    exit(1);
  }
  
  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<BATCH_NUM; i++) {
    buffer[i] = src_map[i];
    dst_map[i] = buffer[i];
  }
  gettimeofday(&t_end, NULL);

  // Clean Up
  munmap(src_map, BATCH_SIZE*BATCH_NUM);
  munmap(dst_map, BATCH_SIZE*BATCH_NUM);
  close(src_descriptor);
  close(dst_descriptor);
  free(buffer);

  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("4K Byte Memory-mapped file Copy-Write took %lld µs\n", t_exe);
  
  return 0;
  
}
