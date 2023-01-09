using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MinimumRoundsToCompleteAllTasks_2244
    {
        Dictionary<int, int> taskNumberTable = new Dictionary<int, int>();

        public int MinimumRounds(int[] tasks)
        {
            int round = 0;
            for (int i = 0; i < tasks.Length; i++)
            {
                if (taskNumberTable.ContainsKey(tasks[i]))
                {
                    taskNumberTable[tasks[i]]++;
                }
                else
                {
                    taskNumberTable.Add(tasks[i], 1);
                }
            }

            foreach (var taskNumberPair in taskNumberTable)
            {
                if (taskNumberPair.Value == 1)
                {
                    return -1;
                }
                else if (taskNumberPair.Value % 3 == 0)
                {
                    round += taskNumberPair.Value / 3;
                }
                else
                {
                    round += (taskNumberPair.Value / 3) + 1; 
                }
            }

            return round;

        }
    }
}
