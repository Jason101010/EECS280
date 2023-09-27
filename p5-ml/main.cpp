// Project UID db1f506d06d84ab787baf250c265e24e


#include "csvstream.h"
#include <set>
#include <cmath>
using namespace std;

class Classifier {
public:

    Classifier(csvstream* train_in, csvstream* test_in) :
        train(train_in), test(test_in), debug(false), size(0)
    {
    }

    Classifier(csvstream* train_in, csvstream* test_in, bool b) :
        train(train_in), test(test_in), debug(b), size(0)
    {
    }

    
    
    void run() {
        if (debug) {
            cout << "training data:" << endl;
        }
        read_rows_train();
        cout << "trained on " << size << " examples" << endl;
        if (debug) {
            debug_output_training();
        }
        read_rows_test();
        int count = predict_all();
        cout << "performance: " << count << " / " << correct.size()
            << " posts predicted correctly" << endl << endl;
    }
    
   

public:
    csvstream* train;
    csvstream* test;
    bool debug;
    int size;
    map<int,set<string>> words_found;
    map<string, int> words;
    map<string, int> tags;
    map<pair<string, string>, int> both;
    map<int, string> test_content;
    map<pair<string,int>, string> correct; //content, tag
    

    set<string> unique_words(const string& str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    void read_rows_train() {
        string l;
        string w;
        set<string> strings;
        map<string, string> temp;
        while (*train >> temp) {
            l = temp["tag"];
            w = temp["content"];
            if (debug) {
                cout << "  label = " << l << ", content = " << w << endl;
            }
            tags[l] += 1;
            strings = unique_words(w);
            for (string s : strings) {
                words[s] += 1;
                both[{l, s}] += 1;
            }
            ++size;
        }
    }

    void read_rows_test() {
        set<string> strings;
        string w;
        string l;
        map<string, string> temp;
        int count = 0;
        while (*test >> temp) {
            w = temp["content"];
            l = temp["tag"];
            correct[{w, count}] = l;
            test_content[count] = w;
            strings = unique_words(w);
            for (string s : strings) {
                words_found[count].insert(s);
            }
            ++count;
        }
    }


    double log_likely(string s, string tag, double count) {
        double prob = 0.0;
        if (count > 0) {
            prob += log(count / tags[tag]);
        }
        else if (words[s] != 0) {

            prob += log(static_cast<double>(words[s]) / size);
        }
        else {


            prob += log(1.0 / static_cast<double>(size));
        }
        return prob;
    }

    double log_probabilitie_score(string tag, int ind) {
        double prob = 0.0;
        prob += log(static_cast<double>(tags[tag]) / size);
        for (string s : words_found[ind]) {
            if (both[{tag, s}] != 0) {
                prob += log(static_cast<double>(both[{tag, s}]) / tags[tag]);
            }
            else if (words[s] != 0) {
                prob += log(static_cast<double>(words[s]) / size);
            }
            else {
                prob += log(1.0 / static_cast<double>(size));
            }
        }
        return prob;
    }

    pair<string,double> predict_one(int ind) {
        double max = log_probabilitie_score(tags.begin()->first, ind);
        double temp;
        string tag_chosen = tags.begin()->first;
        for (auto s : tags) {
            temp = log_probabilitie_score(s.first, ind);
            if (temp > max) {
                max = temp;
                tag_chosen = s.first;
            }
        }
        return { tag_chosen, max };
    }

    int predict_all() {
        int count = 0;
        cout << "\ntest data:" << endl;
        string temp;
        for (int i = 0; i < correct.size(); ++i) {
            temp = test_content[i];
            pair<string, double> result = predict_one(i);
            cout << "  correct = " << correct[{temp, i}] << ", predicted = " 
                << result.first
                << ", log-probability score = " << result.second << endl;
            cout << "  content = " << temp << endl << endl;
            if (result.first == correct[{temp, i}]) {
                ++count;
            }
        }
        return count;
    }
    void debug_output_training() {
        cout << "vocabulary size = " << words.size() << endl << endl;
        cout << "classes:" << endl;
        for (auto s : tags) {
            cout << "  " << s.first << ", " << s.second << " examples, log-prior = "
                << log(static_cast<double>(tags[s.first]) / size) << endl;
        }
        cout << "classifier parameters:" << endl;
        for (auto s : both) {
            cout << "  " << s.first.first << ":"
                << s.first.second << ", count = " << s.second
                << ", log-likelihood = "
                << log_likely(s.first.second, s.first.first, s.second) << endl;
        }
    }

};

int main(int argc, char** argv){
    cout.precision(3);
    
    if (argc != 3) {
        if (argc != 4) {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }
        string s = argv[3];
        if (s != "--debug") {
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }
    }
    csvstream train(argv[1]);
    csvstream test(argv[2]);
    bool dbug = false;
    if (argc != 3) {
        dbug = true;
    }
    Classifier c(&train, &test, dbug);
    c.run();
}

