/* ragel so_tag.rl && gcc so_tag.c -o so_tag */
#include <stdio.h>
#include <string.h>

static char *text_start;

%%{
  machine parser;

  action MarkStart { text_start = fpc; }

  action PrintTextNode {
    int text_len = fpc - text_start;
    if (text_len > 0) {
      printf("TEXT(%.*s)\n", text_len, text_start);
    }
  }

  action PrintTagNode {
    int text_len = fpc - text_start - 1;  /* drop closing bracket */
    printf("TAG(%.*s)\n", text_len, text_start);
  }

  tag = '[[' (lower+ >MarkStart) ']]' @PrintTagNode;
  dig = '[[' (digit+ >MarkStart) ']]' @PrintTagNode;

  main := (
    (any - '[')* >MarkStart %PrintTextNode
    ('[' ^'[' %PrintTextNode | tag) >MarkStart
  )* @eof(PrintTextNode);
}%%

%% write data;

int main(void) {
	char buffer[4096];

	int cs;

	char *p = NULL;
	char *pe = NULL;
	char *eof = NULL;

  %% write init;

  do {
	  size_t nread = fread(buffer, 1, sizeof(buffer), stdin);

	  p = buffer;
	  pe = p + nread;

	  if (nread < sizeof(buffer) && feof(stdin)) {
		  eof = pe;
	  }

    %% write exec;

    if (eof || cs == %%{ write error; }%% ) {
			break;
		}

  } while (1);

  return 0;
}
