//Quick & Dirty Testing ! C++

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>

extern "C" {
#include <assert.h>
#include "fence.h"
}

using std::vector;
using std::getline;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::cerr;
using std::endl;

//vector with the lines of the file
vector<vector<char>> read_file(const string&filename) {
    vector<vector<char>> result;
    ifstream file;
    file.open(filename);
    std::string line = "";
    while (getline(file, line)) {
	std::istringstream iss(line);
	vector<char> line_vector;
	char a = 0;
	while (iss >> a) {
	    line_vector.push_back(a);
	}
	if (line_vector.size() > 0) {
	    result.push_back(line_vector);
	}
    }
    file.close();
    return (result);
}

//line from right to left
fence_t from_vector(vector<char> vec) {
    fence_t fence = fence_P();
    if (vec.back() != 'P') {
	throw string("Invalid test case! Should end with P");
    }
    auto it = vec.rbegin();
    //ignore the last P:
    it++;
    while (it != vec.rend()) {
	switch (*it) {
	case 'A' : fence = fence_add_A(fence); break;
	case 'H' : fence = fence_add_H(fence); break;
	case 'P' : fence = fence_add_P(fence); break;
	case 'T' : fence = fence_add_T(fence); break;
	default: break;
	}
	it++;
    }
    return (fence);
}

//convers a fence to a vector
vector<char> to_vector(fence_t fence) {
    vector<char> result;
    type_t *elems = fence_to_array(fence);
    unsigned int size = fence_size(fence);
    for (unsigned int i = 0; i < size; i++) {
	switch (elems[i]) {
	case P: result.push_back('P'); break;
	case A: result.push_back('A'); break;
	case H: result.push_back('H'); break;
	case T: result.push_back('T'); break;
	default: ;
	}
    }
    free(elems);
    return (result);
}

//shows vector on screen
void display_vector(const vector<char> &v){
    std::copy(v.begin(), v.end(),
	      std::ostream_iterator<char>(std::cout, " "));
    cout << endl;
}

//compute perimeter
unsigned int get_perimeter(const vector<char> &v) {
    unsigned int perimeter = 0;
    for (char a : v) {
	perimeter += a == 'P' ? 0 : 3;
    }
    return (perimeter);
}

//is_correct: has a 'T' and every 'T' is surrounded by a 'P'
bool is_correct(const vector<char> &v) {
    auto it = v.begin();
    bool has_t = false;
    bool enclosed = true;
    while (it != v.end() && enclosed) {
	if (*it == 'T' || *it == 'H' || *it == 'A') {
	    enclosed = (it + 1 != v.end()) && (*(it + 1) == 'P');
	    enclosed = enclosed && (it != v.begin()) && (*(it - 1) == 'P');
	}
	if (*it == 'T') {
	    has_t = true;
	}
	it++;
    }
    return (enclosed && has_t);
}

//test a line of the file
void test(const vector<char> &line) throw(string) {
    cout << "Testing line:" << endl;
    display_vector(line);
    cout << "Building a fence from line..." << endl;
    fence_t fence = from_vector(line);
    cout << "Expected size of array: " << line.size() << endl;
    cout << "fence_size gave: " << fence_size(fence) << endl;
    if (line.size() != fence_size(fence)) {
	fence = fence_destroy(fence);
	//horrible!
	throw string("fence_size is wrong!");
    }
    cout << "Checking if fence_to_array returns the same line..." << endl;
    const auto & res = to_vector(fence);
    display_vector(to_vector(fence));
    if (res != line) {
	fence = fence_destroy(fence);
	throw string("fence_to_array is wrong!");
    }
    unsigned int expected_p = get_perimeter(line);
    unsigned int result_p = fence_perimeter(fence);
    cout << "Expected perimeter: " << expected_p << endl;
    cout << "Result perimeter: " << result_p << endl;
    if (expected_p != result_p) {
	fence = fence_destroy(fence);
	throw string("fence_perimeter is wrong!");
    }
    bool expected_c = is_correct(line);
    bool result_c = fence_is_correct(fence);
    cout << "Expected is_correct: " << std::boolalpha <<  expected_c << endl;
    cout << "Result is_correct: " << result_c << endl;
    if (expected_c != result_c) {
	fence = fence_destroy(fence);
	throw string("fence_is_correct is wrong!");
    }
    fence = fence_destroy(fence);
}

int main() {
    int res = 0;
    auto lines = read_file("test.in");
    try {
	for (auto line : lines) {
	    test(line);
	    cout << endl << endl;
	}
    } catch (string msg) {
	cerr << endl << "FAIL: " << msg << endl;
	res = 1;
    }
    if (res == 0) {
	cout << "You WIN! :)" << endl;
    }
    return (res);
}
