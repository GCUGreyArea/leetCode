/*
 * @lc app=leetcode id=2 lang=c
 *
 * [2] Add Two Numbers
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// Asume base 10
static int digits(long int num) {
	int dg = 0;
	while(num) {
		num = num / 10;
		dg++;
	}

	return dg;
}

static long long int to_power_of(long long int num, int exp) {
	long long int ret = 1;
	
	if(exp) {
		ret = num;
		if(num) {
			for(int i=0;i<exp-1;i++) {
				ret *= num;
			}
		}
	}

	return ret;
}

static int get_list_length(struct ListNode*l) {
    int len=0;

    while(l) {
		len++;
		l = l->next;
    }

	return len;
}


static int get_nth_value(struct ListNode*l, int nth) 
{
	int len = get_list_length(l);
	if(nth > len) {
		return 0;
	}

	struct ListNode*n=l;
	while(nth-1) {
		n=n->next;
		nth--;
	}

	return n->val;
}	

static struct ListNode* make_list_node() {
	struct ListNode* n = malloc(sizeof(struct ListNode));
	if(n) {
		n->val = 0;
		n->next = NULL;
	}

	return n;
} 

static struct ListNode* last_node(struct ListNode*l) {
	while(l) {
		if(l->next == NULL) {
			return l;
		}

		l = l->next;
	}

	return l;
}


static struct ListNode* make_into_list(long int val) {
	struct ListNode* ret = NULL;
	if(val) {
		struct ListNode* n = make_list_node();
		int dg = digits(val);

		for(int i=dg;i>0;i--) {
			long long int pow = to_power_of(10,i-1);
			long int v = val / pow;

			// This will be the last node
			n->val = v;
			// n->next = NULL;

			// This is the next value
			val = val - (v * pow);
			
			if(i > 1) {
				// Make the new first node 
				struct ListNode* first = make_list_node();
				if(first) {
					first->next = n;
					n = first;
				}
			}
			else {
				ret = n;
			}
		}
	}
    else {
       struct ListNode* n = make_list_node();
       n->val = val;
       n->next = NULL;
       ret = n; 
    }

	return ret;
}

static struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
{
	int len1 = get_list_length(l1);
	int len2 = get_list_length(l2);

	// l1 = [1 2 3]
	// l2 =     [9]
	// l3 = [1 3 2]
	int nth = 0;
	if(len1 == len2) {
		nth = len1;
	}
	else if(len1 > len2) {
		nth = len1;
	}
	else {
		nth = len2;
	}

	int r = 0;
	int q = 0;

	int place = 1;

	struct ListNode* head = NULL;
	struct ListNode* tail = NULL;
	struct ListNode* ret  = NULL;

	while(place <= nth) {
		tail = make_list_node();
		int v1 = get_nth_value(l1,place);
		int v2 = get_nth_value(l2,place);

		int v = v1 + v2 + q;
		if(v >= 10) {
			q = v / 10;
			r = v % 10;

			tail->val = r;
		}
		else {
			tail->val = v;
			q = 0;
		}

		if(head) {
			// Make tail the new head so we always ad to tail
			head->next = tail;
			head = tail;
		}
		else {
			// Set up the reture value as the true head of the list
			head = tail;
			ret  = head;
		}

		place++;
	}

	if(q) {
		tail = make_list_node();
		tail->val = q;
		// printf("%d ", q);
		head->next = tail;
	}

	return ret;
}
// @lc code=end

