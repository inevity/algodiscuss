https://leetcode.com/problems/word-break-ii/description/
https://www.lintcode.com/problem/word-break-ii
class Solution {
public:
    /*
     * @param s: A string
     * @param wordDict: A set of words.
     * @return: All possible sentences.
     */
    vector<string> wordBreak(string &s, unordered_set<string> &wordDict) {
        // write your code here
        vector<string> ans;
        vector<string> split;
         int max_length = 0;
        for (auto iter = wordDict.begin(); iter != wordDict.end(); ++iter) {
            max_length = max(max_length, static_cast<int>((*iter).length()));
        }
        // return dfs(s, 0, split, ans, dict);
        //dfs1(s, 0, split, ans, wordDict, max_length);
        vector<bool> memo(s.size(), true); //why default true;
        dfs2(s, 0, split, ans, wordDict, max_length, memo);
       // if (ans.size() > 0) {
       //     return true;
       // } else {
       //     return false;
       // }
       return ans;
    }
    vector<string> wordBreaksimple(string &s, unordered_set<string> &wordDict) {
        ss = s;
        dict = wordDict;
        n = s.size();


        for (int i = 0; i < n; ++i) {
            cout << "here" << endl;
            //f[i] = true;
            f.push_back(true);
            cout << "here1" << endl;
        }
        dfssimple(0, "");
        return ans;

    }

private:
        vector<string> ans;
        string ss;
        unordered_set<string> dict;
        vector<bool> f;;
        int n;
    bool dfssimple(int p, string now) { // p next start,startindex. and the now is path.
   // bool dfs(int p, string &now) { // constant as rval
        if (p == n) {
            ans.push_back(now);
            return true;
        }
        if (!f[p]) return false;

        if (p > 0) now += " ";// now = now + " ";

        bool success = false;
        string cur = "";
        for (int i = p; i < n; i++) {
            cur += ss[i];
            if (dict.find(cur) != dict.end()) success |= dfssimple(i + 1, now + cur);
        }
        // memo the whole and consective to flase .连续取值。一次为真，就成功但必须到字符串结束。 还是不理解
        // 注意，这里没有backtracking？？
        f[p] = success;
        return success;

    }
   // even add max_length,also get Time Limit Exceeded. think deep

