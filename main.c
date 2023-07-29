#include "shell.h"

/**
 * main - Entry point of the shell.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	// Redirect file descriptor 2 (stderr) to fd (useful for testing).
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	// If a script is provided as an argument, open it for reading.
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			// Handle file open errors and exit with appropriate codes.
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	// Populate the environment list and read history from file.
	populate_env_list(info);
	read_history(info);

	// Start the shell.
	hsh(info, av);

	return (EXIT_SUCCESS);
}
