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

    string command = "g++ -std=c++11 " + dir + "/testing.cpp -o " + dir + "/testing.exe";

    int ret = system(command.c_str());
    if (ret != 0) {
        return CE;
    }
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

        ret = system(command.c_str()) / 256;
        if (ret == 0) {
            return OK;
        } else {
            return WA;
        }
    }
    return 0;
}
