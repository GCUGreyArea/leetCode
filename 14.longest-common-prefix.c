/*
 * @lc app=leetcode id=14 lang=c
 *
 * [14] Longest Common Prefix
 */

// @lc code=start

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char * longestCommonPrefix(char ** strs, int strsSize) {
    // We need to probe all strings for common prefix
    // Until it failes starting at 0. The resulting number
    // Will be the longest common substring

    if(strs[0] == NULL && strsSize == 0) return NULL;

    int len = 0;    // Length of common prefixs
    int probeLen=1; // Length to probe
    int longest=0;  // Longest string length
    int shortest=strlen(strs[0]);
    int shortIdx=0;

    // Firstly get the length of the longest string.
    // This is the break case
    for(int i=0;i<strsSize;i++) {
        int len = strlen(strs[i]);
        if(len > longest) longest=len;
    }

    for(int i=0;i<strsSize;i++) {
        int len = strlen(strs[i]);
        if(len < shortest) {
            shortest=len;
            shortIdx=i;
        }
    }

    char * str = strs[shortIdx];
    bool match = true;
    for(int i=0;i<strsSize;i++) {
        for(int j=0;j<probeLen;j++) {
            if(str[j] != strs[i][j]) {
                match=false;
                break;
            }


        }
    }
}
// @lc code=end

