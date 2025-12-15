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

// scheduling.cpp — FINAL FIXED VERSION
// Supports: RT, ReadyQueueTimeline, FCFS, SJF-NP, SJF-P, Priority NP/P, RR

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

/* ---------------- SJF NP ---------------- */
void runSJF_NP(vector<Process>& p, vector<Seg>& g){
    int n=p.size();
    vector<bool> done(n,false);
    int finished=0, time=0;

    while(finished<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++){
            if(!done[i] && p[i].arrival<=time && p[i].burst < best){
                best=p[i].burst;
                idx=i;
            }
        }
        if(idx==-1){ time++; continue; }

        int st=max(time,p[idx].arrival);
        if(p[idx].rt==-1) p[idx].rt = st - p[idx].arrival;
        int en=st+p[idx].burst;

        p[idx].completion=en;
        p[idx].tat=en-p[idx].arrival;
        p[idx].wt=p[idx].tat-p[idx].burst;

        g.push_back({p[idx].pid, st, en});
        done[idx]=true;
        finished++;
        time=en;
    }
}

/* ---------------- SJF Preemptive (SRTF) ---------------- */
void runSJF_P(vector<Process>& p, vector<Seg>& g){
    int n=p.size();
    vector<int> rem(n);
    for(int i=0;i<n;i++) rem[i]=p[i].burst;

    int done=0, time=0;

    while(done<n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++){
            if(rem[i]>0 && p[i].arrival<=time && rem[i]<best){
                best=rem[i];
                idx=i;
            }
        }
        if(idx==-1){ time++; continue; }

        int st=time;
        if(p[idx].rt==-1) p[idx].rt = st - p[idx].arrival;

        rem[idx]--; time++;

        int en=time;

        if(!g.empty() && g.back().pid==p[idx].pid && g.back().end==st)
            g.back().end=en;
        else
            g.push_back({p[idx].pid, st, en});

        if(rem[idx]==0){
            p[idx].completion=time;
            p[idx].tat=time-p[idx].arrival;
            p[idx].wt=p[idx].tat-p[idx].burst;
            done++;
        }
    }
}

/* ---------------- Priority NP ---------------- */
void runPriority_NP(vector<Process>& p, vector<Seg>& g, bool high){
    int n=p.size();
    vector<bool> done(n,false);
    int time=0, finished=0;

    while(finished<n){
        int idx=-1;
        for(int i=0;i<n;i++){
            if(!done[i] && p[i].arrival<=time){
                if(idx==-1) idx=i;
                else{
                    if(high && p[i].priority > p[idx].priority) idx=i;
                    if(!high && p[i].priority < p[idx].priority) idx=i;
                }
            }
        }

        if(idx==-1){ time++; continue; }

        int st=max(time,p[idx].arrival);
        if(p[idx].rt==-1) p[idx].rt = st - p[idx].arrival;
        int en=st+p[idx].burst;

        p[idx].completion=en;
        p[idx].tat=en-p[idx].arrival;
        p[idx].wt=p[idx].tat-p[idx].burst;

        g.push_back({p[idx].pid, st, en});

        done[idx]=true;
        finished++;
        time=en;
    }
}

/* ---------------- Priority Preemptive ---------------- */
void runPriority_P(vector<Process>& p, vector<Seg>& g, bool high){
    int n=p.size();
    vector<int> rem(n);
    for(int i=0;i<n;i++) rem[i]=p[i].burst;

    int time=0, done=0;

    while(done<n){
        int idx=-1;
        for(int i=0;i<n;i++){
            if(rem[i]>0 && p[i].arrival<=time){
                if(idx==-1) idx=i;
                else{
                    if(high && p[i].priority > p[idx].priority) idx=i;
                    if(!high && p[i].priority < p[idx].priority) idx=i;
                }
            }
        }
        if(idx==-1){ time++; continue; }

        int st=time;
        if(p[idx].rt==-1) p[idx].rt = st - p[idx].arrival;

        rem[idx]--; time++;
        int en=time;

        if(!g.empty() && g.back().pid==p[idx].pid && g.back().end==st)
            g.back().end=en;
        else
            g.push_back({p[idx].pid, st, en});

        if(rem[idx]==0){
            p[idx].completion=time;
            p[idx].tat=time-p[idx].arrival;
            p[idx].wt=p[idx].tat-p[idx].burst;
            done++;
        }
    }
}

