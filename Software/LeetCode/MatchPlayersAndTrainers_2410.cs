using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MatchPlayersAndTrainers_2410
    {
        public int MatchPlayersAndTrainers(int[] players, int[] trainers)
        {
            Array.Sort(players);
            Array.Sort(trainers);

            int counter = 0;
            int trainerIndex = 0;
            for (int i = 0; i < players.Length; i++)
            {
                if (i > trainers.Length - 1)
                {
                    return counter;
                }

                for (int j = trainerIndex; j < trainers.Length; j++)
                {
                    if (trainerIndex == trainers.Length)
                    {
                        return counter;
                    }

                    if (players[i] <= trainers[j])
                    {
                        trainerIndex = j + 1;
                        counter++;
                        break;
                    }
                    else
                    {

                    }
                }
            }


            return counter;
        }
    }
}
