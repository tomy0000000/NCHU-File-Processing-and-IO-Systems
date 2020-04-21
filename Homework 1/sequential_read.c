//
//  main.c
//  Sequential Read
//
//  Created by Tomy Hsieh on 2020/4/6.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#define __USE_GNU 1
#include <fcntl.h>  // open()
#include <unistd.h>  // read(), write()
#include <sys/time.h>  // gettimeofday()

static int FILE_DESCRIPTOR = -1;

// Close FILE_DESCRIPTOR then Exit if I/O Operation Failed, 
void check_io_error(int status, char* operation) {
  if (status == -1) {
    printf("%s Error\n", operation);
    if (FILE_DESCRIPTOR != -1) {
      close(FILE_DESCRIPTOR);
    }
    exit(1);
  }
  if (FILE_DESCRIPTOR == -1) {
    FILE_DESCRIPTOR = status;
  }
}

int main(int argc, const char * argv[]) {
  
  // Initialization
  const int FILE_SIZE = 100 * 1024 * 1024;  // 100 MB
  int8_t *buffer = valloc(sizeof(char) * FILE_SIZE);
  struct timeval t_begin, t_end;
  
  // Open File Descriptor
  int tmp_fd = open("testfile", O_RDONLY, S_IRWXU);
  check_io_error(tmp_fd, "File Open");
  
  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  ssize_t rop_res = read(FILE_DESCRIPTOR, buffer, FILE_SIZE);
  gettimeofday(&t_end, NULL);
  check_io_error((int)rop_res, "File Read");
  
  // Clean Up
  close(FILE_DESCRIPTOR);
  free(buffer);
  
  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("Sequantial Read took %lld µs\n", t_exe);
  
  return 0;
  
}
