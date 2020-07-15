#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include<string.h>
static void

    handle_events(int fd,FILE* fd2, int wd  , FILE* fd3)
    {
		char buf[4096]
   		__attribute__ ((aligned(__alignof__(struct inotify_event))));
		char buf2[4096];
		long int start, end;
		const struct inotify_event *event;
		int i;
		int flag =0;
		ssize_t len;
		char *ptr;

		/* Loop while events can be read from inotify file descriptor. */
		for (;;)
		{
   			/* Read some events. */
			flag =0;
   			len = read(fd, buf, sizeof buf);	
	    if (len == -1 && errno != EAGAIN) {
		   perror("read");
		   exit(EXIT_FAILURE);
	    }

	    if (len <= 0)
		   break;

        for(ptr = buf; ptr < buf + len;ptr += sizeof(struct inotify_event) + event->len)
        {

	       event = (const struct inotify_event *) ptr;
	    /* Print event type */	
		    if (event->mask & IN_MODIFY && flag == 0)
				flag = 1;
				start = ftell(fd2);
				fseek(fd2, 0, SEEK_END);
				end = ftell(fd2);
				fseek(fd2, start, SEEK_SET);
				while(ftell(fd2)<end)
				{
					fread(buf2, sizeof buf2, 1, fd2);
					fprintf(fd3, "%s", buf2);
					buf2[0] = '\0';
				}
				fseek(fd2, 0, SEEK_END);

	        if(event->len)
		        printf("%s", event->name);

        }
    }
}

int main()
{
	char buf;
	int fd, i, poll_num;
	FILE* fd2;
	FILE* fd3;

	int wd;
	nfds_t nfds;
	struct pollfd fds[2];

	/* Create the file descriptor for accessing the inotify API */

	fd = inotify_init1(IN_NONBLOCK);
	if (fd == -1)
	{
		perror("inotify_init1");
		exit(EXIT_FAILURE);
	}

	
	wd = inotify_add_watch(fd, "/var/log/auth.log", IN_ACCESS | IN_MODIFY);	
	fd2 = fopen("/var/log/auth.log", "r");
	fd3 = fopen("changes.txt" , "w");

	if (wd == -1)
	{
	   fprintf(stderr, "Cannot watch '%s': %s\n",
			   "/var/log/auth.log", strerror(errno));
	   exit(EXIT_FAILURE);
	}

	/* Prepare for polling */

	nfds = 2;

	/* Console input */

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN;

	/* Inotify input */

	fds[1].fd = fd;
	fds[1].events = POLLIN;

	/* Wait for events and/or terminal input */

	printf("Listening for events.\n");
	while (1)
	{
	    poll_num = poll(fds, nfds, -1);
	    if (poll_num == -1)
	    {
		    if (errno == EINTR)
			   continue;
		    perror("poll");
		    exit(EXIT_FAILURE);
	    }
	    if (poll_num > 0) {

		    if (fds[0].revents & POLLIN)
		    {
         	   /* Console input is available. Empty stdin and quit */
			    while (read(STDIN_FILENO, &buf, 1) > 0 && buf != '\n')
				   continue;
			    break;
		    }

		    if (fds[1].revents & POLLIN){
			   /* Inotify events are available */
			    handle_events(fd, fd2, wd ,fd3);
		    }
	   }
	}

	printf("Listening for events stopped.\n");


	close(fd);
	fclose(fd2);
	
	exit(EXIT_SUCCESS);
}
