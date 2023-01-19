using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class SubarraysDivByK_974
    {
        public int SubarraysDivByK(int[] nums, int k)
        {
            int result = 0;

            // remainderToFrequencyMap
            List<int> remainderToFrequencyMap = new List<int>(new int[k])
            {
                [0] = 1
            };

            int sumToCurrentIndex = 0;

            for (int i = 0; i < nums.Length; i++)
            {
                sumToCurrentIndex += nums[i];
                
                int remainder = sumToCurrentIndex % k;
                if (remainder < 0)
                {
                    remainder += k;
                }

                result += remainderToFrequencyMap[remainder];

                remainderToFrequencyMap[remainder]++;
            }

            return result;
        }
    }
}
