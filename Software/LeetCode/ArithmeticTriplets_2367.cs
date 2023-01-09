using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class ArithmeticTriplets_2367
    {       
        public int ArithmeticTriplets_Naive(int[] nums, int diff)
        {
            int answer = 0;
            for (int i = 0; i < nums.Length; i++)
            {
                for (int j = i+1; j < nums.Length; j++)
                {
                    for (int k = j+1; k < nums.Length; k++)
                    {
                        if (nums[j] - nums[i] == diff)
                        {
                            if (nums[k] - nums[j] == diff)
                            {
                                answer++;
                            }
                        }
                    }
                }
            }

            return answer;
        }

    }
}
