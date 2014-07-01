#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096
char inbuffer[MAX_LINE_LENGTH];
char outbuffer[MAX_LINE_LENGTH];

%%{
	machine parser;
	include clf "machine.rl";
	main := line;
	write data;
}%%

// Declare these in global scope so that the machine and our action
// definitions can access them.
int cs;
char *p;
char *pe;
char *ts;

// Mark is similar, but C has no notion of instance variables
// To emit, we write this key:value pair to our output buffer
static inline void mark() { 
	ts = p;
}

static inline void emit(char *type) {
	*p = '\0';
	char fmtbuffer[MAX_LINE_LENGTH];
	sprintf(fmtbuffer, "\"%s\":\"%s\",", type, ts);
	strcat(outbuffer, fmtbuffer);
}

int main() {
	int lines = 0;

	fputc('[', stdout); // Start the list

	while (fgets(inbuffer, MAX_LINE_LENGTH, stdin) != NULL) {

		// Start writing the JSON object to the buffer
		// Include a leading comma if we need to separate it from its
		// predecessor
		if (lines) {
			strcpy(outbuffer, ",\n {");
		} else {
			strcpy(outbuffer, "{");
		}

		// Start the machine running on the input buffer
		p = inbuffer;
		pe = inbuffer + strlen(inbuffer);
		ts = p;

		fprintf(stdout, "1p  : %s", p);
		fprintf(stdout, "1pe : %s", pe);
		fprintf(stdout, "1ts : %s", ts);

		%% write init;
		%% write exec;

		fprintf(stdout, "2p  : %s", p);
		fprintf(stdout, "2pe : %s", pe);
		fprintf(stdout, "2ts : %s", ts);

		// Finalize the object, chomping off the last comma
		int len = strnlen(outbuffer, MAX_LINE_LENGTH);

		outbuffer[len - 1] = '\0';

		fprintf(stdout, "%s}", outbuffer);

		lines++;
	}

	fprintf(stdout, "]\n");

	return 0;
}

double test21(double * restrict a)
{
	size_t i;

	double *x = __builtin_assume_aligned(a, 16);
	double y = 0;

	for (i = 0; i < 10000; i++)
	{
		y += x[i];
	}

	return y;
}


void test9(double * restrict a, double * restrict b)
{
	size_t i;

	double *x = __builtin_assume_aligned(a, 16);
	double *y = __builtin_assume_aligned(b, 16);

	for (i = 0; i < 1000; i++)
	{
		/* max() */
		x[i] = ((y[i] > x[i]) ? y[i] : x[i]);
	}
}
