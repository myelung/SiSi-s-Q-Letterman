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

bool word_swappable(char *word1, int word1_len, char *word2, int word2_len){

	if (word1_len != word2_len){
		return false;
	}
	else{
		for (int i=0;i<word1_len;++i){
			if (word1[i] != word2[i]){
				break;
			}
		}
		if (i == word1_len - 1 || i == word1_len){
			return false;
		}
		else{
			if (word1[i] != word2[i+1] || word1[i+1] != word2[i]){
				return false;
			}
			for (j=i+2;j<word2_len;++j){
				if (word1[j] != word2[j]){
					return false;
				}
			}
		}
	}
	return true;

}

bool word_insertable(char *word1, int word1_len, char *word2, int word2_len){

	char *word_short, *word_long;
	int word_short_len;

	switch(word2_len - word1_len){
		case -1:{
			word_short = word2;
			word_long = word1;
			word_short_len = word2_len;
			break;
		}
		case 1:{
			word_short = word1;
			word_long = word2;
			word_short_len = word1_len;
			break;
		}
		default:{
			return false;
		}
	}

	for (int i=0;i<word_short_len;++i){
		if (word_short[i] != word_long[i]){
			break;
		}
	}
	for (int j=i;j<word_short_len;++j){
		if (word_short[j] != word_long[j+1]){
			return false;
		}
	}
	return true;

}

bool word_deletable(char *word1, int word1_len, char *word2, int word2_len){
	return word_insertable(word2,word2_len,word1,word1_len);
}

void read_complex_input_file(vector<DictEntry> &dictionary){
    size_t number;
    cin >> number;
    string newline;
    dictionary.resize(3 * number);//有问题
    int dictCount = 0;
    while(getline(cin,newline)){
        if(newline[0]!='/'){ // input is not a comment
            bool newline_is_complex = false;
            for(int i = 0; i < newline.size();++i){
                if (newline[i] =='['){
                    for (int j = i+1; j < newline.size(); ++j){
                        if(newline[j]== ']'){
                            newline_is_complex = true;
                            if(j != newline.size()-1){
                                for(int k = i+1; k <j; ++k){
                                    dictionary[dictCount].word=newline.substr(0,i)+ newline[k] + newline.substr(j+1);
                                    dictCount += 1;
                                }
                            }else{
                                for(int k = i+1; k < j; ++k){
                                    dictionary[dictCount].word=newline.substr(0,i)+ newline[k];
                                    dictCount += 1;
                                }
                            }
                        }
                    }
                    break;
                }//when []
                else if(newline[i]=='&'){
                    newline_is_complex = true;
                    dictionary[dictCount].word = newline.substr(0,newline.size()-1);
                    dictCount += 1;
                    for(int l = i-1; l > -1; --l ){
                        dictionary[dictCount].word += newline[l];
                    }
                    dictCount += 1;
                    break;
                }//when &
                else if(newline[i] == '!'){
                    newline_is_complex = true;
                    if(i!=newline.size()-1){
                        dictionary[dictCount].word = newline.substr(0,i) + newline.substr(i+1);
                        dictCount += 1;
                        dictionary[dictCount].word = newline.substr(0,i-2) + newline[i-1] + newline[i-2] + newline.substr(i+1);
                        dictCount += 1;
                    }else{
                        dictionary[dictCount].word = newline.substr(0,i);
                        dictCount += 1;
                        dictionary[dictCount].word = newline.substr(0,i-2) + newline[i-1] + newline[i-2];
                        dictCount += 1;
                    }
                    break;
                }//when !
                else if(newline[i] == '?'){
                    newline_is_complex = true;
                    dictionary[dictCount].word = newline.erase(i,1);
                    dictCount += 1;
                    dictionary[dictCount].word = newline.insert(i,1,newline[i-1]);
                    dictCount += 1;
                    break;
                }
            }//traverse every "newline"
            if(!newline_is_complex){
                dictionary[dictCount].word = newline;
            }
        }//not comment
    }
    
}
