using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Software.LeetCode
{
    public class RestoreIpAddresses_93
    {
        public IList<string> RestoreIpAddresses(string s) 
        {
            List<string> answers = new List<string>();
            AnalyzeIpAddress(s, answers, 0, "", 0);
            return answers;
        }

        private void AnalyzeIpAddress(string currentString,
            List<string> allAnswers, int index, string temp, int count)
        {
            if (count > 4)
            {
                return; 
            }

            if (count == 4 && index == currentString.Length)
            {
                allAnswers.Add(temp);
            }

            for (int i = 1; i < 4; i++)
            {
                if (index + i > currentString.Length)
                {
                    break;
                }

                string s = currentString.Substring(index, i);

                if ((s.StartsWith("0") && s.Length > 1) || (i==3 && Convert.ToInt32(s) >= 256))
                {
                    continue;
                }

                AnalyzeIpAddress(currentString, allAnswers, 
                    index + i, 
                    temp + s + (count == 3? "" : "."), 
                    count + 1);
            }

        }
    }
}