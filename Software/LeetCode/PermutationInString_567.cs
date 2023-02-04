using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class PermutationInString_567
    {
        public bool CheckInclusion(string s1, string s2)
        {
            if (s1.Length > s2.Length)
            {
                return false;
            }


            List<int> alphabetFrequencyS1 = new List<int>(26);
            List<int> alphabetFrequencyS2 = new List<int>(26);

            for (int i = 0; i < 26; i++)
            {
                alphabetFrequencyS1.Add(0);
                alphabetFrequencyS2.Add(0);
            }

            for (int i = 0; i < s1.Length; i++)
            {
                alphabetFrequencyS1[s1[i] - 'a']++;
                alphabetFrequencyS2[s2[i] - 'a']++;
            }
            

            if (IsPermutation(alphabetFrequencyS1, alphabetFrequencyS2))
            {
                return true;
            }

            int leftIndex = 0;
            for (int rightIndex = s1.Length; rightIndex < s2.Length; rightIndex++)
            {
                alphabetFrequencyS2[s2[leftIndex] - 'a']--;
                leftIndex++;
                alphabetFrequencyS2[s2[rightIndex] - 'a']++;
                if (IsPermutation(alphabetFrequencyS1, alphabetFrequencyS2))
                {
                    return true;
                }
            }

            return false;
        }

        private bool IsPermutation(List<int> list1, List<int> list2)
        {
            for (int i = 0; i < list1.Count; i++)
            {
                if (list1[i] != list2[i])
                {
                    return false;
                }
            }
            return true;
        }
    }
}
