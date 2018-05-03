#include<iostream>
using namespace std;

typedef int Status;

int main() {

}

struct queue {


};

Status queue_in(queue *q, char *word, int word_len) {

}

bool word_changable(char *word1, int word1_len, char *word2, int word2_len) {
	if (word1_len != word2_len) {
		return false;
	}
	else {
		bool only_one_differ_flag = false;
		for (int i = 0; i < word1_len; ++i) {
			if (word1[i] != word2[i]) {
				if (only_one_differ_flag) { //more than one different letter
					return false;
				}
				only_one_differ_flag = true;
			}
		}
		return only_one_differ_flag;
	}
	return false;
}

bool op_change_queue(char *start, int start_len, queue *q, char *dict[], int words_len[], int dict_len, bool dict_added_flag[]) {

	bool changable_flag = false;
	for (int i = 0; i < dict_len; ++i) {
		if (word_changable(start, start_len, dict[i], words_len[i])
			&& !dict_added_flag[i]) {
			queue_in(q, dict[i], words_len[i]);
			changable_flag = dict_added_flag[i] = true;
		}
	}
	return changable_flag;

}