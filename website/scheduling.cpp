#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, arrival, burst, priority;
    int remaining;
    int completion = 0;
    int tat = 0;
    int wt = 0;
    int rt = -1;
};

struct Seg { int pid, start, end; };

vector<Process> parseData(string data) {
    vector<Process> v;
    stringstream ss(data);
    string line;
    while (getline(ss, line, ';')) {
        stringstream s(line);
        Process p;
        if (!(s >> p.pid >> p.arrival >> p.burst >> p.priority)) continue;
        p.remaining = p.burst;
        v.push_back(p);
    }
    return v;
}

string esc(string s){
    string o="";
    for(char c:s){
        if(c=='"') o+="\\\"";
        else if(c=='\\') o+="\\\\";
        else if(c=='\n') o+="\\n";
        else o+=c;
    }
    return o;
}

/* ---------------- FCFS ---------------- */
void runFCFS(vector<Process>& p, vector<Seg>& g){
    sort(p.begin(), p.end(), [&](auto &a, auto &b){
        if(a.arrival != b.arrival) return a.arrival < b.arrival;
        return a.pid < b.pid;
    });

    int time=0;
    for(auto& pr:p){
        if(time < pr.arrival) time = pr.arrival;
        int st=time;
        if(pr.rt==-1) pr.rt = st - pr.arrival;
        int en = st + pr.burst;

        pr.completion=en;
        pr.tat=en-pr.arrival;
        pr.wt=pr.tat-pr.burst;

        g.push_back({pr.pid, st, en});
        time=en;
    }
}
