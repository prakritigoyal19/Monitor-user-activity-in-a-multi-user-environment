Developing a kernel module to monitor user activity in a multi-user environment

1.To run the monitor.c file:
$ gcc monitor.c
$ ./a.out

2.To run through ssh( For multi-user environment)
For creating server
$  gcc monitor.c
$ ./a.out

In other system(For client )
$ ssh server_user_name@<server_ip_address>
All the information from the auth file will be stored in changes.txt file

3.To run the data_analyzer.cpp
To extract information from changes.txt, run
$ g++ data_analyzer.cpp
$ ./a.out

Final output will be shown in output.txt file
