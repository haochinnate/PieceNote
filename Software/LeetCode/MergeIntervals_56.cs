using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MergeIntervals_56
    {
        public int[][] Merge(int[][] intervals)
        {
            List<int[]> results = new List<int[]>();
            List<int[]> intervalsList = new List<int[]>(intervals);
            var orderedIntervalsList = intervalsList.OrderBy(x => x[0]).ToList();

            int low = orderedIntervalsList[0][0];
            int high = orderedIntervalsList[0][1];
            for (int i = 1; i < orderedIntervalsList.Count; i++)
            {
                if (orderedIntervalsList[i][0] >= high)
                {
                    results.Add(new int[2] { low, high });
                    low = orderedIntervalsList[i][0];
                    high = orderedIntervalsList[i][1];
                }
                else if (orderedIntervalsList[i][0] < high)
                {
                    high = Math.Max(orderedIntervalsList[i][1], high);
                }               
            }

            results.Add(new int[2] { low, high });
            return results.ToArray();
        }
    }
}
