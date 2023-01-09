using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class SmallestNumberInInfiniteSet_2336
    {
    }

    public class SmallestInfiniteSet
    {
        List<int> missingElements = new List<int>();
        int currentSmallestNumber = 1;
        public SmallestInfiniteSet()
        {

        }

        public int PopSmallest()
        {
            int tmpSmallestNumner = currentSmallestNumber;
            int newSmallestNumber = currentSmallestNumber + 1;
            while (true)
            {                
                if (!missingElements.Contains(newSmallestNumber))
                {
                    currentSmallestNumber = newSmallestNumber;
                    break;
                }
                else
                {
                    newSmallestNumber++;
                }
            }

            missingElements.Add(tmpSmallestNumner);
            return tmpSmallestNumner;
        }

        public void AddBack(int num)
        {
            if (num < currentSmallestNumber)
            {
                currentSmallestNumber = num;
            }

            if (missingElements.Contains(num))
            {
                missingElements.Remove(num);
            }
        }
    }
}
