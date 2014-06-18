#include "bstrlib.h"
#include "darray.h"
#include "dbg.h"
#include "hashmap.h"
#include "miniunit.h"
#include <assert.h>
#include <stdio.h>

int dfs(int a[], int n, int k, int i, int sum)
{
	/* reached end. time to pony up. */
	if (i == n) {
		return sum == k;
	}

	/* skip current */
	if (dfs(a, n, k, i + 1, sum)) {
		return 1;
	}

	/* use current */
	if (dfs(a, n, k, i + 1, sum + a[i])) {
		return 1;
	}

	/* no dice either way */
	return 0;
}

char *test_dfs() {
	int a[] = { 1, 2, 4, 7 };
	int n = 4;
	int k = 13;

	mu_assert(dfs(a, n, k, 0, 0) == 1, "Unable\n");

	k = 15;
	mu_assert(dfs(a, n, k, 0, 0) == 0, "Unable\n");

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_dfs);

	return NULL;
}

RUN_TESTS(all_tests);
