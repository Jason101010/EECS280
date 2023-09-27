// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {
	vector < pair<double, int> > a;
	sort(v);
	int temp;
	bool contains = false;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < a.size(); ++j) {
			if (v[i] == a[j].first) {
				temp = j;
				contains = true;
				break;
			}
		}
		if (!contains) {
			a.push_back({ v[i], 1 });
		}
		else {
			a.insert(a.begin() + temp,{a[temp].first, a[temp].second + 1});
			a.erase(a.begin()+ temp + 1);
		}
		contains = false;
	}
	return a;
}

int count(vector<double> v) {
	return v.size();
}

double sum(vector<double> v) {
	double sum = 0;
	for (int i = 0; i < count(v); ++i) {
		sum += v[i];
	}
	return sum;
}

double mean(vector<double> v) {
	double mean = sum(v);
	mean = mean / count(v);
	return mean;
}

double median(vector<double> v) {
	int size = count(v);
	int ind = size / 2;
	double med;
	if (size % 2 == 1) {
		med = v[ind];
	}
	else {
		med = (v[ind] + v[ind - 1]) / 2.0;
	}

	return med;
}

double mode(vector<double> v) {
	sort(v);
	int count = 1;
	int countMax = 1;
	int countMaxInd = 0;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] == v[i - 1]) {
			++count;
		}
		else {
			if (count > countMax) {
				countMax = count;
				countMaxInd = i - 1;
			}
			count = 1;
		}
	}
	return v[countMaxInd];
}

double min(vector<double> v) {
	sort(v);
	return v[0];
}

double max(vector<double> v) {
	sort(v);
	return v[v.size() - 1];
}

double stdev(vector<double> v) {
	double s = 0;
	double m = mean(v);
	for (int i = 0; i < v.size(); ++i) {
		s += pow((v[i] - m), 2.0);
	}
	s = s / (count(v) - 1);
	s = sqrt(s);
	return s;
}

double percentile(vector<double> v, double p) {
	double rank;
	double perc;
	sort(v);
	rank = (p * (count(v) - 1)) + 1;
	double fractpart = 0;
	double intpart = 0;
	fractpart = modf(rank, &intpart);
	if (p == 1.0) {
		return v[count(v) - 1];
	}
	perc = v[intpart - 1] + fractpart * (v[intpart] - v[intpart - 1]);
	return perc;
}
