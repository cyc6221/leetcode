class ExamTracker {
public:
    vector<int> t;
    vector<long long> prefix;
    
    ExamTracker() {
            
    }
    
    void record(int time, int score) {
        t.push_back(time);

        if(prefix.empty()) prefix.push_back(score);
        else prefix.push_back(prefix.back() + score);
    }
    
    long long totalScore(int startTime, int endTime) {
        int L = lower_bound(t.begin(), t.end(), startTime) - t.begin();
        int R = upper_bound(t.begin(), t.end(), endTime) - t.begin();

        if(L >= R) return 0;

        long long total = prefix[R - 1];
        if(L > 0) total -= prefix[L - 1];

        return total;
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */