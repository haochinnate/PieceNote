using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Software.LeetCode
{
    public class PalindromePartitioning_131
    {
        public IList<IList<string>> Partition(string s) 
        {
            List<IList<string>> output = new List<IList<string>>();
            List<string> ds = new List<string>();

            PalindromePartition(0, ds, output, s);

            return output;
        }

        public bool IsPalindrome(string s, int startIndex, int endIndex)
        {
            while (startIndex <= endIndex)
            {
                if (s[startIndex] != s[endIndex])
                {
                    return false;
                }
                startIndex++;
                endIndex--;
            }
            return true;
        }

        public void PalindromePartition(int index, List<string> ds, 
            List<IList<string>> output, string str)
        {
            if (index == str.Length)
            {
                output.Add(new List<string>(ds));
                return;
            }
            for (int i = index; i < str.Length; i++)
            {
                if (IsPalindrome(str, index, i))
                {
                    ds.Add(str.Substring(index, 1));
                    PalindromePartition(i+1, ds, output, str);
                    ds.RemoveAt(ds.Count - 1);
                }
            }
        }

    }
}