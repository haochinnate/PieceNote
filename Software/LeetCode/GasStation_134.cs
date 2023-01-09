using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class GasStation_134
    {
        public int CanCompleteCircuit(int[] gas, int[] cost)
        {
            int n = gas.Length;
            int totalGasAmount = 0;
            int tankGasAmout = 0;
            int startIndex = 0;

            for (int i = 0; i < n; i++)
            {
                totalGasAmount += gas[i] - cost[i];
                tankGasAmout += gas[i] - cost[i];
                if (tankGasAmout < 0)
                {
                    tankGasAmout = 0;
                    startIndex = i + 1;
                }
            }

            return (totalGasAmount < 0) ? -1 : startIndex;

        }
    }
}
