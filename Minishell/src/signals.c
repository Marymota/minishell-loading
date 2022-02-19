/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmota <marmota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:15:25 by pestevao          #+#    #+#             */
/*   Updated: 2022/02/18 13:31:22 by marmota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ctrl + c = singint
	ctrl + \ = singquit
	ctrl + d = eof
	
	STTY SETTINGS
	tcgetattr() ->	Get the attributes for terminall
					Initializes the "term" termios struct so that it can be modified
	term.c_lflag &= ~(ECHOCTL) ->	Changes terminal settings so that when ctrl-c is used
									the '^C' is not printed
	tcsetattr ->	Set the parameters associated with the terminal (the one configured above)
					TCSANOW defines that changes shall be implemented immediately
*/

#include "../minishell.h"

void setup_stty()
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
	{
		perror("tcgetattr() error");
		exec_error();
	}
	else
	{
		term.c_lflag &= ~(ECHOCTL);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}	
}

void	handle_signal(int sig)
{
	(void) sig;
	if (g_v.sigprint == 1)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_v.last_exit = 1;
	}
	if (g_v.sigprint == 0)
		g_v.last_exit = 130;
}

void	setup_sig(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
