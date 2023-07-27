/*
 * @lc app=leetcode id=127 lang=c
 *
 * [127] Word Ladder
 */

// @lc code=start
// int diff(char * word1, char * word2);
typedef struct {
	char ** words;	// stack of words
	int * widx;		// stack of index into word list for each word in stack - to replace in dictionary
	int place;		// Current place in the stack
	int size;		// Maximum size of the stack
} wordStck_t;

static void print_stack(wordStck_t * stack) {
	printf("Elements: %d [ ", stack->place);
	for(int i=0;i<stack->place;i++) {
		if(stack->words[i]) printf("%s ", stack->words[i]);
	}

	printf("]\n");
}

static int diff(char * word1, char * word2) {
	int i=0;
	int degree=0;
	while(word1[i] != '\0') {
		if(word1[i] != word2[i]) {
			degree++;
		}
		i++;
	}

	return degree;
}

static int word_in_list(char * word, char ** words, int wordLen) {
    for(int i=0;i<wordLen;i++) {
		if(words[i] == NULL) continue;
        if(strcmp(word,words[i]) == 0) {
            return i;
        }
    }

    return -1;
}

static void print_wordlist(char ** words,int size) {
	printf("[");
	for(int i=0;i<size;i++) {
		printf(" %s", words[i]);
	}

	printf(" ]\n");
}

static wordStck_t * setup_stack(int size) {
	wordStck_t * stack = malloc(sizeof(wordStck_t));
	if(stack) {
		// setup the stack 
		stack->words = (char**) malloc(sizeof(char*) * size);
		if(stack->words == NULL) {
			free(stack);
			return NULL;
		}

		// Stack of indices
		stack->widx = (int*) malloc(sizeof(int) * size);
		if(stack->widx == NULL) {
			free(stack->words);
			free(stack);
			return NULL;
		}

		stack->place = 0;
		stack->size  = size;
	}

	return stack;

}

static void kill_stack(wordStck_t * stack) {
	if(stack) {
		free(stack->words);
		free(stack->widx);
		free(stack);
	}
}

static int push_to_stack(wordStck_t * stack, char * word, int pos) {
	int ret = -1;
	if(stack && stack->place < stack->size) {
		stack->words[stack->place] = word;
		stack->widx[stack->place]  = pos;
		stack->place++;

		ret = stack->place;
	}

	return ret;
}

static int pop_from_stack(wordStck_t * stack,char ** word) {
	int ret = -1;

	if(stack && word && stack->place > 1) {
		stack->place--;
		*word = stack->words[stack->place];
		ret   = stack->widx[stack->place]; 
	}

	return ret;
}

static int get_stack_items(wordStck_t * stack) {
	int ret = -1;
	if(stack) {
		ret = stack->place; 
	}

	return ret;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize) {
	// int degree = diff(beginWord, endWord);
	int wordLen = strlen(beginWord);
	if(wordLen == 1 && wordListSize >= 1) {
		return 2;
	}
	
	printf("Testing [begin %s / end %s]\n", beginWord, endWord);

	// For large dictionaries this would work better as a tree or a hash table
	// init_dictionary(wordList, wordListSize);
	int endIdx = word_in_list(endWord,wordList,wordListSize);
	if(endIdx == -1) {
		printf("Target word not found\n");
		return 0;
	}

	int endDiff = diff(beginWord,endWord); 
	if(endDiff == 1) {
		return 2;
	}

	wordStck_t * stack = setup_stack(wordListSize);
	if(stack == NULL) {
		return -1;
	}

	int beginIdx = word_in_list(beginWord,wordList,wordListSize);

	bool path=false;
	char * current = beginWord;
	
	// Get the index of start word if it exists
	int foundIdx = word_in_list(current,wordList,wordListSize);
	int nextIdx = -1;
		
	// Print out starting state
	print_stack(stack);	
	print_wordlist(wordList, wordListSize);

	int iteration=0;
	int deapth=0;
	int paths=0;
	bool backtrack=false;
	int dcur = wordLen; 
	int ecur = wordLen;
	int ret=0;
	// int sub=1;
	int start=0;
	char ** backList = (char**) malloc(sizeof(char*) * wordListSize);
	int lastBack=0;

	printf("Start...\n");

	do 
	{
		char * next = NULL;
		// int ediff = wordLen;
		printf("Start [Iteration %d / current %s]\n", ++iteration, current);

		// Find the first word with a difference of one between it and the current word  
		for(int i=start;i<wordListSize;i++) {
			// ediff = diff(wordList[i], endWord);
			dcur = diff(wordList[i],current);
			if(wordList[i][0] != '-' && dcur == 1) {
				next=wordList[i];
				nextIdx=i;
				break;
			}
		}

		printf("Next state [dcur %d / current %s / next %s]\n", dcur, current, next);

		if(next == NULL) {
			backtrack=true;
		}
		else if(dcur == 1)  {
			push_to_stack(stack,current,foundIdx);

			// Eliminate it from the search to avoid loops
			wordList[foundIdx] = "-";

			// Reset current to next matched
			current=next;
			foundIdx=nextIdx;

			// If the next word is the end word and the degree of difference is one
			// we have found a path
			if(diff(current,endWord) == 0) {
				deapth = stack->place+1;
				paths++;
				backtrack=true;
				printf("Found path ");
				print_stack(stack);
				print_wordlist(wordList,wordListSize);

				// If the number of transformations is equal to the difference
				// between the start and end word, it's has to be the shortest path.  
				if(stack->place == endDiff) {
					break;
				}
			}
		}
		
		if(backtrack && next == NULL && (stack->place == 0 || stack->place == 1)) {
			// Backtracked asa far as it will go
			break;
		}

		while(backtrack) {
			if(stack->place > 0) {
				char * word = NULL;
				int next;
				int idx = pop_from_stack(stack,&word);
				if(idx == -1) {
					// No more stack
					break;
				}
				if(word_in_list(word,backList,wordListSize) == -1) { 
					printf("Backtrack: [word %s / start %d]\n", word, idx);
					print_stack(stack);
					current=word;
					foundIdx=idx;
					start = idx+1;
					backtrack=false;
					wordList[idx] = word;
					backList[lastBack++] = word;
					break;
				}
			}
			else {
				path=true;
				break;
			}
		}


		printf("End of loop state\n");
		print_stack(stack);
		print_wordlist(wordList,wordListSize);
	} while(!path);

	printf("EXIT FROM LOOP: Paths %d - ", paths);
	print_stack(stack);
	kill_stack(stack);
	printf("Path from %s to %s is %d\n", beginWord, endWord, deapth);
	return deapth;
}

// @lc code=end

