// Copyright 2020 Andrew Hu
/* Single header file unit testing framework
 * #include "safe_assert.h" at the top of your file
 * and _don't_ use a main() function. Instead add
 *
 * suite("Suite Name") { ... }
 *
 * Inside of the suite, add various tests inside of
 *
 * test("It should blah blah blah" { ... }
 *
 * Use safe_assert() just like assert() from assert.h
 * */
#ifndef _SAFE_ASSERT_H_
#define _SAFE_ASSERT_H_

#ifndef NOCOLOR
#define __SA_COLOR_RESET__       "\x1B[0m"
#define __SA_COLOR_RED__         "\x1B[31m"    /* Red */
#define __SA_COLOR_GREEN__       "\x1B[32m"    /* Green */
#else
#define __SA_COLOR_RESET__       "" /* Make colors a No-op */
#define __SA_COLOR_RED__         ""
#define __SA_COLOR_GREEN__       ""
#endif

#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
pid_t sa_fork_res;
int sa_child_status;

int sa_num_passes = 0, sa_num_failures = 0;

#define SA_SEGFAULT 11

#define safe_assert(cond) sa_fork_res = fork();\
if (sa_fork_res == 0) /*Only run cond in child*/ {\
  if (!(cond))\
    exit(EXIT_FAILURE);\
  else\
    exit(EXIT_SUCCESS);\
} else {\
  wait(&sa_child_status);\
  if (sa_child_status != EXIT_SUCCESS) /*Allow status SIGSEGV for segfault*/ {\
    printf("    "__SA_COLOR_RED__"%s"__SA_COLOR_RESET__\
            " (%s:%d): ", (WIFSIGNALED(sa_child_status) && WTERMSIG(sa_child_status) == SA_SEGFAULT) ? "Segfault" : "Assert failed",\
             __FILE__, __LINE__);\
    printf("`%s'\n", #cond);\
    fflush(stdout);\
    finish_it(true);\
  } else {\
    int useless = 0;/*Execute cond*/\
    if(cond) { useless++; } else { useless--; }\
  }\
}

extern char* suite_name;
#define suite(name) char* suite_name = name;\
void suite_main() /* suite definition follows this macro */

void suite_main();
int main(int argc, char** argv) {
  printf("Suite: %s\n", suite_name);
  fflush(stdout);
  suite_main();

  printf("Final results:\n");
  if (sa_num_failures == 0) {
    printf("  " __SA_COLOR_GREEN__ "ALL PASS (%d/%d)" __SA_COLOR_RESET__ "\n", sa_num_passes, sa_num_passes);
  } else {
    printf("  " __SA_COLOR_GREEN__ "%d passed" __SA_COLOR_RESET__ "\n", sa_num_passes);
    printf("  " __SA_COLOR_RED__ "%d failed" __SA_COLOR_RESET__ "\n", sa_num_failures);
  }
  fflush(stdout);
  return sa_num_failures;
}

int start_it(char* message) {
  printf("  %s\n", message);
  fflush(stdout);
  int res = fork();
  if (res == 0) {  // Child
    return true;
  } else {  // Parent
    int status;
    wait(&status);
    int failed = status != EXIT_SUCCESS;
    printf("    (%s)%s\n", failed ? __SA_COLOR_RED__ "FAILED" __SA_COLOR_RESET__
      : __SA_COLOR_GREEN__ "OK" __SA_COLOR_RESET__,
    status == SA_SEGFAULT ? 
      " : "__SA_COLOR_RED__"Segfault outside of safe_assert"__SA_COLOR_RESET__ : "");
    fflush(stdout);
    if (status) {
      sa_num_failures++;
    } else {
      sa_num_passes++;
    }
    return false;
  }
}

int finish_it(bool failed) {
  fflush(stdout);
  if (failed)
    exit(EXIT_FAILURE);
  else
    exit(EXIT_SUCCESS);
}

#define test(description) \
for (bool has_run = false;\
    has_run < 1 ? (start_it(description)) : finish_it(false);\
    has_run = true)

#endif
