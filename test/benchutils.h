#include <stdio.h>
#include <time.h>

#define bench_ns_t unsigned long long

static inline bench_ns_t clock_ns()
{
	struct timespec tm;
	clock_gettime(CLOCK_MONOTONIC, &tm);
	return 1000000000uLL * tm.tv_sec + tm.tv_nsec;
}

#define BENCH_START() clock_ns()

#define BENCH_END() clock_ns()

#define BENCH_DURATION(start) clock_ns() - start

static void bench_print(const char *name, size_t duration, size_t n) {
	printf("%30s %.2f ns\n", name, (double) duration / n);
}