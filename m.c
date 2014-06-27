
#line 1 "m.rl"
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 4096
char inbuffer[MAX_LINE_LENGTH];
char outbuffer[MAX_LINE_LENGTH];


#line 12 "m.c"
static const int parser_start = 1;
static const int parser_first_final = 3;
static const int parser_error = 0;

static const int parser_en_main = 1;


#line 13 "m.rl"


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
			strcpy(outbuffer, ",\n{");
		} else {
			strcpy(outbuffer, "{");
		}

		// Start the machine running on the input buffer
		p = inbuffer;
		pe = inbuffer + strlen(inbuffer);
		ts = p;

		
#line 64 "m.c"
	{
	cs = parser_start;
	}

#line 56 "m.rl"
		
#line 71 "m.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr0;
	} else if ( (*p) >= 65 )
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 3 "machine.rl"
	{ mark(); }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 95 "m.c"
	if ( (*p) == 32 )
		goto tr2;
	if ( (*p) < 65 ) {
		if ( 9 <= (*p) && (*p) <= 13 )
			goto tr2;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st2;
	} else
		goto st2;
	goto st0;
tr2:
#line 5 "machine.rl"
	{ emit("user");    }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 115 "m.c"
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 57 "m.rl"

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
