

#include "minishell.h"

void	set_heredoc_signals()
{
	struct sigaction	ignored;
	struct sigaction	ctrl_c;

	ft_bzero(&ignored, sizeof(ignored));
	ignored.sa_handler = SIG_IGN;
	sigemptyset(&ignored.sa_mask);
	sigaction(SIGQUIT, &ignored, NULL);
	ft_bzero(&ctrl_c, sizeof(ctrl_c));
	ctrl_c.sa_handler = heredoc_ctrl_c_handler;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	set_heredoc_mode(t_shell *core, int mode)
{
	if (mode == ON)
	{
		set_heredoc_signals();
		set_termios(&core->term);
	}
	if (mode == OFF)
	{
		ignore_signals();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	}
}