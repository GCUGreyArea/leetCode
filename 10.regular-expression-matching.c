/*
 * @lc app=leetcode id=10 lang=c
 *
 * [10] Regular Expression Matching
 *
 * https://leetcode.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (27.00%)
 * Likes:    4946
 * Dislikes: 788
 * Total Accepted:    480.2K
 * Total Submissions: 1.8M
 * Testcase Example:  '"aa"\n"a"'
 *
 * Given an input string (s) and a pattern (p), implement regular expression
 * matching with support for '.' and '*' where: 
 * 
 * 
 * '.' Matches any single character.​​​​
 * '*' Matches zero or more of the preceding element.
 * 
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aa", p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aa", p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the preceding element, 'a'.
 * Therefore, by repeating 'a' once, it becomes "aa".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "ab", p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: s = "aab", p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore,
 * it matches "aab".
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: s = "mississippi", p = "mis*is*p*."
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= s.length <= 20
 * 0 <= p.length <= 30
 * s contains only lowercase English letters.
 * p contains only lowercase English letters, '.', and '*'.
 * It is guaranteed for each appearance of the character '*', there will be a
 * previous valid character to match.
 * 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// @lc code=start
typedef enum {
	SEARCH_WILD_CARD_NEXT,
	SEARCH_WILD_CARD,
	SEARCH_WILD_CARD_MATCH,
	SEARCH_CHAR,
	SEARCH_END_SEARCH_STRING,
	SEARCH_NONE
} sstate_t;

static inline const char * printState(sstate_t s) {
	switch(s) {
		case SEARCH_WILD_CARD_NEXT: 	return "SEARCH_WILD_CARD_NEXT"; 
		case SEARCH_WILD_CARD: 			return "SEARCH_WILD_CARD";
		case SEARCH_WILD_CARD_MATCH:	return "SEARCH_WILD_CARD_MATCH";
		case SEARCH_CHAR: 				return "SEARCH_CHAR";
		case SEARCH_END_SEARCH_STRING:	return "SEARCH_END_SEARCH_STRING";
		case SEARCH_NONE: 				return "SEARCH_NONE";
		default:
			break;
	}

	return "UNKNOWN";
}

sstate_t shiftState(char sc, char pc, char nc) {
	if(sc == '\0') {
		return SEARCH_END_SEARCH_STRING;
	}
	
	if(pc == '*') {
		if(sc == nc) {
			return SEARCH_CHAR;
		}
		return SEARCH_WILD_CARD;
	}
	
	if(pc == '.') {
		return SEARCH_WILD_CARD_NEXT;
	}
	
	if(nc == '*') {
		return SEARCH_WILD_CARD_NEXT;
	}
	
	if(sc == pc) {
		return SEARCH_CHAR;
	}

	return SEARCH_NONE;
}

// s = string
// p = search pattern
bool isMatch(char * s, char * p) {
	// first make sure that p and s are valid
	if(p == NULL || s == NULL) {
		return false;
	}

	printf("Mattching [str %s / pattern %s]\n", s, p);

	// Get the length of both 
	int plen = strlen(p);
	int slen = strlen(s);

	// Indicies into string and pattern
	int sidx=0;
	int pidx=0;


	// we have to match character for character in s for p untill we hit a '.' or a '*' 
	bool match=false;
	sstate_t state=SEARCH_NONE;
	int charCount=0;
	char nc = '\0';

	// first match char for char
	while(s[sidx] != '\0' && p[pidx] != '\0')  {
		char sc = s[sidx];
		char pc = p[pidx];

		if(pidx < plen) {
			nc = p[pidx+1];
		}

		state = shiftState(sc, pc, nc);

		printf("State %d [string '%c' / pattern '%c' / nc '%c' / state %s]\n", ++charCount, sc,pc,nc,printState(state));

		// Each iteration we have to move the state machine to the next state 
		switch(state) {
			case SEARCH_WILD_CARD: // current index in p is '*'
				sidx++;
				break;
			case SEARCH_WILD_CARD_MATCH:
				pidx++;
				sidx++;
				break;
			case SEARCH_WILD_CARD_NEXT:
				pidx++;
				sidx++;
				break;
			case SEARCH_CHAR:	   // current index in p is a char
				pidx++;
				sidx++;
				break;
			case SEARCH_END_SEARCH_STRING:
				pidx++;
				break;
			default:
				printf("false 2\n");
				printState(state);
				return false;
		}
	} 

	if(s[sidx] == '\0' && nc != '\0') {
		return false;
	} 
	else if(s[sidx] != '\0' && nc != '*') {
		return false;
	}

	
	printState(state);

	return true;
}

// Run test cases
void main() {
	
}

// @lc code=end

