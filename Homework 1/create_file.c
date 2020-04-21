//
//  main.c
//  Create File
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
  
  // Open File Descriptor
  int tmp_fd = open("testfile", O_WRONLY | O_CREAT, S_IRWXU);
  check_io_error(tmp_fd, "File Open");
  
  // Write to File
  ssize_t wop_res = write(FILE_DESCRIPTOR, buffer, FILE_SIZE);
  check_io_error((int)wop_res, "File Write");
  
  // Clean Up
  close(FILE_DESCRIPTOR);
  free(buffer);
  
  return 0;
  
}
