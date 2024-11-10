void help_c(char username[], int *al)
{
	printw("\n\nWELCOME TO SSHELL, DEAR %s\n", username);
	printw("sshell is stands for simple shell, maybe .\n\n");
	printw("there is some of unique commands of sshell :\n\n");
	printw("help -> shows the help screen .\n");
	printw("saywithsmile [word] -> prints your word with smiling face .\n");

	*al += 7;
}
