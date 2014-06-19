#include "dbg.h"
#include "miniunit.h"
#include <assert.h>
#include <stdio.h>

int dfs(int a[], int n, int k, int i, int sum);
char *test_dfs(void);
char *all_tests(void);

RUN_TESTS(all_tests)

char *test_2d() {
	char **xy = calloc(10, sizeof(char*));
	mu_assert(xy != NULL, "Unable\n");

	xy[0] = calloc(3, sizeof(char));
	mu_assert(xy[0] != NULL, "Unable\n");

	xy[1] = calloc(5, sizeof(char));
	mu_assert(xy[1] != NULL, "Unable\n");

	xy[2] = calloc(5, sizeof(char));
	mu_assert(xy[2] != NULL, "Unable\n");

	xy[0][0] = 'a';
	xy[0][1] = 'b';

	xy[1][0] = 'a';
	xy[1][1] = 'b';
	xy[1][2] = 'c';
	xy[1][3] = 'd';

	strncpy(xy[2], "123", 3);

	log_info("xy[0]: %s", xy[0]);
	log_info("xy[1]: %s", xy[1]);
	log_info("xy[2]: %s", xy[2]);
	log_info("xy[1][0]: %c", xy[1][0]);
	log_info("xy[1][3]: %c", xy[1][3]);
	log_info("xy[2][2]: %c", xy[2][2]);

	free(xy[0]);
	free(xy[1]);
	free(xy[2]);

	free(xy);

	xy = NULL;

	mu_assert(xy == NULL, "Unable\n");

	return NULL;
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_2d);

	return NULL;
}
