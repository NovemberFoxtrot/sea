#include "dbg.h"
#include "miniunit.h"
#include "dlist.h"
#include <assert.h>
#include <stdio.h>

int dfs(int a[], int n, int k, int i, int sum);
char *test_dfs(void);
char *all_tests(void);

RUN_TESTS(all_tests)

void wipe(char **xy, int i, int j) {
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (i + x < 0 || i + x > 9) continue;
			if (j + y < 0 || j + y > 9) continue;
			if (xy[i + x][j + y] != 'w') continue;

			xy[i + x][j + y] = '.';

			wipe(xy, i + x, j + y);
		}
	}
}

int count_lakes(char **xy) {
	int result = 0;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (xy[i][j] != '.') {
				result++;
				wipe(xy, i, j);
			}
		}
	}

	return result;
}

char *test_2d() {
	char **xy = calloc(10, sizeof(char*));
	check_mem(xy);

	for(int i = 0; i < 10; i++) {
		xy[i] = calloc(11, sizeof(char));
		check_mem(xy[i]);
	}

	strncpy(xy[0], "w......ww.", 10);
	strncpy(xy[1], "...w...ww.", 10);
	strncpy(xy[2], "....ww.w..", 10);
	strncpy(xy[3], "....w..w..", 10);
	strncpy(xy[4], ".......ww.", 10);
	strncpy(xy[5], "..w.....w.", 10);
	strncpy(xy[6], ".w.w...ww.", 10);
	strncpy(xy[7], "w.w.w..ww.", 10);
	strncpy(xy[8], ".w.w....w.", 10);
	strncpy(xy[9], "..w.......", 10);

	log_info("# lakes: %d", count_lakes(xy));

	for(int i = 0; i < 10; i++) {
		free(xy[i]);
		xy[i] = NULL;
	}

	free(xy);

	xy = NULL;

	mu_assert(xy == NULL, "Unable\n");

	return NULL;

error:
	for(int i = 0; i < 10; i++) {
		free(xy[i]);
		xy[i] = NULL;
	}

	free(xy);

	return NULL;
}

int bfs(char **xy) {
	DList *queue;
	queue = DList_create();
	
	DList_clear_destroy(queue);
}

char *test_maze() {
	char **xy = calloc(10, sizeof(char*));
	check_mem(xy);

	for(int i = 0; i < 10; i++) {
		xy[i] = calloc(11, sizeof(char));
		check_mem(xy[i]);
	}

	strncpy(xy[0], "#S#.######", 10);
	strncpy(xy[1], "#.#.#....#", 10);
	strncpy(xy[2], "#.#...####", 10);
	strncpy(xy[3], "#.#.#.#...", 10);
	strncpy(xy[4], "#...#.#.#.", 10);
	strncpy(xy[5], "#####.#.#.", 10);
	strncpy(xy[6], "......#.#.", 10);
	strncpy(xy[7], ".######.#.", 10);
	strncpy(xy[8], ".#......#.", 10);
	strncpy(xy[9], "...#####G.", 10);

	log_info("# lakes: %d", count_lakes(xy));

	for(int i = 0; i < 10; i++) {
		free(xy[i]);
		xy[i] = NULL;
	}

	free(xy);

	xy = NULL;

	mu_assert(xy == NULL, "Unable\n");

	return NULL;

error:
	for(int i = 0; i < 10; i++) {
		free(xy[i]);
		xy[i] = NULL;
	}

	free(xy);

	return NULL;
}

static DList *dlist = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
	dlist = DList_create();
	mu_assert(dlist != NULL, "Failed to create list.");

	return NULL;
}

char *test_destroy()
{
	DList_clear_destroy(dlist);

	return NULL;
}

char *test_push_pop()
{
	DList_push(dlist, test1);
	mu_assert(DList_last(dlist) == test1, "Wrong last value.");

	DList_push(dlist, test2);
	mu_assert(DList_last(dlist) == test2, "Wrong last value");

	DList_push(dlist, test3);
	mu_assert(DList_last(dlist) == test3, "Wrong last value.");
	mu_assert(DList_count(dlist) == 3, "Wrong count on push.");

	char *val = DList_pop(dlist);
	mu_assert(val == test3, "Wrong value on pop.");

	val = DList_pop(dlist);
	mu_assert(val == test2, "Wrong value on pop.");

	val = DList_pop(dlist);
	mu_assert(val == test1, "Wrong value on pop.");
	mu_assert(DList_count(dlist) == 0, "Wrong count after pop.");

	return NULL;
}

char *test_unshift()
{
	DList_unshift(dlist, test1);
	mu_assert(DList_first(dlist) == test1, "Wrong first value.");

	DList_unshift(dlist, test2);
	mu_assert(DList_first(dlist) == test2, "Wrong first value");

	DList_unshift(dlist, test3);
	mu_assert(DList_first(dlist) == test3, "Wrong last value.");
	mu_assert(DList_count(dlist) == 3, "Wrong count on unshift.");

	return NULL;
}

char *test_remove()
{
	char *val = DList_remove(dlist, dlist->first->next);
	mu_assert(val == test2, "Wrong removed element.");
	mu_assert(DList_count(dlist) == 2, "Wrong count after remove.");
	mu_assert(DList_first(dlist) == test3, "Wrong first after remove.");
	mu_assert(DList_last(dlist) == test1, "Wrong last after remove.");

	return NULL;
}

char *test_shift() {
	mu_assert(DList_count(dlist) != 0, "Wrong count before shift.");

	char *val = DList_shift(dlist);
	mu_assert(val == test3, "Wrong value on shift.");

	val = DList_shift(dlist);
	mu_assert(val == test1, "Wrong value on shift.");
	mu_assert(DList_count(dlist) == 0, "Wrong count after shift.");

	return NULL;
}

char *test_sim_dist() {

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_2d);
	mu_run_test(test_maze);

	mu_run_test(test_create);
	mu_run_test(test_push_pop);
	mu_run_test(test_unshift);
	mu_run_test(test_remove);
	mu_run_test(test_shift);
	mu_run_test(test_destroy);

	return NULL;
}
