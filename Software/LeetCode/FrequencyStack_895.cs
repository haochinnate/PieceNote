using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class FrequencyStack_895
    {
        public class FreqStack
        {
            Dictionary<int, int> numberToTimesMapping = new Dictionary<int, int>();
            Dictionary<int, Stack<int>> timesToNumbers = new Dictionary<int, Stack<int>>();
            int maximumFrequency = 0;
            public FreqStack()
            {

            }

            public void Push(int val)
            {
                if (numberToTimesMapping.ContainsKey(val))
                {
                    numberToTimesMapping[val]++;
                }
                else
                {
                    numberToTimesMapping.Add(val, 1);
                }
                
                maximumFrequency = Math.Max(maximumFrequency, numberToTimesMapping[val]);

                if (timesToNumbers.ContainsKey(numberToTimesMapping[val]))
                {
                    timesToNumbers[numberToTimesMapping[val]].Push(val);
                }
                else
                {
                    var newStack = new Stack<int>();
                    newStack.Push(val);
                    timesToNumbers.Add(numberToTimesMapping[val], newStack);
                }
            }

            public int Pop()
            {
                int highestFrequenct_number = timesToNumbers[maximumFrequency].Pop();

                numberToTimesMapping[highestFrequenct_number]--;

                if (timesToNumbers[maximumFrequency].Count == 0)
                {
                    maximumFrequency--;
                }

                return highestFrequenct_number;                
            }
        }

    }
}
