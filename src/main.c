#include <stdint.h>
#include "dbg.h"
#include "miniunit.h"
#include <assert.h>
#include <stdio.h>

#include <Judy.h>

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

char *test_wiz() {
	Pvoid_t PJArray = (PWord_t)NULL; // Judy array.
	PWord_t PValue;			 // Judy array element.
	Word_t Bytes;			 // size of JudySL array.

	char dude[10] = "THE";

	JSLI(PValue, PJArray, "THE");
	*PValue += 1;

	JSLI(PValue, PJArray, "DUDE");
	*PValue += 1;

	JSLI(PValue, PJArray, "ABIDES");
	*PValue += 1;

	JSLI(PValue, PJArray, "the");
	(*PValue)++;

	if (PValue == PJERR) {
		printf("Malloc failed -- get more ram\n");
		exit(1);
	}

	dude[0] = '\0';

	JSLF(PValue, PJArray, dude);

	while(PValue != NULL) {
		printf("%s %d\n", dude, *PValue);
		JSLN(PValue, PJArray, dude);
	}

	JSLFA(Bytes, PJArray);

	printf("%lu bytes used\n", Bytes);

	return NULL;
}

char *all_tests() {
	mu_suite_start();

	mu_run_test(test_2d);
	mu_run_test(test_wiz);

	return NULL;
}
