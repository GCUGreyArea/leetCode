/*
 * @lc app=leetcode id=19 lang=c
 *
 * [19] Remove Nth Node From End of List
 * Submition: https://leetcode.com/submissions/detail/549779721/
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *index;
 * };
 */


 #include <stdio.h>
 #include <stdlib.h>

/**
 * Nth nnode starting from 0
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    if(head == NULL) return NULL;

    struct ListNode* localhead = head;

    struct ListNode* index = head;
    struct ListNode* last = head;

    // Get the length of the list
    int len=0;
    while(index) {
        len++;
        index = index->next;
    }

    // There's only one element
    if(len == 1 && n == 1) return NULL;

    // Reset next;
    index=localhead;

    // Get the place in the list we want to prune
    int place = len-n;

    // If it's the first place the solution is to move the head of teh list up
    if(place == 0) {
        localhead = localhead->next;
    }
    else {
        for(int i=0;i<place;i++) {
            last = index;
            index = index->next;
        }

        // Last should now point to the list item before the one we want
        // And index should be the one we want
        if(last && index) {
            last->next = index->next;
        }
    }

    // Return our copy of the head of the list
    return localhead;

}
// @lc code=end

