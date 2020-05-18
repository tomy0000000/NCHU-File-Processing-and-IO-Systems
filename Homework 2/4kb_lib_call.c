//
//  main.c
//  4K Byte Library Call
//
//  Created by Tomy Hsieh on 2020/4/27.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>  // fopen(), fwrite(), fclose()
#include <stdlib.h>
#define __USE_GNU 1
#include <sys/time.h>  // gettimeofday()

int main(int argc, const char * argv[]) {
  
  // Initialization
  const int BATCH_SIZE = 4096;  // in Byte
  const int BATCH_NUM = 1000;
  struct timeval t_begin, t_end;
  int8_t *buffer = valloc(sizeof(char) * BATCH_SIZE);
  
  // Open File Descriptor
  FILE* file_descriptor = fopen("testfile", "wt+");
  if (file_descriptor == NULL) {
    printf("File Open Error\n");
    exit(1);
  }
  
  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<BATCH_NUM; i++) {
    fwrite(buffer, sizeof(char), BATCH_SIZE, file_descriptor);
  }
  gettimeofday(&t_end, NULL);

  // Clean Up
  fclose(file_descriptor);
  free(buffer);

  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("4K Byte Library Call took %lld µs\n", t_exe);
  
  return 0;
  
}
