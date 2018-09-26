我是先BFS建一个graph…

然后返回这个graph，所有从首到尾的path
一个单词可能指向不同的节点，所以通常的memo不太行
@则博 一个单词可能指向不同的节点，所以通常的memo不太行 。嗯，所有bfs的时候除了记录neighbors，也记录这个word的距离，然后在dfs的时候根据curr的距离+1 = 记录的word的距离就可以判断是否下一个word

from string import ascii_lowercase

class Solution(object):
    def findLadders(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        wordset = set(wordList)
        if endWord not in wordset:
            return []
        new_words_level = []
        orgn_dis = self.distance(endWord,beginWord)
        new_words_level.append((beginWord,[beginWord],orgn_dis))
        output = []
        
        while len(new_words_level)>0:
            #print("new_words_level",new_words_level)
            cur_words_level = new_words_level
            new_words_level = []
            reach_end_word = False
            for cur in cur_words_level:
                word = cur[0]
                path = cur[1]
                path_set = set(cur[1])
                origin_dis = cur[2]
                for i in range(len(word)):
                    for a in ascii_lowercase:
                        new_word = word[:i] + a + word[i+1:]
                        if new_word !=word and new_word in wordset and new_word not in path_set:
                            new_dis = self.distance(endWord,new_word)
                            if new_dis <=origin_dis:
                                new_path = path[:]
                                new_path.append(new_word)
                                if new_word == endWord:
                                    reach_end_word = True
                                    #print("reach endWord!",new_path)
                                    output.append(new_path)
                                else:
                                    new_words_level.append((new_word,new_path,new_dis))
            if reach_end_word:
                break
        return output
    
    def distance(self,target,cur):
        dis = 0 
        for i in range(len(target)):
            if target[i]!=cur[i]:
                dis+=1
        return dis
        
        
 
 vector<string> findNeighbours(const string& word, const unordered_set<string>& dict) {
        vector<string> neighbours;
        for (int i = 0; i != word.length(); ++i) {
            for (char c = 'a'; c <= 'z'; ++c) {
                string new_word = word ;
                new_word[i] = c;
                if (dict.find(new_word) == dict.end() || word[i] == c) continue;
                neighbours.push_back(new_word);
            }
        }
        return neighbours;
    }
      
    void bfs (  const string& start, 
                const string& end, 
                const unordered_set<string> &dict, 
                unordered_map<string, int>& distance, 
                unordered_map<string, vector<string>>& memo) {
        queue<string> q;
        q.push(start);
        distance[start] = 0;
        while (!q.empty()) {
            int length = q.size();
            for (int i = 0; i != length; ++i) {
                string word = q.front(); q.pop();
                if (word == end) break;
                vector<string> neighbours = findNeighbours(word, dict);
                if (memo.find(word) == memo.end()) memo[word] = neighbours;
                for (auto& neighbour : neighbours) {
                    if (distance.find(neighbour) != distance.end()) continue;
                    distance[neighbour] = distance[word] + 1;
                    q.push(neighbour);
                }
            }
        }
    }
    
    void dfs (  vector<vector<string>>& result,
                vector<string>& path,
                string& current,
                string& end,
                unordered_map<string, int>& distance,
                unordered_map<string, vector<string>>& memo) {
        if (current == end) {
            result.push_back(path);
            return;
        }
        for (auto neighbour : memo[current]) {
            if ( distance[neighbour] != distance[current] + 1) continue;// 保证path达到
            path.push_back(neighbour);
            dfs(result, path, neighbour, end, distance, memo);
            path.pop_back();
        }
    }

    vector<vector<string>> findLadders(string &start, string &end, unordered_set<string> &dict) {
        unordered_map<string, vector<string>> memo;
        unordered_map<string, int> distance;
        vector<vector<string>> result;
        vector<string> path;
        path.push_back(start);
        dict.insert(start);
        dict.insert(end);
        bfs(start, end, dict, distance, memo);// get neirihg and distencace
        dfs(result, path, start, end, distance, memo);// get path
        return result;
    }    
