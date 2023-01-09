using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class IntersectionOfTwoArrays_349
    {
        public int[] Intersection(int[] nums1, int[] nums2)
        {
            List<int> list = new List<int>();
            for (int i = 0; i < nums1.Length; i++)
            {
                if (!list.Contains(nums1[i]))
                {
                    list.Add(nums1[i]);
                }
            }

            List<int> ans = new List<int>();
            for (int i = 0; i < nums2.Length; i++)
            {
                if (list.Contains(nums2[i]) && !ans.Contains(nums2[i]))
                {
                    ans.Add(nums2[i]);
                }
            }

            return ans.ToArray();
        }
    }
}
