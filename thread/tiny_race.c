/**
 * thread sample
 * 2020-07-01 K.OHWADA
 */

// run two threads 
// detects data races with ThreadSanitizer

// gcc -fsanitize=thread -g -O1 tiny_race.c

// reference : https://clang.llvm.org/docs/ThreadSanitizer.html


#include <pthread.h>

// global
int g_int;


/**
 * ThreadA
 */
void* threadA(void* x) 
{
    g_int = 43;
    return x;
}


/**
 * ThreadB
 */
void* threadB(void* y) 
{
    g_int = 42; // data race
    return y;
}


/**
 * main
 */
int main(void) 
{
  pthread_t t1, t2;

  pthread_create(&t1, NULL, threadA, NULL);
  pthread_create(&t2, NULL, threadB, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}


// ==================
// WARNING: ThreadSanitizer: data race (pid=42176)
//  Write of size 4 at 0x00010edd6040 by thread T2:
//    #0 threadB tiny_race.c:20 (a.out:x86_64+0x100000e51)
//  Previous write of size 4 at 0x00010edd6040 by thread T1:
//    #0 threadA tiny_race.c:14 (a.out:x86_64+0x100000e11)
//  Location is global 'g_int' at 0x00010edd6040 (a.out+0x000100002040)
//  Thread T2 (tid=1678482, running) created by main thread at:
//    #0 pthread_create <null>:1600912 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2aacd)
//     #1 main tiny_race.c:30 (a.out:x86_64+0x100000eb1)

//   Thread T1 (tid=1678481, finished) created by main thread at:
//    #0 pthread_create <null>:1600912 (libclang_rt.tsan_osx_dynamic.dylib:x86_64h+0x2aacd)
//    #1 main tiny_race.c:29 (a.out:x86_64+0x100000e9a)
// SUMMARY: ThreadSanitizer: data race tiny_race.c:20 in threadB
// ==================
// ThreadSanitizer: reported 1 warnings

