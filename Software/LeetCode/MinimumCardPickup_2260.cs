using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MinimumCardPickup_2260
    {
        public int MinimumCardPickup(int[] cards)
        {
            if (cards.Length == 1)
            {
                return -1;
            }

            int minimumNumber = int.MaxValue;

            Dictionary<int, int> cardsDistance = new Dictionary<int, int>();
            for (int idx = 0; idx < cards.Length; idx++)
            {
                if (cardsDistance.ContainsKey(cards[idx]))
                {
                    // already has card in map
                    minimumNumber = Math.Min(minimumNumber, idx - cardsDistance[cards[idx]] + 1);

                    // new card index
                    cardsDistance[cards[idx]] = idx;
                }
                else
                {
                    // not yet in map
                    cardsDistance.Add(cards[idx], idx);
                }
            }

            return minimumNumber == int.MaxValue ? -1 : minimumNumber;
        }
    }
}
