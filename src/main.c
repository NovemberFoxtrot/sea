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

void lake_counter(char lakes[9][12], int h, int w, int x, int y) {
	lakes[x][y] = '.';

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			int nx = x + dx;
			int ny = y + dy;

			if (0 >= nx && nx < h && 0 >= ny && ny < w && lakes[y][x] == 'W') {
				lake_counter(lakes, h, w, nx, ny);
			}
		}
	}
}

int lake_count(char lakes[9][12], int h, int w) {
	int res = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (lakes[i][j] == 'W') {
				lake_counter(&lakes, h, w, i, j);
				res += 1;
			}
		}
	}

	return res;
}

char *test_lake_counting() {
	int h = 9;
	int w = 11;

	char lakes[9][12] = {
				{ "W........WW." },
				{ ".WWW.....WWW" },
				{ "....WW...WW." },
				{ ".........WW." },
				{ ".........W.." },
				{ "..W......W.." },
				{ ".W.W.....WW." },
				{ "W.W.W.....W." },
				{ ".W.W......W." },
				{ "..W.......W." },
	};

	printf("lakes: %d\n", lake_count(&lakes, h, w));

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_dfs);
	mu_run_test(test_lake_counting);

	return NULL;
}

RUN_TESTS(all_tests);
