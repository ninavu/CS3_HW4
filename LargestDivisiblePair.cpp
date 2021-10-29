#include <iostream>
#include <vector> 
#include <string>
#include <algorithm> 	// for sort()
#include <assert.h>

using namespace std;

/* declare global variables to store the maximum length possible
 * of divisible subsets and 1 subset with that length */
unsigned int max_size = 0;
vector<int> ans;

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

/* a helper function that recursively generates subsets that  
 * satisfy the “divisibility requirement” within a given set */
vector<int> helper_function(vector<int> input, vector<int> subset, int idx){

	for (unsigned int i = idx; i < input.size(); i++){	// initiate a for loop that starts from idx
		
		if (subset.empty() || input.at(i) % subset.back() == 0){	
			subset.push_back(input.at(i));		// push new numbers into the subset if it's empty or is divisible by the last element of the most updated subset
			
			if (max_size < subset.size()){
				max_size = subset.size();		// update max_size if a larger subset's length is found
				ans = subset;					// store that subset temporarily in ans
				//cout << vec_to_string(ans) << endl; 
			}
			//cout << vec_to_string(subset) << endl; 
			
			helper_function(input, subset, i+1);	// call the recursive function to find if the last element of subset divides the next elements from the input
			subset.pop_back();					// remove the last element of the subset if divisiblity not found
		}	
	}
	return ans;
} 

vector<int> largest_divisible_pairs(vector<int> input){
	
	if (!ans.empty()){
		ans.clear();
		max_size = 0;
	}
	
	vector<int> result;
	sort(input.begin(), input.end());	// sort the entire set to examine divisility of the first number only once
	
	if (input.size() == 0){			// base case: return empty list
		return {};
	} else if (input.size() == 1){			// base case: return original vector
		return input;
		
	} else {
		return helper_function(input, result, 0);	// call helper function and get the subset with the largest length	
	}
} 


int main(){
	
	// given test case
	vector<int> ex1 = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> ans1 = largest_divisible_pairs(ex1);
	cout << "Input: " << vec_to_string(ex1) << endl;
	cout << "Answer: " << vec_to_string(ans1) << endl;
	
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
