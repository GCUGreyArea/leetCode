/*
 * @lc app=leetcode id=1 lang=c
 *
 * [1] Two Sum
 */

// @lc code=start

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

// Typically this will be O(n2)
int * twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for(int i=0;i<numsSize;i++) {
        for(int j=0;j<numsSize;j++) {
            if(i != j && nums[i] + nums[j] == target) {
                int * retVal = malloc(sizeof(int) * 2);
                if(retVal == NULL) {
                    fprintf(stderr,"Memeory allocation failure\n");
                    abort();
                }

                retVal[0] = i;
                retVal[1] = j;
                *returnSize = 2;

                return retVal;
            }
        }
    }

    *returnSize = 0;
    return NULL;
}


// @lc code=end

void main() {
    int ret = 0;
    int ar[] = {3,2,4};
    int val = twoSum(ar, 3, 6, &ret);
}
