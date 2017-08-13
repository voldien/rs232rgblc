/**
    rs232 RGB LED controller binary
    Copyright (C) 2017  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include<rs232lc/r232lc.h>
#include<stdio.h>
#include<stdlib.h>
#include<getopt.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc,  char *const * argv){

	/*	*/
	int fd;
	int c;
	int index;
	char buf[3];
	size_t len;
	const char* path = "/dev/ttyS";
	RS232LC state;
	int fd = STDIN_FILENO;
	
	/*	*/
	static struct option longoption[] = {
			{"version",	no_argument,		NULL,	'v'},	/*	Print version of the driver library version.	*/
			{"device",	required_argument,	NULL,	'd'},	/*	Override the default character device.	*/
			{"file",	required_argument,	NULL,	'f'},	/*	Override the pipe file descriptor.	 */
			{NULL,		no_argument,		NULL,	0},
	};

	/*	Iterate through each option.	*/
	const char* const shortopt = "dv";
	while((c = getopt_long(argc, argv, shortopt, &index, &longoption))){
		switch(c){
		case 'v':
			printf("version %s.\n", rs232_version());
			exit(EXIT_SUCCESS);
			break;
		case 'd':
			path = optarg;
			break;
		case 'f':
			if(optarg){
				fd = open(optarg, O_RDONLY);
				if(fd < 0){
					fprintf(stderr, "failed open %s, %s.\n", optarg, strerror(errno));
					exit(EXIT_FAILURE);
				}
			}
			break;
		default:
			break;
		}
	}
	
	/*	Open file.	*/
	fd = open(path, O_RDONLY);
	if(fd < 0){
		fprintf(stderr, "failed open %s, %s.\n", path, strerror(errno));
		return EXIT_FAILURE;
	}

	/*	Initialize driver.	*/
	if(!rs232lc_init(&state, fd))
		return EXIT_FAILURE;

	/*	Read each byte.	*/
	if(isatty(STDIN_FILENO)){
		while(read(fd, buf, 3) > 0){
			rs232lc_set_rgb(&state, R232LC_RGB(buf[0], buf[1], buf[2]));
		}
	}

	/*	Release and close driver.	*/
	rs232lc_close(state);
	close(fd);

	/*	Exit.	*/
	return EXIT_SUCCESS;
}
