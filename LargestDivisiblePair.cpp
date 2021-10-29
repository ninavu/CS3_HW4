#include <iostream>
#include <vector> 
#include <string>
#include <algorithm> 	// for sort()
#include <assert.h>

using namespace std;

/* function converts vector into string for debugging purposes */
string vec_to_string(vector<int> v){
	
	if (v.empty()){
		return {};
	}
	
	string str = "[";
	for (unsigned int i = 0; i < v.size()-1; i++){
		str += to_string(v.at(i)) + ", ";
	}
	
	str += to_string(v.at(v.size()-1)) + "]";
	return str;
}


vector<int> largest_divisible_pairs(vector<int> input){
	
	vector<int> result;
	int n = input.size();
	sort(input.begin(), input.end());	// sort the entire set to examine divisility of the first number only once
	
	if (n == 0){			// base case: return empty list
		return {};
	} 
	
	if (n == 1){			// base case: return original vector
		return input;
	} 
	
	vector<int> counter(n,1);		// stores the max size of sublist containing each number, starts with 1 since each number is divisible by itself
	vector<int> prev_idx(n,-1);		// stores the previous idx of the divisible number
	int max_size = 0;		
	int max_idx = -1;				// the idx of the number with the highest counter
	
	for (unsigned int i = 0; i < n; i++){		// make sure every possible options are examined to find the max_size
		for (unsigned int j = i+1; j < n; j++){
			if (input.at(j) % input.at(i) == 0 && counter.at(j) <= counter.at(i)){	// avoid double counts
				counter.at(j) += 1;		// add 1 to the counter of that number if conditions satisfied
				prev_idx.at(j) = i;		// store the idx of the number i divisible by j
			}
		} 
		
		if (counter.at(i) > max_size){		// update max_size and max_idx when a larger length is found
			max_size = counter.at(i);
			max_idx = i;
		}
	}
	
	int cur_max_idx = max_idx;
	while (cur_max_idx != -1){		// go through pre_idx to add numbers into result
		result.push_back(input.at(cur_max_idx));
		cur_max_idx = prev_idx.at(cur_max_idx);
	}
		
	return result;
} 


int main(){
	
	// given test case
	vector<int> ex1 = {28, 22, 7, 2, 8, 14, 24, 56};
	cout << "Input: " << vec_to_string(ex1) << endl;
	cout << "Answer: " << vec_to_string(largest_divisible_pairs(ex1)) << endl;
	
	// random test case
	vector<int> ex2 = {30, 6, 24, 4, 45, 9, 60};
	cout << "Input: " << vec_to_string(ex2) << endl;
	cout << "Answer: " << vec_to_string(largest_divisible_pairs(ex2)) << endl;
	
	// test case with only 1 input
	vector<int> ex3 = {19};
	cout << "Input: " << vec_to_string(ex3) << endl;
	cout << "Answer: " << vec_to_string(largest_divisible_pairs(ex3)) << endl;
	
	// test case with inputs not divisible to each other
	vector<int> ex4 = {19, 10, 21, 75};
	cout << "Input: " << vec_to_string(ex4) << endl;
	cout << "Answer: " << vec_to_string(largest_divisible_pairs(ex4)) << endl;
	
	// test case with no input
	vector<int> ex5 = {};
	cout << "Input: " << vec_to_string(ex5) << endl;
	cout << "Answer: " << vec_to_string(largest_divisible_pairs(ex5)) << endl; 

}

/* Time Complexity of 2 approaches:
 * Recursion (part 1): O(2^n)
 * Dynamic Programming (part 2): O(n^2)
 */
