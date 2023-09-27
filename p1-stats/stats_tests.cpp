/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_summarize();
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  test_summarize();
  test_count();
  test_sum();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();
 
  // Call your test functions here

  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

void test_summarize() {
	cout << "test_summarize" << endl;

}

void test_count() {
	cout << "test_count" << endl;
	vector<double> data;
	data.push_back(0);
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	assert(count(data) == 4);
}

void test_sum() {
	cout << "test_sum" << endl;
	vector<double> data;
	data.push_back(0);
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	assert(sum(data) == 6.0);
}

void test_mean() {
	cout << "test_mean" << endl;
	vector<double> data;
	data.push_back(0);
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	assert(mean(data) == 1.5);
}

void test_median() {
	cout << "test_median" << endl;
	vector<double> data;
	data.push_back(0);
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	assert(median(data) == 1.5);
	vector<double> data2;
	data2.push_back(1);
	data2.push_back(2);
	data2.push_back(3);
	assert(median(data2) == 2.0);
}

void test_mode() {
	cout << "test_mode" << endl;
	vector<double> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(0);
	data.push_back(1);
	data.push_back(1);
	data.push_back(3);
	assert(mode(data) == 1.0);
	vector<double> data2;
	data2.push_back(1);
	data2.push_back(2);
	data2.push_back(0);
	data2.push_back(1);
	data2.push_back(2);
	data2.push_back(3);
	assert(mode(data2) == 1.0);
	vector<double> data3;
	data3.push_back(0);
	data3.push_back(1);
	data3.push_back(2.1);
	data3.push_back(2.1);
	data3.push_back(3);
	data3.push_back(1);
	data3.push_back(2.1);
	assert(mode(data3) == 2.1);
}

void test_min() {
	cout << "test_min" << endl;
	vector<double> data;
	data.push_back(2);
	data.push_back(3);
	data.push_back(0);
	data.push_back(0.1);
	data.push_back(1);
	data.push_back(1);
	data.push_back(1);
	assert(min(data) == 0.0);
}

void test_max() {
	cout << "test_max" << endl;
	vector<double> data;
	data.push_back(2);
	data.push_back(3.1);
	data.push_back(0);
	data.push_back(0);
	data.push_back(1);
	data.push_back(1);
	data.push_back(1);
	assert(max(data) == 3.1);
}

void test_stdev() {
	cout << "test_stdev" << endl;
	vector<double> data;
	data.push_back(1);
	data.push_back(1);
	data.push_back(1);
	assert(stdev(data) == 0.0);
	vector<double> data2;
	data2.push_back(1);
	data2.push_back(4);
	data2.push_back(1);
	data2.push_back(3);
	data2.push_back(5);
	assert(abs(stdev(data2) - 1.788854) < 0.00001);
}

void test_percentile() {
	cout << "test_percentile" << endl;
	vector<double> data;
	data.push_back(15);
	data.push_back(20);
	data.push_back(40);
	data.push_back(50);
	data.push_back(35);
	assert(percentile(data, 0.4) == 29);
	vector<double> data2;
	data2.push_back(1);
	data2.push_back(1);
	data2.push_back(1);
	data2.push_back(1);
	data2.push_back(1);
	assert(percentile(data2, 0.9) == 1);
}
