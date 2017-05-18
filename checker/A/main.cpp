#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

const double EPS = 1e-7;
const double TIME_LIMIT = 2.0;
const int OK = 0;
const int WA = 1;
const int TL = 2;
const int CE = 3;
const int PE = 4;
const int ML = 5;
const int ME = 4;


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
    system("echo 0 > /sys/fs/cgroup/memory/1/memory.failcnt");
    system("echo 0 > /sys/fs/cgroup/cpuacct/1/cpuacct.stat");
}

int main(int argc, char *argv[]) {
    string dir = "/home/vadim/universe/web-server/VISTestingSystem/checker/A";

<<<<<<< HEAD
    string compiler;


    string language = string(argv[1]);
    if (language == "C++") {
        compiler = "g++ -std=c++11 " + dir + "/testing.cpp -o " + dir + "/testing.exe";
    } else if (language == "Java") {
        compiler = "javac " + dir + "/Testing.java";
    }

    
    int ret = system(compiler.c_str());
    string command = "g++ -std=c++11 " + dir + "/testing.cpp -o " + dir + "/testing.exe";

    int ret = system(command.c_str());
>>>>>>> a90f55ebb279148e0ecd68452c2c58ab862b6e81
    if (ret != 0) {
        return CE;
    }
<<<<<<< HEAD

    double start = (double) clock() / CLOCKS_PER_SEC;

    pid_t pid = fork();
    if (pid == 0) {
        string limit = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/memory/group0/tasks";
        ret = system(limit.c_str());
        string runner;
        string io = "< " + dir + "/input.txt " + " > " + dir + "/output.txt";
        if (language == "C++") {
            runner = dir + "/testing.exe " + io;
        } else if (language == "Java") {
            runner = "java -cp " + dir + " Testing " + io;
        }
        system(runner.c_str());
    } else {

        int status;
        while (1) {
            double diff = (double) clock() / CLOCKS_PER_SEC - start;
            pid_t returned_pid = waitpid(pid, &status, WNOHANG);
            if (returned_pid < 0) {
                return PE;
            }
            if (diff > TIME_LIMIT && returned_pid == 0) {
                return TL;
            } else if (returned_pid == pid) {
                break;
            }
        }

        string command = dir + "/checker.exe " + dir + "/input.txt "
        + dir + "/output.txt " + dir + "/ans.txt";
        
=======
    pid_t pid = fork();
    if (pid == 0) {
        string tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/memory/1/tasks";
        system(tmp.c_str());
        tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/cpuacct/1/tasks";
        system(tmp.c_str());
        command = dir + "/testing.exe < " + dir + "/input.txt " + " > " + dir + "/output.txt";
        system(command.c_str());
    } else {
        sleep(2000);
        freopen("/sys/fs/cgroup/cpuacct/1/cpuacct.stat", "r", stdin);
        long long full_time;
        cin >> full_time;
        full_time /= 1000000000;
        if ((double)full_time - 2.0 > 0.00000001) {
            kill_all_process();
            return TL;
        }
        freopen("/sys/fs/cgroup/cpuacct/1/memory.failcnt", "r", stdin);
        int count;
        cin >> count;
        if (count > 0) {
            kill_all_process();
            return  ME;
        }
        command = dir + "/checker.exe " + dir + "/input.txt "
                  + dir + "/output.txt " + dir + "/ans.txt";

>>>>>>> a90f55ebb279148e0ecd68452c2c58ab862b6e81
        ret = system(command.c_str()) / 256;
        if (ret == 0) {
            return OK;
        } else {
            return WA;
        }
    }
    return 0;
}
