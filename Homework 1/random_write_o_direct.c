//
//  main.c
//  Random Write (using O_DIRECT)
//
//  Created by Tomy Hsieh on 2020/4/6.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
  const int BLOCK_SIZE = 4 * 1024;  // 4KB
  const int OP_COUNT = 25600;
  ssize_t rop_res = 0;
  struct timeval t_begin, t_end;
  int8_t *buffer = valloc(sizeof(char) * BLOCK_SIZE);
  int *offsets = malloc(sizeof(int) * OP_COUNT);
  
  // Generate Random Read Locations
  srand((unsigned int)time(NULL));
  for (int i=0; i<OP_COUNT; i++) {
    int num = rand();
    offsets[i] = num - (num % BLOCK_SIZE); // align to BLOCK_SIZE
  }
  
  // Open File Descriptor
  int tmp_fd = open("testfile", O_WRONLY | O_DIRECT, S_IRWXU);
  check_io_error(tmp_fd, "File Open");
  
  // Open File Descriptor (macOS)
  // int tmp_fd = open("testfile", O_WRONLY, S_IRWXU);
  // check_io_error(tmp_fd, "File Open");
  // int ocop_res = fcntl(FILE_DESCRIPTOR, F_NOCACHE, 1);
  // check_io_error(ocop_res, "Turn Off Cache");
  
  // Write File Randomly with O_DIRECT
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<OP_COUNT; i++) {
    lseek(FILE_DESCRIPTOR, offsets[i], SEEK_SET);
    rop_res = write(FILE_DESCRIPTOR, buffer, BLOCK_SIZE);
  }
  gettimeofday(&t_end, NULL);
  check_io_error((int)rop_res, "File Write");
  
  // Clean Up
  close(FILE_DESCRIPTOR);
  free(buffer);
  free(offsets);
  
  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("Random Write (O_DIRECT) took %lld µs\n", t_exe);
  
  return 0;
  
}
