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


int main(int argc, char *argv[]) {
    //freopen("verdict.txt", "w", stdout);
    string dir = "/home/vadim/universe/web-server/VISTestingSystem/checker/A";

    string command = "g++ -std=c++11 " + dir + "/testing.cpp -o " + dir + "/testing.exe";

    int ret = system(command.c_str());
    if (ret != 0) {
        return CE;
    }
    double start = (double) clock() / CLOCKS_PER_SEC;
    pid_t pid = fork();
    if (pid == 0) {
        string tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/memory/group0/tasks";
        //ret = system(tmp.c_str());
        tmp = "echo " + to_string(getpid()) + " > /sys/fs/cgroup/cpu/group0/tasks";
        //ret = system(tmp.c_str());
        command = dir + "/testing.exe < " + dir + "/input.txt " + " > " + dir + "/output.txt";
        system(command.c_str());
    } else {
        int status;
        while (1) {
            double diff = (double) clock() / CLOCKS_PER_SEC - start;
            pid_t returned_pid = waitpid(pid, &status, WNOHANG);
            if (diff > TIME_LIMIT && returned_pid == 0) {
                return TL;
            } else if (returned_pid == pid) {
                break;
            }
        }
        
        command = dir + "/checker.exe " + dir + "/input.txt "
                  + dir + "/output.txt " + dir + "/ans.txt";

        ret = system(command.c_str()) / 256;
        if (ret == 0) {
            return OK;
        } else {
            return WA;
        }
    }
    return 0;
}
