#include <bits/types/struct_rusage.h>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

bool isExit = false;
void handler(int sig)
{
	std::cout << "Are you sure you want to exit? press y to accept" << std::endl;
	std::string str;
	std::getline(std::cin , str);
	if(str == "y")
	{
		isExit = true;
	}
	return;
}

int main()
{


//	int r = system("cat /proc/'pid'/stat | cut -d' ' -f23 | xargs -n 1 bash -c 'echo $(($1/1024))' args");
//	struct utsname buf1;
//	errno = 0;
//	if(uname(&buf1) != 0)
//	{
//		perror("uname doesn't return 0, there is an error");
//		exit(EXIT_FAILURE);
//	}
	pid_t pid;

	if(pid = fork() < 0) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0) {
		struct sigaction sa = { 0 };
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handler;
		sigaction(SIGINT , &sa , NULL);
		sleep(5);
		while(true)
		{
			system("ps eo user,pid,vsz,rss");
			sleep(5);
		//	int who = RUSAGE_SELF;
		//	struct rusage usage;
		//	int ret;
		//	ret = getrusage(who , &usage);
		//	std::cout << "max rss" << usage.ru_maxrss << std::endl;
		//	std::cout << "vss" << usage.ru_nvcsw << std::endl;
		//	pmap(getppid());
		//	std::string pmap_options = "ps 1 ";
		//	pmap_options += std::to_string(getppid());
		//	int r = system(pmap_options.c_str());
		//	pid_t pid = getppid();
		//	std::string string_pid = "";
		//	string_pid += "sudo cat /proc/m";
		//	string_pid += std::to_string(pid);
		//	string_pid += "/";
		//	int r = system(string_pid.c_str());
		//	string_pid = "";
		if(isExit == true)
			break;
		}	
			exit(0);
	} else {
			kill(getppid() , SIGINT);
			wait(NULL);
			if(isExit == true)
			{
				return 0;
			}
	}
	
//	std::cout << "System name" << buf1.sysname << std::endl;
//	std::cout << "Node name" << buf1.nodename << std::endl;
//	std::cout << "Version" << buf1.version << std::endl;
//	std::cout << "Release" << buf1.release << std::endl;
//	std::cout << "Machine" << buf1.machine << std::endl;

//	int who = RUSAGE_SELF;
//	struct rusage usage;
//	int ret;
//	ret = getrusage(who , &usage);
//	std::cout << usage.ru_maxrss << std::endl;

//	int r = system("cat /proc/1/arch_status");
}
