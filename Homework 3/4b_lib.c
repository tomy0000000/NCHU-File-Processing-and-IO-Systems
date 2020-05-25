//
//  main.c
//  4 Byte Library Call
//
//  Created by Tomy Hsieh on 2020/5/20.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>  // fopen(), fwrite(), fclose()
#include <stdlib.h>
#define __USE_GNU 1
#include <sys/time.h>  // gettimeofday()

int main(int argc, const char * argv[]) {
  
  // Initialization
  const int BATCH_SIZE = 4;  // in Byte
  const int BATCH_NUM = 25*220;
  struct timeval t_begin, t_end;
  int8_t *buffer = valloc(sizeof(char) * BATCH_SIZE);
  
  // Open File Descriptor
  FILE* src_descriptor = fopen("testfile-src", "r");
  if (src_descriptor == NULL) {
    printf("File Open Error\n");
    exit(1);
  }
  FILE* dst_descriptor = fopen("testfile-dst", "w+");
  if (dst_descriptor == NULL) {
    printf("File Open Error\n");
    exit(1);
  }
  
  // Read File Sequantially
  gettimeofday(&t_begin, NULL);
  for (int i=0; i<BATCH_NUM; i++) {
    fread(buffer, sizeof(char), BATCH_SIZE, src_descriptor);
    fwrite(buffer, sizeof(char), BATCH_SIZE, dst_descriptor);
  }
  gettimeofday(&t_end, NULL);

  // Clean Up
  fclose(src_descriptor);
  fclose(dst_descriptor);
  free(buffer);

  // Print Result
  int64_t t_exe = 1000000 * (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_usec - t_begin.tv_usec);
  printf("4 Byte Library Copy-Write took %lld µs\n", t_exe);
  
  return 0;
  
}