   // 那么这里怎么dfs memo呢？
    void dfs1(string &s, int startindex, vector<string> &split, vector<string> &ans,
   unordered_set<string> &dict, int max_length) {
       if (startindex == s.size()) {
           string str;
           for (auto ss : split) {
               cout << ss << endl;
               str = str + " " + ss;
           }
           ans.push_back(str.substr(1, str.size()));
           return;// why forget
       }

       for (int i = startindex; i < s.size(); i++) {
           if (i - startindex + 1 <= max_length) {
                 auto str = s.substr(startindex, i - startindex + 1);

                 if (dict.find(str) != dict.end()) {
                     split.push_back(str);
                     dfs1(s, i + 1, split, ans, dict, max_length);
                     split.pop_back();
                 }
           } else {
               break; //剪支
           }
       }
       return;
   }
    bool dfs2(string &s, int startindex, vector<string> &split, vector<string> &ans,
   unordered_set<string> &dict, int max_length, vector<bool> &memo) {
       if (startindex == s.size()) {
           string str;
           for (auto ss : split) { // same above ,we can build the path once start.
               //cout << ss << endl;
               str = str + " " + ss;
           }
           ans.push_back(str.substr(1, str.size()));
           return true;// why forget
       }
       //cout << "here" << endl;
       if (!memo[startindex]) return false;
       //cout << "str" << str << endl;
       bool success = false;
       for (int i = startindex; i < s.size(); i++) {
           if (i - startindex + 1 <= max_length) {
                 auto str = s.substr(startindex, i - startindex + 1);

                 if (dict.find(str) != dict.end()) { // maybe this find can memo??
                                                     // for loop s ,isword[i][j]
                                                     //possilbe [i]=
                                                     // if (isWord[i][j] && possible[j + 1])
                                                     //possible[i] = true;//memo
                                                     // 如果false就表面没必要sou直接return。
                     split.push_back(str);
                     //cout << "str" << str << endl;
                     success |= dfs2(s, i + 1, split, ans, dict, max_length, memo);
                     // 原来的dfs memo 是由于if else 我这里是用的for循环。可以吗？可以

                     // 以statrindx开始的下一个split，可以false 可以true，但是最后
                     // 行成了path。我们要的是最终能否达到true 且startindex=n。
                     // 对于每个startindex的 为什么可以找到多个集合呢？ 因为递归
                     split.pop_back();
                     //if (success) continue;
                 }
           } else {
               break; //剪支
           }
       }
       memo[startindex] = success;
       return success;
   }
    bool dfs2clean(string &s, int startindex, vector<string> &split, vector<string> &ans,
   unordered_set<string> &dict, int max_length, vector<bool> &memo) {
       if (startindex == s.size()) {
           string str;
           for (auto ss : split) { // same above ,we can build the path once start.
               str = str + " " + ss;
           }
           ans.push_back(str.substr(1, str.size()));
           return true;// why forget
       }
       if (!memo[startindex]) return false;
       bool success = false;
       for (int i = startindex; i < s.size(); i++) {
           if (i - startindex + 1 <= max_length) {
                 auto str = s.substr(startindex, i - startindex + 1);
                 if (dict.find(str) != dict.end()) {
                     split.push_back(str);
                     success |= dfs2(s, i + 1, split, ans, dict, max_length, memo);
                     split.pop_back();
                 }
           } else {
               break; //剪支
           }
       }
       memo[startindex] = success;
       return success;
   }
 // https://www.jiuzhang.com/solution/word-break-ii/#tag-highlight-lang-java
 // 我们可以把s字符串的splie结果list作为memo。持续对字符串递归。
 // 这里是对字符串进行递归变化，前面是对i+1长度进行。。
 // 纯粹的一个递归
 // public ArrayList<String> wordBreakHelper(String s, Set<String> dict, Map<String, ArrayList<String>> memo){
//         if(memo.containsKey(s)) return memo.get(s);
//         ArrayList<String> result = new ArrayList<String>();
//         int n = s.length();
//         if(n <= 0) return result;
//         for(int len = 1; len <= n; ++len){
//             String subfix = s.substring(0,len);
//             if(dict.contains(subfix)){
//                 if(len == n){
//                     result.add(subfix);
//                 }else{
//                     String prefix = s.substring(len);
//                     ArrayList<String> tmp = wordBreakHelper(prefix, dict, memo);
//                     for(String item:tmp){
//                         item = subfix + " " + item;
//                         result.add(item);
//                     }
//                 }
//             }
//         }
//         memo.put(s, result);
//         return result;
//     }



 //  //将s 分割成s1 s2  其中s1长度为len 分治法
 //很好的思维 只是拆分为s1 包含在词典，然后递归到第二个s2
//  // version：高频题班
// public class Solution {
//     public List<String> wordBreak(String s, Set<String> dict) {
//         Map<String, List<String>> done = new HashMap<>();
//         done.put("", new ArrayList<>());
//         done.get("").add("");
//
//         return dfs(s, dict, done);
//     }
//
//     List<String> dfs(String s, Set<String> dict, Map<String, List<String>> done) {
//         if (done.containsKey(s)) {
//             return done.get(s);
//         }
//         List<String> ans = new ArrayList<>();
//
//         for (int len = 1; len <= s.length(); len++) {  //将s 分割成s1 s2  其中s1长度为len
                //分治 ，1到len次的分治法。
//             String s1 = s.substring(0, len);
//             String s2 = s.substring(len);
//
//             if (dict.contains(s1)) {
//                 List<String> s2_res = dfs(s2, dict, done);
//                 for (String item : s2_res) {
//                     if (item == "") {
//                         ans.add(s1);
//                     } else {
//                         ans.add(s1 + " " + item);
//                     }
//                 }
//             }
//         }
//         done.put(s, ans);
//         return ans;
//     }
//
};
