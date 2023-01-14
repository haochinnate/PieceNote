using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Software.LeetCode
{
    public class SmallestEquivalentString_1061
    {
        public string SmallestEquivalentString(string s1, string s2, string baseStr) 
        {
            List<HashSet<char>> allSets = new List<HashSet<char>>();

            for (int i = 0; i < s1.Length; i++)
            {
                var s1CharSet = allSets.FirstOrDefault(s => s.Contains(s1[i]) == true);
                var s2CharSet = allSets.FirstOrDefault(s => s.Contains(s2[i]) == true);

                if (s1CharSet == null && s2CharSet == null)
                {
                    allSets.Add(new HashSet<char>() { s1[i], s2[i]});
                }
                else if (s1CharSet != null && s2CharSet == null)
                {
                    s1CharSet.Add(s2[i]);
                }
                else if (s1CharSet == null && s2CharSet != null)
                {
                    s2CharSet.Add(s1[i]);
                }
                else
                {
                    var newSet = new HashSet<char>(s1CharSet);
                    newSet.UnionWith(s2CharSet);
                    allSets.Remove(s1CharSet);
                    allSets.Remove(s2CharSet);
                    allSets.Add(newSet);
                }
            }

            for (int i = 0; i < allSets.Count; i++)
            {
                allSets[i] = allSets[i].OrderBy(x => x).ToHashSet();
            }

            StringBuilder result = new StringBuilder();
            for (int i = 0; i < baseStr.Length; i++)
            {
                var newCharSet = allSets.FirstOrDefault(s => s.Contains(baseStr[i]));

                if (newCharSet == null)
                {
                    result.Append(baseStr[i]);
                }
                else
                {
                result.Append(newCharSet.First());

                }

            }

            return result.ToString();

        }
    }
}