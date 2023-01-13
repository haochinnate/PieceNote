using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class NumberOfArrays_2145
    {
        public int NumberOfArrays(int[] differences, int lower, int upper)
        {
            long max_difference = 0;
            long min_difference = 0;
            long num = 0;
            for (int i = 0; i < differences.Length; i++)
            {
                num += differences[i];
                max_difference = Math.Max(max_difference, num);
                min_difference = Math.Min(min_difference, num);                
            }

            long ans = (upper - max_difference) - (lower - min_difference) + 1;
            return ((int)Math.Max((long)0, ans));
        }
    }
}
