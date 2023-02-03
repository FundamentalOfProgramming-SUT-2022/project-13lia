#include <minivim.h>

/* editor_conf global var */
struct editor_conf g_e;

/* main */
int main(int argc, char *argv[]) {
	/* change terminal to raw mode */
	enb_raw_mode();

	/* initialise editor */
	init_editor();

	//tree list
	if (!strcmp(argv[1], "tree"))
	{
		printf("tree list\n");
		execv("tree",argv);
		//remove("../inc/tree");
		return 0;
	}
	/* open file in editor */
	if (argc >= 2)
		editor_open(argv[1]);
	
	/* set editor status msg empty at start */
	editor_set_status_msg("");

	/* program loop */
	while (1) {
		editor_refresh_screen();
		editor_process_keypress();
	}

	return (EXIT_SUCCESS);
}
