using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class DifferenceOfSum_2535
    {
        public int DifferenceOfSum(int[] nums)
        {
            int elementSumTotal = 0;
            int digitSumTotal = 0;
            for (int i = 0; i < nums.Length; i++)
            {
                elementSumTotal += nums[i];

                digitSumTotal += CalculateDigitSum(nums[i]);
            }

            return Math.Abs(elementSumTotal - digitSumTotal);
        }

        private int CalculateDigitSum(int number)
        {
            int sum = 0;
            int tenBase = 1000;
            while (number >= 10)
            {
                if (number >= tenBase)
                {
                    int digit = number / tenBase;
                    sum += digit;
                    number %= tenBase;
                }
                tenBase /= 10;
            }
            sum += number;
            return sum;
        }
    }
}
