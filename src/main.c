#include <stdio.h>
#include "miniunit.h"
#include "dbg.h"
#include "darray.h"
#include "bstrlib.h"
#include "hashmap.h"
#include <assert.h>

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

char *test_dfs()
{
	int a[] = { 1, 2, 4, 7 };
	int n = 4;
	int k = 13;

	mu_assert(dfs(a, n, k, 0, 0) == 1, "Unable\n");

	k = 15;
	mu_assert(dfs(a, n, k, 0, 0) == 0, "Unable\n");

	return NULL;
}

char *strrpl(const char *input, int length, int pos, char ch) {
	char *tmp = calloc((length + 1), sizeof(char*));

	if (tmp == NULL) {
		perror("malloc error");
		exit(1);
	}

	for(int i = 0; i < length; i++) {
		if (i != pos) {
			tmp[i] = input[i];
		} else {
			tmp[i] = ch;
		}
	}

	return tmp;
}

void lake_counter(char **lakes, int h, int w, int x, int y)
{
	lakes[y] = strrpl(lakes[y], w, x, '.');

	printf("%s\n", lakes[y]);

	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			int nx = x + dx;
			int ny = y + dy;

			if (0 <= nx && nx < h && 0 <= ny && ny < w && lakes[x][y] == 'W') {
				// lake_counter(lakes, h, w, nx, ny);
			}
		}
	}
}

int lake_count(char **lakes, int h, int w)
{
	int res = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (lakes[i][j] == 'W') {
				lake_counter(lakes, h, w, i, j);
				res++;
			}
		}
	}

	return res;
}

char *test_strrpl_single() {
	char *result = strrpl("A", 1, 0, 'R');

	mu_assert(result[0] == 'R', "RRRR\n");

	return NULL;
}

char *test_strrpl_double() {
	char *result = strrpl("AB", 2, 0, 'R');

	printf("Unable %s\n", result);
	mu_assert(result[0] == 'R', "!= R\n");
	mu_assert(result[1] == 'B', "!= B\n");

	return NULL;
}

char *test_strrpl_long() {
	char *result = strrpl("W........WW.", 12, 0, '.');

	mu_assert(result[0] == '.', "!= R\n");
	mu_assert(result[1] == '.', "!= B\n");

	result = strrpl(result, 12, 11, '.');
	mu_assert(result[11] == '.', "!= R\n");

	return NULL;
}

char *test_lake_counting() {

	int h = 9; /* height */
	int w = 12; /* width */

	char **lakes = calloc(h+1, sizeof(char*));

	if (lakes == NULL) {
		perror("malloc error");
		exit(1);
	}

	lakes[0] = "W........WW.";
	lakes[1] = ".WWW.....WWW";
	lakes[2] = "....WW...WW.";
	lakes[3] = ".........WW.";
	lakes[4] = ".........W..";
	lakes[5] = "..W......W..";
	lakes[6] = ".W.W.....WW.";
	lakes[7] = "W.W.W.....W.";
	lakes[8] = ".W.W......W.";
	lakes[9] = "..W.......W.";

	printf("lakes: %d\n", lake_count(lakes, h, w));

	free(lakes);
	
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_dfs);
	mu_run_test(test_strrpl_single);
	mu_run_test(test_strrpl_double);
	mu_run_test(test_strrpl_long);
	mu_run_test(test_lake_counting);

	return NULL;
}

RUN_TESTS(all_tests);
