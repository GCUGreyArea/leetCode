/*
 * @lc app=leetcode id=17 lang=c
 *
 * [17] Letter Combinations of a Phone Number
 *
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (47.68%)
 * Likes:    4626
 * Dislikes: 452
 * Total Accepted:    684.7K
 * Total Submissions: 1.4M
 * Testcase Example:  '"23"'
 *
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer in
 * any order.
 * 
 * A mapping of digit to letters (just like on the telephone buttons) is given
 * below. Note that 1 does not map to any letters.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: digits = ""
 * Output: []
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: digits = "2"
 * Output: ["a","b","c"]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= digits.length <= 4
 * digits[i] is a digit in the range ['2', '9'].
 * 
 * 
 */

// @lc code=start


// Database of all letter combinations
// These have to be the same length to satisfy the permutation algorithm
// Because of this we will need to exclude permutations that are no all alpha strings
static const char * numberStrs[] = {"----", "----", "abc-","def-","ghi-","jkl-","mno-","pqrs","tuv-","wxyz"};

// We need the actual number of characters to calculate the number of strings to generate
static const int lengths[]       = {0,       0,     3,     3,     3,     3,     3,     4,     3,     4};
static const int bound = 4; 

// Debug to print out the database..
static inline void printDatabase() {
	printf("[");
	for(int i=0;i<10;i++) {
		printf("[");
		for(int j=0;j<lengths[i];j++) {
			printf("%c", numberStrs[i][j]);
		}
		printf("]");
	}
	printf("]\n");
}

static inline void printArrays(char ** ars, int len) {
	printf("[");
	for(int i=0;i<len;i++) {
		printf("[%s]", ars[i]);
	}
	printf("]\n");
}


static inline void freeArrays(char ** ars, int len) {
	for(int i=0;i<len;i++) {
		free(ars[i]);
	}

	free(ars);
}

// Convert a decimal character into an integer or return -1
static inline int ctoi(char c) {
	switch(c) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default:
			break;
	}

	return -1;
}

// Convert a character array of digits into an integer array.
// If any character in the string is not a decimal digit the program will abort with a message
int * makeIntArray(char * digits, int * len) {
	int l = strlen(digits);

	int * nums = (int*) malloc(sizeof(int) * l);
	if(nums == NULL) {
		printf("Memory allocation failure\n");
		abort();
	}

	for(int i=0;i<l;i++) {
		int val = ctoi(digits[i]);
		if(val == -1) {
			printf("Wrong number [%c]\n", digits[i]);
			abort();
		}
		nums[i] = val; 
	}

	*len = l;

	return nums;
}


static inline char * copyCharArray(char * str, int len) {
	char * nstr = (char*) malloc(sizeof(char) * len+1);
	if(nstr == NULL) {
		printf("Memory allocation failure\n");
		abort();
	}

	for(int i=0;i<len;i++) {
		nstr[i] = str[i];
	}

	// Null terminate for printing
	nstr[len] = '\0';


	return nstr;
}

void printIntArry(int * ar, int len) {
	printf("[");
	for(int i=0;i<len;i++) {
		printf("%d", ar[i]);
	}
	printf("]\n");
}


// Generate a number string based on an array of indicies into the character database
// Permutations will be generated in separate arrays in order to generate all perutations of 
// letter combinations representing the numbers.
int generateNumberString(int * idxs, int * nums, int len, char * str) {
	int count=0;
	for(int i=0;i<len;i++) {
		if(idxs[i] < lengths[nums[i]]) {
			str[i] = numberStrs[nums[i]][idxs[i]];
			count++;
		}
	}


	return count;
}

bool rotateArray(int * idx,int len, int bound) {
	bool rotate=true;
	int i=0;
	while(rotate) {
		// Increment
		idx[i]++;

		// test bounds at the same time 
		if(idx[i] == bound) {
			idx[i] = 0;
			i++;
		}
		else {
			rotate=false;
		}

		if(i==len) {
			return true;
		}
	}

	return false;
}


// As per leetCode the returned array must be malloced, 
// we assume caller calls free().
char ** letterCombinations(char * digits, int* returnSize) {
	int len=0;
	int * nums = makeIntArray(digits, &len);

	if(len == 0) {
		*returnSize = 0;
		return NULL;
	}

	// The number of possible letter combinations is n1 * n2 * ni where n = number of chars and i = nth digit
	// which gives us the maximum number of arrays
	int arrays=0;
	for(int i=0;i<len;i++) {
		if(arrays) {
			arrays = arrays * lengths[nums[i]];
		}
		else {
			arrays = lengths[nums[i]];
		}
	}

	printf("Arrays needed [ar %d]\n", arrays);

	char ** retArray = malloc(sizeof(char*) * arrays);
	if(retArray == NULL) {
		printf("Memory allocation failure\n");
		abort();
	}

	int * idx = malloc(sizeof(int) * len);
	if(idx == NULL) {
		printf("Memory allocation failure\n");
		abort();
	}

	// To get all permutations of the letter substitutions we need to get 
	// all permutations of the indices into the substitution database

	// This can be calculated by rotating through all possible states
	// If we imagine the the values as arrays being rotated  
	// [0,1,2,3] -> [3,0,1,2] -> [2,3,0,1] -> [1,2,3,0] -> [0,1,2,3] 
	// where a full rations returns to 0

	// Such that 
	// 1. Index 0 is rotated first 
	// 2. Each time index n rotates back to 0
	//    array n+1 rotates 1 place
	// 3. The algorithm is finished when the last value rotates back to 0
 
	// When all permutations for all indices have been found
	// All permutations for letters / number substitution has been found

	for(int i=0;i<len;i++) {
		idx[i] = 0;	// Start all indices at 0
	}

	bool stop=false;  // The algorithm has finished
	int arIdx=0;      // The index into the return array
	char * ar = NULL; // The next value to add to return

	while(!stop) {
		if(ar==NULL) {
			ar = malloc(sizeof(char) * (len+1));
			if(ar == NULL) {
				printf("Memory allocation failure\n");
				abort();
			} 
		}

		// Generate a string of letters from the index array to add to the return value
		int gen = generateNumberString(idx,nums,len,ar);

		// To make things easier all bounds are normailsed to the same value
		// and additional 'non legal' character data added to the end of the 
		// character database for each number where needed
		if(gen == len) {
			// Null terminate for printing and add to return
			ar[len] = '\0'; 
			retArray[arIdx] = ar;	

			arIdx++;
			ar=NULL;
		}

		// The index array is then rotated as described above to generate the next sequence
		stop = rotateArray(idx,len, bound);
	}
	
	if(ar) {
		// If we allocated and it didn't get used free it
		free(ar);
	}

	// Free working values
	free(idx);
	free(nums);

	*returnSize = arrays;
	return retArray;
}

// @lc code=end

