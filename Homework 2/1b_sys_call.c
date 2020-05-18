//
//  main.c
//  1 Byte System Call
//
//  Created by Tomy Hsieh on 2020/4/27.
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
  const int BATCH_SIZE = 1;  // in Byte
  const int BATCH_NUM = 4096000;
  struct timeval t_begin, t_end;
  int8_t *buffer = valloc(sizeof(char) * BATCH_SIZE);
  
  // Open File Descriptor
  int file_descriptor = open("testfile", O_WRONLY | O_CREAT, S_IWUSR);
  if (file_descriptor == -1) {
    printf("File Open Error\n");
    exit(1);
  }

  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<BATCH_NUM; i++) {
    write(file_descriptor, buffer, BATCH_SIZE);
  }
  gettimeofday(&t_end, NULL);

  // Clean Up
  close(file_descriptor);
  free(buffer);

  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("1 Byte System Call took %lld µs\n", t_exe);
  
  return 0;
  
}
