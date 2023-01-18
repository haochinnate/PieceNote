using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MinFlipsMonoIncr_926
    {
        public int MinFlipsMonoIncr(string s)
        {
            return CalculateWorkhorse(s, 0, 0);
        }

        private int CalculateWorkhorse(string s, int counter_one, int counter_flip)
        {
            foreach (var singleChar in s)
            {
                if (singleChar == '1')
                {
                    counter_one++;
                }
                else if (singleChar == '0')
                {
                    counter_flip++;
                }

                counter_flip = Math.Min(counter_one, counter_flip);
            }

            return counter_flip;
        }
    }
}
