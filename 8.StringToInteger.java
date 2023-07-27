/*
 * @lc app=leetcode id=8 lang=java
 * [8] String to Integer (atoi)
 * Submition: https://leetcode.com/submissions/detail/549823056/
 */

import java.util.Arrays;

// @lc code=start
class Solution
{
    private final int INT_MAX = 2147483647;
    private final int INT_MIN = -2147483648;

    int num_from_char(char n) {
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

    int count_numeric(char [] s) {
        int i=0;
        for(char c : s) {
            if(num_from_char(c) != -1) i++;
        }

        return i;
    }

    int last_numeric(char [] s) {
        int i=0;
        for(char c : s) {
            if(num_from_char(c) == -1) return i;
            i++;
        }

        return i;
    }

    int myAtoi(String s) {
        Boolean neg  = false;

        int len = s.length();
        if(len == 0) return 0;

        char [] arr = s.toCharArray();
        int i=0;


        // Find all whitespace
        int whiteSpace=0;
        for(char c : arr) {
            // Break at a number or a positive or negative sign
            if(num_from_char(c) != -1 || c == '-' || c == '+') break;

            if(Character.isWhitespace(c)) {whiteSpace++;}
            else if(Character.isAlphabetic(c)) {return 0;}
        }

        // And remvoe if it exists
        if(whiteSpace > 0) {
            if(whiteSpace == arr.length) return 0;
            arr = Arrays.copyOfRange(arr, whiteSpace, arr.length);
        }

        if(arr[0] == '+') {
            // pos=true;
            arr = Arrays.copyOfRange(arr, 1, arr.length);
        }
        else if(arr[0] == '-') {
            neg=true;
            arr = Arrays.copyOfRange(arr, 1, arr.length);
        }

        int count = last_numeric(arr);
        if(count != arr.length) {
            arr = Arrays.copyOfRange(arr, 0, count);
        }

        // We should now be at the start of valid numbers
        int numlen = count_numeric(arr);
        if(numlen != arr.length) return 0;

        if(numlen == 1) {
            int v = num_from_char(arr[0]);
            if(v == -1) return 0;
            if(neg) {
                return v * -1;
            }

            return v;
        }

        double raise = 1;
        double ret = 0;

        for(i=numlen-1;i>=0;i--) {
            double v = num_from_char(arr[i]);
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
}
// @lc code=end