using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class InsertInterval_57
    {
        public int[][] Insert(int[][] intervals, int[] newInterval)
        {
            var intervalsList = intervals.ToList();

            var result = new List<int[]>();

            // int currentIndex = -1;

            for (int i = 0; i < intervalsList.Count; i++)
            {
                if (intervalsList[i][1] <= newInterval[0])
                {
                    result.Add(intervalsList[i]);
                }
                else if (intervalsList[i][0] >= newInterval[1])
                {
                    result.Add(newInterval);
                    newInterval = intervalsList[i];
                }
                else
                {
                    newInterval[0] = Math.Min(intervalsList[i][0], newInterval[0]);
                    newInterval[1] = Math.Max(intervalsList[i][1], newInterval[1]);
                }
            }
            result.Add(newInterval);

            return result.ToArray();
        }
    }
}
