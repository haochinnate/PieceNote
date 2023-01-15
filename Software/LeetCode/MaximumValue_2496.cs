using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Software.LeetCode
{
    public class MaximumValue_2496
    {
        public int MaximumValue(string[] strs) 
        {
            
            int maxSize = int.MinValue;
            foreach (var str in strs)
            {
                bool isAllDigit = true;
                
                for (int i = 0; i < str.Length; i++)
                {
                    if (char.IsLetter(str[i]))
                    {
                        isAllDigit = false;
                        break;
                    }
                }

                if (isAllDigit)
                {
                    maxSize = Math.Max(maxSize, Convert.ToInt32(str));
                }
                else
                {
                    maxSize = Math.Max(maxSize, str.Length);
                }


            }        

            return maxSize;
        }
    }
}