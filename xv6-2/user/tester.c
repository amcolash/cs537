// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
	const int KERNEL_NPROC = 64;
	const int CHILD_STARTUP_SLEEP = 100;
	const int MIN_UPTIME = 1000;
	if(argc!=2) {
    	printf(1, "%s", "USAGE: tester.c <int testnum>\n");
		exit();
	}
	int option = atoi(argv[1]);
	if(option == 0) {
		//SAME PERCENT RESERVE

		//Make this reserve 50
		int returnval = reserve(50);
		if(returnval < 0) {
			printf(1, "ERROR: reserve failed\n");
		}
		//Test 4 reserve procs with 50% reserve
		//Expect ~same number of times chosen
		const int NUM_PROC = 3;
		int pids[NUM_PROC+1];
		int chosen[NUM_PROC+1];
		int time[NUM_PROC+1];
		int charge[NUM_PROC+1];
		int i;
		int pid;
		pids[0] = getpid();
        for(i=0; i<NUM_PROC; i++) {
			pid = fork();
			if(pid == 0) {
				//child
				returnval = reserve(50);
				if(returnval < 0) {
					printf(1, "ERROR: reserve failed\n");
				}
				break;
			}
			else {
				//parent
				pids[i+1] = pid;
			}
		}
		if(pid == 0) {
			sleep(CHILD_STARTUP_SLEEP*2);
			while(1) {
			}
		}
		else {
			while(1) {
				sleep(MIN_UPTIME);
				struct pstat p;
				struct pstat *stats = &p;
				int returnval = getpinfo(stats);
				if(returnval < 0) {
					continue;
				}
				int count = 0;
				for(i=0; i<KERNEL_NPROC; i++) {
					int j;
					for(j=0; j<NUM_PROC+1; j++) {
						if(pids[j] == stats->pid[i] || getpid() == stats->pid[i]) {
							chosen[j] = stats->chosen[i];
							time[j] = stats->time[i];
							charge[j] = stats->charge[i];
							count++;
						}
					}
				}
				for(i=0; i<NUM_PROC+1; i++) {
					//pid,chosen,time,charge
					printf(1, "%d,%d,%d,%d\n", pids[i], chosen[i], time[i], charge[i]);
				}
			}
		}
	}

	else if(option == 2) {
		//DIFF BID SPOT

		//Make this spot with bid 50
		int returnval;
		returnval = spot(50);
		if(returnval < 0) {
			printf(1, "ERROR: spot failed\n");
		}
		//Expect significant difference in number of times chosen between bid levels
		const int NUM_PROC = 10;
		int pids[NUM_PROC+1];
		int chosen[NUM_PROC+1];
		int time[NUM_PROC+1];
		int charge[NUM_PROC+1];
		int i;
		int pid;
		int bid = 20;

		pids[0] = getpid();

        for(i=0; i<NUM_PROC; i++) {
			pid = fork();
			if(pid == 0) {
				//child
				returnval = spot(bid);
				if(returnval < 0) {
					printf(1, "ERROR: spot failed\n");
				}
				break;
			}
			else {
				//parent
				if(i==4) {
					bid+=10;
				}
				pids[i+1] = pid;
			}
		}
		if(pid == 0) {
			sleep(CHILD_STARTUP_SLEEP);
			while(1) {
			}
		}
		else {
			while(1) {
				sleep(MIN_UPTIME);
				struct pstat p;
				struct pstat *stats = &p;
				int returnval = getpinfo(stats);
				if(returnval < 0) {
					printf(1, "getpinfo failed\n");
					continue;
				}
				int count = 0;
				for(i=0; i<KERNEL_NPROC; i++) {
					int j;
					for(j=0; j<NUM_PROC+1; j++) {
						if(pids[j] == stats->pid[i]) {
							chosen[j] = stats->chosen[i];
							time[j] = stats->time[i];
							charge[j] = stats->charge[i];
							count++;
						}
					}
				}
				for(i=0; i<NUM_PROC+1; i++) {
					//pid,chosen,time,charge
					printf(1, "%d,%d,%d,%d\n", pids[i], chosen[i], time[i], charge[i]);
				}
			}
		}
	}
	else if(option == 3) {
		//DIFF PERCENT RESERVE

		//Make this reserve with 10 percent
		int returnval;
		returnval = reserve(10);
		if(returnval < 0) {
			printf(1, "ERROR: reserve failed\n");
		}
		//Test different reservation sizes
		//Sizes are 10 (parent proc), 20, 30, 40, 50, 50
		const int NUM_PROC = 5;
		int pids[NUM_PROC+1];
		int chosen[NUM_PROC+1];
		int time[NUM_PROC+1];
		int charge[NUM_PROC+1];
		int i;
		int pid;
		int percent = 20;

		pids[0] = getpid();

        for(i=0; i<NUM_PROC; i++) {
			pid = fork();
			if(pid == 0) {
				//child
				returnval = reserve(percent);
				if(returnval < 0) {
					printf(1, "ERROR: spot failed\n");
				}
				break;
			}
			else {
				//parent
				if(i<NUM_PROC-2) {
					percent+=10;
				}
				pids[i+1] = pid;
			}
		}
		if(pid == 0) {
			sleep(CHILD_STARTUP_SLEEP);
			while(1){
			}
		}
		else {
			while(1) {
				sleep(MIN_UPTIME);
				struct pstat p;
				struct pstat *stats = &p;
				int returnval = getpinfo(stats);
				if(returnval < 0) {
					continue;
				}
				int count = 0;
				for(i=0; i<KERNEL_NPROC; i++) {
					int j;
					//Find pid in pstat
					for(j=0; j<NUM_PROC+1; j++) {
						if(pids[j] == stats->pid[i]) {
							chosen[j] = stats->chosen[i];
							time[j] = stats->time[i];
							charge[j] = stats->charge[i];
							count++;
						}
					}
				}
        printf(1, "\n");
				for(i=0; i<NUM_PROC+1; i++) {
					//pid,chosen,time,charge
					printf(1, "pid: %d, chosen: %d, time: %d, charge: %d\n", pids[i], chosen[i], time[i], charge[i]);
				}
			}
		}
	}
	else if(option == 4) {
		//RESERVE CALL TOO LOW


		//Test user attempting to reserve a percentage < 0
		//Expect -1 to be returned from the reserve call
		int flag = reserve(-1);
		if(flag < 0) {
			printf(1, "Test succeeded, reserve call failed.\n");
		}
		else {
			printf(1, "ERROR: test failed. Reserve call did not fail when percentage < 0 was input.");
		}
		exit();
	}
	else if(option == 5) {
		//RESERVE CALL TOO HIGH

		//Test user attempting to reserve a percentage > 100
		//Expect -1 to be returned from the reserve call
		int flag = reserve(101);
		if(flag < 0) {
			printf(1, "Test succeeded, reserve call failed.\n");
		}
		else {
			printf(1, "ERROR: test failed. Reserve call did not fail when a percantage > 100 was input.");
		}
		exit();
	}
	else if(option == 6) {
		//RESERVE SUM TOO HIGH

		//Make this reserve of 100
		int returnval = reserve(100);
		if(returnval < 0) {
			printf(1, "ERROR: reserve failed\n");
		}
		//Test user attempting to reserve too much cpu (currentreservation + newreservation > 200)
		//Expect -1 to be returned from second child's reserve call
		const int NUM_PROC = 2;
		int pids[NUM_PROC];
		int i;
		int pid;
        for(i=0; i<NUM_PROC; i++) {
			pid = fork();
			if(pid == 0) {
				//child
				int flag = reserve(100);
				if(i==0 && flag < 0) {
					printf(1, "ERROR: incorrect reserve failed\n");
				}
				if(i==1 && flag < 0) {
					printf(1, "Test succeeded, reserve call failed.\n");
				}
				else if(i==1) {
					printf(1, "ERROR: test failed. Reserve call did not fail when the total process percent exceeded 200.");
				}
				break;
			}
			else {
				pids[i] = pid;
				sleep(100);
			}
		}
		if(pid == 0) {
			while(1);
		}
		else {
			sleep(500);
			for(i=0; i<NUM_PROC; i++) {
				kill(pids[i]);
				wait();
			}
			exit();
		}
	}

	else if(option == 7) {
		//CHARGE TEST

		//Make this reserve with 100
		int returnval = reserve(100);
		if(returnval < 0) {
			printf(1,"ERROR: spot call failed\n");
		}
		//Test charge in dollars
		//Expecting time*bid/nanodollars = charge
		//NOTE: ADD 10 to time and 1 to chosen to insure no error
		struct pstat p;
		struct pstat *stats = &p;
        //returnval = getpinfo(stats);
		int prevchosen = 0;
		int prevtime = 0;
		int i;
		int pid = fork();
		if(pid == 0) {
			returnval = spot(100);
			if(returnval < 0) {
				printf(1,"ERROR: reserve call failed\n");
			}
			while(1) {
			}
		}
		sleep(MIN_UPTIME);
		returnval = getpinfo(stats);
		if(returnval >= 0) {
			for(i=0; i<KERNEL_NPROC; i++) {
				if(pid == stats->pid[i]) {
					printf(1, "%d,%d,%d,%d\n", stats->pid[i], stats->chosen[i]-prevchosen, stats->time[i]-prevtime, stats->charge[i]);
				}
			}
		}
		else {
			printf(1, "ERROR: getpinfo failed\n");
		}
		while(1);
	}
	else if(option == 9) {
		//STARVATION TEST EXTRA CREDIT

		int returnval = reserve(100);
		if(returnval < 0) {
			printf(1, "ERROR: reserve failed\n");
		}
		//Test starvation
		//Expect ~same number of times chosen
		const int NUM_PROC = 4;
		int pids[NUM_PROC+1];
		int chosen[NUM_PROC+1];
		int time[NUM_PROC+1];
		int charge[NUM_PROC+1];
		int i;
		int pid;
		pids[0] = getpid();
        for(i=0; i<NUM_PROC; i++) {
			pid = fork();
			if(pid == 0) {
				//child
				if(i==0) {
					returnval = reserve(100);
					if(returnval < 0) {
						printf(1, "ERROR: reserve failed\n");
					}
				}
				else {
					returnval = spot(100);
					if(returnval < 0) {
						printf(1, "ERROR: reserve failed\n");
					}
				}
				break;
			}
			else {
				//parent
				if(i==0) {
					sleep(20);
				}
				pids[i+1] = pid;
			}
		}
		if(pid == 0) {
			while(1) {
			}
		}
		else {
			while(1) {
				sleep(MIN_UPTIME);
				struct pstat p;
				struct pstat *stats = &p;
				int returnval = getpinfo(stats);
				if(returnval < 0) {
					continue;
				}
				int count = 0;
				for(i=0; i<KERNEL_NPROC; i++) {
					int j;
					for(j=0; j<NUM_PROC+1; j++) {
						if(pids[j] == stats->pid[i] || getpid() == stats->pid[i]) {
							chosen[j] = stats->chosen[i];
							time[j] = stats->time[i];
							charge[j] = stats->charge[i];
							count++;
						}
					}
				}
				for(i=0; i<NUM_PROC+1; i++) {
					//pid,chosen,time,charge
					printf(1, "%d,%d,%d,%d\n", pids[i], chosen[i], time[i], charge[i]);
				}
			}
		}
	}
  return 0;
}
