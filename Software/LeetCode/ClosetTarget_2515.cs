using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class ClosetTarget_2515
    {
        public int ClosetTarget(string[] words, string target, int startIndex)
        {
            List<int> matchTargetDistance = new List<int>();
            
            
            for (int i = 0; i < words.Length; i++)
            {
                if (words[i].Equals(target))
                {
                    if (startIndex >= i)
                    {
                        matchTargetDistance.Add(startIndex - i);
                        matchTargetDistance.Add(words.Length - startIndex + i);

                    }
                    else
                    {
                        matchTargetDistance.Add(i - startIndex);
                        matchTargetDistance.Add(startIndex + words.Length - i);
                    }
                }
            }

            if (matchTargetDistance.Count == 0)
            {
                return -1;
            }
            else
            {
                return matchTargetDistance.Min(); 
            }
        }
    }
}
