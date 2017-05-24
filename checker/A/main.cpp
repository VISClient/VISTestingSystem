#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

const double EPS = 1e-7;
const double TIME_LIMIT = 2.0;
const int OK = 0;
const int WA = 1;
const int TL = 2;
const int CE = 3;
const int ML = 4;

// If program catched TL or ML this function will be called and it will set default values on cgroup folders
void kill_all_process() {
    FILE *fp;
    fp = fopen("/sys/fs/cgroup/memory/1/tasks", "r");
    long long j;
    string s;
    while (fscanf(fp, "%lld", &j) > 0) {
        s = "kill -9 " + to_string(j);
        system(s.c_str());
    }
    fclose(fp);
    fp = fopen("/sys/fs/cgroup/cpuacct/1/tasks", "r");
    while (fscanf(fp, "%lld", &j) > 0) {
        s = "kill -9 " + to_string(j);
        system(s.c_str());
    }
    fclose(fp);
    fp = fopen("/sys/fs/cgroup/freezer/1/tasks", "r");
    while (fscanf(fp, "%lld", &j) > 0) {
        s = "kill -9 " + to_string(j);
        system(s.c_str());
    }
    fclose(fp);
    system("echo 0 > /sys/fs/cgroup/memory/1/memory.failcnt");
    system("echo 0 > /sys/fs/cgroup/cpuacct/1/cpuacct.usage");
    system("echo THAWED > /sys/fs/cgroup/freezer/1/freezer.state");
}

int main(int argc, char *argv[]) {
    string dir = "/home/ivan/Рабочий\\ стол/VISTestingSystem/checker/A";

    string compiler;

    string language = string(argv[1]);
    if (language == "C++") {
        compiler = "g++ -std=c++11 " + dir + "/testing.cpp -o " + dir + "/testing.exe";
    } else if (language == "Java") {
        compiler = "javac " + dir + "/Testing.java";
    }

    //if terminal returned not 0 signal then return compilation error
    int ret = system(compiler.c_str());

    if (ret != 0) {
        return CE;
    }

    //split processes on two
    pid_t pid = fork();
    if (pid == 0) {
        //child process 
        //write pid of child process in cgroup limits
        string tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/memory/1/tasks";
        system(tmp.c_str());
        tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/cpuacct/1/tasks";
        system(tmp.c_str());
	    tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/freezer/1/tasks";
        system(tmp.c_str());
        string runner;
        string io = "< " + dir + "/input.txt " + " > " + dir + "/output.txt";
        if (language == "C++") {
            runner = dir + "/testing.exe " + io;
        } else if (language == "Java") {
            runner = "java -cp " + dir + " Testing " + io;
        }
        //run contestian's program
        system(runner.c_str());
    } else {
        //parent process
        sleep(3);
        //freeze all process in cgroups
	    system("echo FROZEN > /sys/fs/cgroup/freezer/1/freezer.state");
	    freopen("/sys/fs/cgroup/memory/1/memory.failcnt", "r", stdin);
        int count = 0;
        cin >> count;
        //check on memory limit. In memory.failcnt we store counter that stores info about memory axceeding
        if (count > 0) {
            kill_all_process();
	        cout << "ML" << endl;
            return  ML;
        }
        freopen("/sys/fs/cgroup/cpuacct/1/cpuacct.usage", "r", stdin);
        long long full_time = 0;
        cin >> full_time;
	    //cout << "time is " << full_time << endl;
        //check full time in cgroup. If program worked more than TL, then kill our processes and return TL
        if (full_time - 2000000000 > 0) {
            kill_all_process();
	        cout << "TL" << endl;
            return TL;
        }
        
        //all is correct, kill all processes and set default values and then check answer of contestian
	    kill_all_process();
        string command = dir + "/checker.exe " + dir + "/input.txt "
                         + dir + "/output.txt " + dir + "/ans.txt";

        ret = system(command.c_str()) / 256;
        if (ret == 0) {
            //right answer
	        cout << "OK" << endl;
            return OK;
        } else {
            //wrong answer
	        cout << "WA" << endl;
            return WA;
        }
    }

    return 0;
}
