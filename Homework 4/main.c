//
//  main.c
//  Searching
//
//  Created by Tomy Hsieh on 2020/5/26.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#define __USE_GNU 1
#include <dirent.h> // opendir(), readdir(), closedir()
#include <stdbool.h> // bool
#include <string.h> // strcmp(), strcpy(), strcat()
#include <unistd.h> // getcwd()

bool search_directory(const char* directory_path, const char* target);

int main(int argc, const char * argv[]) {
  
  // Read Input
  const char *path;
  const char *target;
  if (argc == 1) {
    printf("Please supply file name to search\n");
    exit(1);
  } else if (argc == 2) {
    if ((path=getcwd(NULL, 0)) == NULL) {
      printf("Can not get current working directory\n");
    }
    target = argv[1];
  } else if (argc == 3) {
    path = argv[1];
    target = argv[2];
  } else {
    printf("Too Many Arguments\n");
    exit(1);
  }
  
  bool found = false;
  found = search_directory(path, target);
  if (!found) {
    printf("cannot find the corresponding file.\n");
  }
  
}

bool search_directory(const char* directory_path, const char* target) {
  // Open Directory
  DIR* work_dir = opendir(directory_path);
  if (work_dir == NULL) {
    printf("Open Directory Error\t%s\n", directory_path);
    return false;
  }

  // Read Directory
  struct dirent* dir_entry = NULL;
  bool found = false;
  while ((dir_entry = readdir(work_dir)) != NULL) {
    if (dir_entry->d_type == DT_DIR) {
      
      // Pass for "." and ".."
      if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0) {
        continue;
      }
      
      // Build new path name
      char *new_path = malloc(strlen(directory_path) + strlen(dir_entry->d_name) + 2);
      strcpy(new_path, directory_path);
      if (strcmp(directory_path, "/") != 0) {
        strcat(new_path, "/");
      }
      strcat(new_path, dir_entry->d_name);
      
      // Search directory
      if (search_directory(new_path, target)) {
        found = true;
      }
      free(new_path);
      
    } else if (strcmp(dir_entry->d_name, target) == 0) {
      found = true;
      printf("found in  %s/%s\n", directory_path, dir_entry->d_name);
    }
  }

  // Close Directory
  if (closedir(work_dir) < 0) {
    printf("Close Directory Error\n");
  }
  
  return found;
}
