using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class BestTeamScore_1626
    {
        public int BestTeamScore(int[] scores, int[] ages)
        {
            int playerCount = scores.Length;

            (int score, int age)[] scoreAgeTuples = new (int score, int age)[playerCount];
            for (int i = 0; i < playerCount; i++)
            {
                scoreAgeTuples[i] = (scores[i], ages[i]);
            }

            Array.Sort(scoreAgeTuples, (player1, player2) =>
            {
                var cmp = player1.age.CompareTo(player2.age);
                if (cmp != 0)
                {
                    return cmp;
                }
                return player1.score.CompareTo(player2.score);
            });

            int[] dp = new int[playerCount];


            for (int i = 0; i < playerCount; i++)
            {
                dp[i] = scoreAgeTuples[i].score;

                for (int j = 0; j < i; j++)
                {
                    if (scoreAgeTuples[j].age == scoreAgeTuples[i].age)
                    {
                        dp[i] = Math.Max(dp[i], dp[j] + scoreAgeTuples[i].score);
                    }
                    else if (scoreAgeTuples[j].age < scoreAgeTuples[i].age
                        && scoreAgeTuples[j].score <= scoreAgeTuples[i].score)
                    {
                        dp[i] = Math.Max(dp[i], dp[j] + scoreAgeTuples[i].score);
                    }
                }
            }

            int result = int.MinValue;
            for (int i = 0; i < playerCount; i++)
            {
                result = Math.Max(result, dp[i]);
            }

            return result;
        }
    }
}
