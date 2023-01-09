using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Metadata.W3cXsd2001;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class SearchInsertPosition_35
    {
        public int SearchInsert(int[] nums, int target)
        {
            if (nums.Length == 1)
            {
                return nums[0] >= target ? 0 : 1;   
            }
            if (target <= nums[0])
            {
                return 0;
            }
            if (target == nums[nums.Length - 1])
            {
                return nums.Length - 1;
            }
            if (target > nums[nums.Length - 1])
            {
                return nums.Length;
            }

            int leftIndex = 0, rightIndex = nums.Length - 1;

            while (leftIndex <= rightIndex)
            {
                int centralIndex = Convert.ToInt32(Math.Ceiling((leftIndex + rightIndex) / 2.0));

                if (nums[centralIndex] >= target)
                {
                    if (nums[centralIndex - 1] < target)
                    {
                        return centralIndex;
                    }
                    else
                    {
                        rightIndex = centralIndex;
                    }
                }
                else
                {
                    if (nums[centralIndex + 1] >= target)
                    {
                        return centralIndex + 1;
                    }
                    else
                    {
                        leftIndex = centralIndex;
                    }
                }
            }

            return -1;
        }

    }
}
