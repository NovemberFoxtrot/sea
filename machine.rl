%%{
	machine clf;
	action mark { mark(); }

	word    = alpha+         >mark %{ emit("user");    };

	line = (
		word            space
	);
}%%
