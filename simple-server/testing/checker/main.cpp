#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char * argv[]) {
    pid_t pid = fork();
    string command = "echo " + to_string(pid) + " > /sys/fs/cgroup/memory/group0/tasks";
    int l = system(command.c_str());

    char * a = argv[1];
    //int n = atoi(argv[2]);
    string str = a;
    string new_str = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            break;
        } else {
            new_str = new_str + str[i];
        }
    }
    string tmp = new_str;
    new_str = "g++ " + str + " -o " + new_str + ".exe";
    int i = system(new_str.c_str());
    str = "./" + tmp + ".exe";
    //start contestian program
    time_t start = time(0);
    i = execl(str.c_str(), NULL);
    double seconds_since_start = difftime(time(0), start);
    if (seconds_since_start - 2.0 > 0.00001) {
        cout << "TL ";
        exit(0);
    }
    // stop contestian program
    str = "./checker.exe input.txt output.txt ans.txt";
    i = system(str.c_str());
    if (i == 0) {
        cout << "OK";
    } else {
        cout << "WA";
    }
}
