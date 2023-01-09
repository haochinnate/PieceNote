using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class DistinctPrimeFactors_2521
    {
        HashSet<int> primes = new HashSet<int>();
        public int DistinctPrimeFactors(int[] nums)
        {
            foreach (var num in nums)
            {
                List<int> primesOfNum = FindPrimes(num);
                primes.UnionWith(primesOfNum); 
            }

            return primes.Count;
        }

        private List<int> FindPrimes(int num)
        {
            List<int> results = new List<int>();
         
            for (int pri = 2; pri < num; pri++)
            {
                while (num % pri == 0 && num != pri)
                {
                    results.Add(pri);
                    num /= pri;
                }
            }
            results.Add(num);

            return results;
        }
    }
}
