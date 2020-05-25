//
//  main.c
//  4 Byte System Call
//
//  Created by Tomy Hsieh on 2020/5/20.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU 1
#include <fcntl.h>  // open()
#include <unistd.h>  // write(), close()
#include <sys/time.h>  // gettimeofday()

int main(int argc, const char * argv[]) {
  
  // Initialization
  const int BATCH_SIZE = 4;  // in Byte
  const int BATCH_NUM = 25*220;
  struct timeval t_begin, t_end;
  int8_t *buffer = valloc(sizeof(char) * BATCH_SIZE);
  
  // Open File Descriptor
  int src_descriptor = open("testfile-src", O_RDONLY, S_IWUSR);
  if (src_descriptor == -1) {
    printf("File Open Error\n");
    exit(1);
  }
  int dst_descriptor = open("testfile-dst", O_WRONLY | O_CREAT, S_IWUSR);
  if (dst_descriptor == -1) {
    printf("File Open Error\n");
    exit(1);
  }

  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<BATCH_NUM; i++) {
    read(src_descriptor, buffer, BATCH_SIZE);
    write(dst_descriptor, buffer, BATCH_SIZE);
  }
  gettimeofday(&t_end, NULL);

  // Clean Up
  close(src_descriptor);
  close(dst_descriptor);
  free(buffer);

  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("4 Byte System Copy-Write took %lld µs\n", t_exe);
  
  return 0;
  
}