/* ---------------- Round Robin ---------------- */
void runRR(vector<Process>& p, vector<Seg>& g, int q){
    int n=p.size();
    sort(p.begin(), p.end(), [&](auto &a, auto &b){
        return a.arrival < b.arrival;
    });

    vector<int> rem(n);
    for(int i=0;i<n;i++) rem[i]=p[i].burst;

    queue<int> qn;
    int time=0, idx=0;

    while(idx<n && p[idx].arrival<=time){
        qn.push(idx);
        idx++;
    }
    if(qn.empty() && idx<n){
        time=p[idx].arrival;
        qn.push(idx++);
    }

    while(!qn.empty()){
        int i=qn.front(); qn.pop();

        int st=time;
        if(p[i].rt==-1) p[i].rt = st - p[i].arrival;

        int exec=min(q, rem[i]);
        rem[i]-=exec; time+=exec;
        int en=time;

        if(!g.empty() && g.back().pid==p[i].pid && g.back().end==st)
            g.back().end=en;
        else
            g.push_back({p[i].pid, st, en});

        while(idx<n && p[idx].arrival<=time){
            qn.push(idx++);
        }

        if(rem[i]>0) qn.push(i);
        else{
            p[i].completion=time;
            p[i].tat=time-p[i].arrival;
            p[i].wt=p[i].tat-p[i].burst;
        }

        if(qn.empty() && idx<n){
            time=p[idx].arrival;
            qn.push(idx++);
        }
    }
}

/* -------- Build Ready Queue -------- */
vector<vector<int>> buildReady(const vector<Process>& p, const vector<Seg>& g, int total){
    vector<int> run(total, -1);
    for(auto&s:g){
        for(int t=s.start;t<s.end;t++) run[t]=s.pid;
    }

    vector<vector<int>> rq(total);

    for(int t=0;t<total;t++){
        for(auto &pr:p){
            if(pr.arrival<=t && pr.completion>t && run[t]!=pr.pid)
                rq[t].push_back(pr.pid);
        }
    }
    return rq;
}

/* -------- Build JSON -------- */
string makeJSON(string algo, vector<Process> orig, vector<Process> p, vector<Seg> g){
    unordered_map<int,Process> mp;
    for(auto &x:p) mp[x.pid]=x;

    int total=0;
    for(auto &s:g) total=max(total, s.end);

    auto rq=buildReady(p,g,total);

    stringstream o;
    o<<"{";
    o<<"\"algorithm\":\""<<algo<<"\",";
    o<<"\"totalTime\":"<<total<<",";

    o<<"\"processes\":[";
    for(int i=0;i<orig.size();i++){
        auto pr=mp[orig[i].pid];
        o<<"{"
         <<"\"pid\":"<<pr.pid<<","
         <<"\"arrival\":"<<pr.arrival<<","
         <<"\"burst\":"<<pr.burst<<","
         <<"\"priority\":"<<pr.priority<<","
         <<"\"completion\":"<<pr.completion<<","
         <<"\"tat\":"<<pr.tat<<","
         <<"\"wt\":"<<pr.wt<<","
         <<"\"rt\":"<<pr.rt
         <<"}";
        if(i+1<orig.size()) o<<",";
    }
    o<<"],";

    o<<"\"gantt\":[";
    for(int i=0;i<g.size();i++){
        o<<"{\"pid\":"<<g[i].pid<<",\"start\":"<<g[i].start<<",\"end\":"<<g[i].end<<"}";
        if(i+1<g.size()) o<<",";
    }
    o<<"],";

    o<<"\"readyQueueTimeline\":[";
    for(int t=0;t<rq.size();t++){
        o<<"{\"time\":"<<t<<",\"ready\":[";
        for(int j=0;j<rq[t].size();j++){
            o<<rq[t][j];
            if(j+1<rq[t].size()) o<<",";
        }
        o<<"]}";
        if(t+1<rq.size()) o<<",";
    }
    o<<"]";

    o<<"}";
    return o.str();
}

/* ---------------- MAIN ---------------- */
int main(int argc,char*argv[]){
    if(argc<3){ cout<<"{}"; return 0; }

    string algo=argv[1];
    string data=argv[2];
    int q = (argc>=4)? stoi(argv[3]) : 2;
    bool high = (argc>=5 && string(argv[4])=="high");

    auto orig = parseData(data);
    auto p = orig;

    vector<Seg> g;

    if(algo=="fcfs") runFCFS(p,g);
    else if(algo=="sjf-np") runSJF_NP(p,g);
    else if(algo=="sjf-p") runSJF_P(p,g);
    else if(algo=="priority-np") runPriority_NP(p,g,high);
    else if(algo=="priority-p") runPriority_P(p,g,high);
    else if(algo=="rr") runRR(p,g,q);

    cout<<makeJSON(algo,orig,p,g);
}
