#include <iostream>
#include <vector> 
#include <string>
#include <algorithm> 
#include <assert.h>

using namespace std;

int max_size = 0;
vector<int> ans;

string vec_to_string(vector<int> v){
	
	string str = "[";
	for (unsigned int i = 0; i < v.size()-1; i++){
		str += to_string(v.at(i)) + ", ";
	}
	
	str += to_string(v.at(v.size()-1)) + "]";
	return str;
}

vector<int> helper_function(vector<int> input, vector<int> subset, int idx){
	
	for (int i = idx; i < input.size(); i++){
		if (subset.empty() || input.at(i) % subset.back() == 0){
			subset.push_back(input.at(i));
			if (max_size < subset.size()){
				max_size = subset.size();
				ans = subset;
			}
			//cout << vec_to_string(subset) << endl; //comment out later
			helper_function(input, subset, i+1);
			subset.pop_back();
		}	
	}
	return ans;
} 

vector<int> largest_divisible_pairs(vector<int> input){
	
	sort(input.begin(), input.end());
	vector<int> result;
	
	if (input.size() <= 1){			// base case
		return input;
		
	} else {
		result = helper_function(input, result, 0);
		return result; 			
	}
} 


int main(){
	// work with any list that (a) contains only positive numbers and (b) does not contain any duplicate numbers
	vector<int> ex = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> result = largest_divisible_pairs(ex);
	cout << "Answer: " << vec_to_string(result) << endl;
	
}
