using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class ReversePrefix_2000
    {
        public string ReversePrefix(string word, char ch)
        {
            StringBuilder prefix = new StringBuilder();
            int endingIndex = -1;
            for (int i = 0; i < word.Length; i++)
            {
                if (word[i] == ch)
                {
                    endingIndex = i + 1;
                    prefix.Insert(0, word[i]);
                    break;
                }
                else
                {
                    prefix.Insert(0, word[i]);
                }
            }

            if (endingIndex == -1)
            {
                return word;
            }
            else if (endingIndex == word.Length)
            {
                return prefix.ToString();
            }
            else
            {
                return prefix.ToString() + word.Substring(endingIndex);
            }

        }
    }
}
