/*
 * @lc app=leetcode id=8 lang=c
 *
 * [8] String to Integer (atoi)
 * Submition: https://leetcode.com/submissions/detail/549791930/
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// @lc code=start
#ifndef INT_MAX
#define INT_MAX 2147483648
#endif

#ifndef INT_MIN
#define INT_MIN -2147483648
#endif

inline static int num_from_char(char n) {
    switch(n) {
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

inline static int count_numeric(char * s) {
	int i=0;
	while(s[i] != '\0' && num_from_char(s[i]) != -1) {
		i++;
	}

	return i;
}

int myAtoi(char * s) {
    bool neg  = false;
	bool zero = false;
	bool pos  = false;
	bool spa  = false;
    bool pnt  = false;

	if(strlen(s) == 0) return 0;

	int i=0;
	while(s[i] != '\0') {
		if(isalpha(s[i])) {
			return 0;
		}

		if(num_from_char(s[i]) != -1) {
			s = &s[i];
			break;
		}

		// Test negative sign and move forward
		if(s[i] == '-' ) {
			if(neg || pos || zero) return 0;
			if(s[i+1] != '\0' && num_from_char(s[i+1]) == -1) return 0;

			neg = true;
		}

		if(s[i] == '+') {
			if(pos || neg || zero) return 0;
			if(s[i+1] != '\0' && num_from_char(s[i+1]) == -1) return 0;

            pos = true;
		}

		if(s[i] == '0') {
			zero = true;
		}

		if(s[i] == '.') {
			if(num_from_char(s[i+1]) != -1) {
				return 0;
			}
		}

		if(s[i] == ' ') {
			if(pos || zero) return 0;
		}

		i++;
	}

    // We should now be at the start of valid numbers
	int len = count_numeric(s);
	if(len == 1) {
		int v = num_from_char(s[0]);
		if(v == -1) return 0;
		if(neg) {
			return v * -1;
		}

		return v;
	}

	double raise = 1;
    double ret = 0;

    for(int i=len-1;i>=0;i--) {
        double v = num_from_char(s[i]);
        if(v == -1) {
            return 0;
        }

        if(ret + (v * raise) > (double) INT_MAX) {
            if(neg) return INT_MIN;
            return INT_MAX;
        }

        ret += (v * raise);
        raise = raise * 10;
    }

    if(neg) {
        ret = ret * -1;
    }

    return (int) ret;
}

// @lc code=end

