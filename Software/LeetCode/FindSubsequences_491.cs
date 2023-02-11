using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Software.LeetCode
{
    public class FindSubsequences_491
    {
        public IList<IList<int>> FindSubsequences(int[] nums) 
        {
            
            IList<IList<int>> allSubSequences = new List<IList<int>>();
            HashSet<int> considered = new HashSet<int>();

            for (int i = 0; i < nums.Length; i++)
            {
                if (!considered.Contains(nums[i]))
                {
                    FindSubsequencesWorkHorse(nums, i, allSubSequences, new List<int>());
                }

                considered.Add(nums[i]);
            }


            return allSubSequences;
        }

        void FindSubsequencesWorkHorse(int[] nums, int index,
            IList<IList<int>> allSubsequences, 
            IList<int> currentSubsequence)
        {
            int subsequenceLastItemIndex = currentSubsequence.Count-1;

            HashSet<int> considered = new HashSet<int>();
            for(int i = index+1; i < nums.Length; i++)
            {
                if(nums[i] >= currentSubsequence[subsequenceLastItemIndex] && !considered.Contains(nums[i]))
                {
                    currentSubsequence.Add(nums[i]);
                    allSubsequences.Add(new List<int>(currentSubsequence));
                    FindSubsequencesWorkHorse(nums, i, allSubsequences, currentSubsequence);
                    currentSubsequence.RemoveAt(subsequenceLastItemIndex+1);
                }

                considered.Add(nums[i]);
            }
        }
    }
}