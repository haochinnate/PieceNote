using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class FindWinners_2225
    {
        public IList<IList<int>> FindWinners(int[][] matches)
        {
            IList<IList<int>> result = new List<IList<int>>();

            Dictionary<int, int> losesCounts = new Dictionary<int, int>();

            foreach (var match in matches)
            {
                if (!losesCounts.ContainsKey(match[0]))
                {
                    losesCounts.Add(match[0], 0);
                }

                if (!losesCounts.ContainsKey(match[1]))
                {
                    losesCounts.Add(match[1], 1);
                }
                else
                {
                    losesCounts[match[1]]++;
                }
            }

            var noLostWinner = losesCounts.Where(l => l.Value == 0).Select(pair => pair.Key).OrderBy(k => k);
            var oneLostWinner = losesCounts.Where(l => l.Value == 1).Select(pair => pair.Key).OrderBy(k => k);

            result.Add(noLostWinner.ToList());
            result.Add(oneLostWinner.ToList());

            return result;
        }

    }
}
