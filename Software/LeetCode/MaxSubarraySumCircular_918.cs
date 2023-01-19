using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MaxSubarraySumCircular_918
    {
        public int MaxSubarraySumCircular(int[] nums)
        {
            int size = nums.Length;
            if (size == 1)
            {
                return nums[0];
            }
            
            int ans = nums[0];

            List<int> dp = new List<int>();
            dp.Add(nums[0]); // dp[0] = nums[0]

            int sumOfnums = nums[0];
            for (int i = 1; i < size; i++)
            {
                // add all values together for use in case 2
                sumOfnums += nums[i];
                // previous step + self  or only self, which one is bigger 
                dp.Add(Math.Max(dp[i-1] + nums[i], nums[i]));

                ans = Math.Max(ans, dp[i]);
            }

            // case 2: find the min subarray in nums 
            List<int> dp_min = new List<int>();
            dp_min.Add(nums[0]); // dp[0] = nums[0]
            int minSum_circular = int.MaxValue;
            for (int i = 1; i < size; i++)
            {
                // previous step + self  or only self, which one is smaller 
                dp_min.Add(Math.Min(dp_min[i - 1] + nums[i], nums[i]));

                minSum_circular = Math.Min(minSum_circular, dp_min[i]);
            }

            if (ans > 0)
            {
                return Math.Max(ans, sumOfnums - minSum_circular);
            }
            else
            {
                return ans;
            }
        }
    }
}
