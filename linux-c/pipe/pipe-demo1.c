#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <some-string>\n", argv[0]);
		return -1;
	}

	if (pipe(pipefd) == -1) {
		perror("pipe");
		return -1;
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		return -1;
	}

	if (cpid == 0) {
		close(pipefd[1]);

		printf("Recv: ");
		fflush(stdout);
		while(read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		return 0;
	} else {
		close(pipefd[0]);
		printf("Send: %s\n", argv[1]);
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);
		wait(NULL);
		return 0;
	}

}
