#include "dbg.h"
#include "miniunit.h"
#include <assert.h>
#include <stdio.h>

int dfs(int a[], int n, int k, int i, int sum);
char *test_dfs(void);
char *all_tests(void);

RUN_TESTS(all_tests)

char *test_dfs() {
	mu_assert(1 == 1, "Unable\n");

	return NULL;
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_dfs);

	return NULL;
}
