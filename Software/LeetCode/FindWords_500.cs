using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class FindWords_500
    {
        public string[] FindWords(string[] words)
        {
            Dictionary<char, int> map = new Dictionary<char, int>()
            {
                { 'q', 1 }, { 'w', 1 }, { 'e', 1 },{ 'r', 1 },{ 't', 1 },{ 'y', 1 },{ 'u', 1 },{ 'i', 1 },{ 'o', 1 },{ 'p', 1 },
                { 'a', 2 }, { 's', 2 }, { 'd', 2 },{ 'f', 2 },{ 'g', 2 },{ 'h', 2 },{ 'j', 2 },{ 'k', 2 },{ 'l', 2 },
                { 'z', 3 }, { 'x', 3 },{ 'c', 3 },{ 'v', 3 },{ 'b', 3 },{ 'n', 3 },{ 'm', 3 }
            };

            List<string> ans = new List<string>();
            foreach (var word in words)
            {
                var newWord = word.ToLower();
                var firstChar = newWord[0];
                var firstCharRow = map[firstChar];
                if (word.Length == 1)
                {
                    ans.Add(word);
                    continue;
                }
                bool isSame = true;
                for (int i = 1; i < newWord.Length; i++)
                {
                    if (map[newWord[i]] != firstCharRow)
                    {
                        isSame = false;
                        break;
                    }
                }

                if (isSame)
                {
                    ans.Add(word);
                }
            }

            return ans.ToArray();
        }
    }
}
