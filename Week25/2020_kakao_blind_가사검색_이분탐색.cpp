#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> rWords;

bool comp(string a, string b)
{
    if(a.size() < b.size())
        return true;
    else if(a.size() == b.size())
    {
        if(a < b)
            return true;
    }
    return false;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer;
    
    sort(words.begin(), words.end(), comp);
    rWords = words;

    for(auto& word : rWords)
    {
        reverse(word.begin(), word.end());
    }
    sort(rWords.begin(), rWords.end(), comp);
        
    for(auto query : queries)
    {
        int wordCnt = 0;
        if(query[0] != '?')
        {
            string wordStart = "";
            string wordEnd = "";
            
            for(int i = 0 ; i < query.size() ; i++)
            {
                if(query[i] != '?')
                {
                    wordStart += query[i];
                    wordEnd += query[i];
                }
                else
                {
                    wordStart += "a";
                    wordEnd += "z";
                }
            }
                        
            int lo = lower_bound(words.begin(), words.end(), wordStart, comp) - words.begin();
            int up = upper_bound(words.begin(), words.end(), wordEnd, comp) - words.begin();
            
            wordCnt = up - lo;
        }
        else
        {
            string wordStart = "";
            string wordEnd = "";
            
            for(int i = query.size() - 1 ; i >= 0  ; i--)
            {
                if(query[i] != '?')
                {
                    wordStart += query[i];
                    wordEnd += query[i];
                }
                else
                {
                    wordStart += "a";
                    wordEnd += "z";
                }
            }
                
            int lo = lower_bound(rWords.begin(), rWords.end(), wordStart, comp) - words.begin();
            int up = upper_bound(rWords.begin(), rWords.end(), wordEnd, comp) - words.begin();
            
            wordCnt = up - lo;
        }
        answer.push_back(wordCnt);
    }
    
    return answer;
}

// 출처 : 대경희대졸업생 안효빈
