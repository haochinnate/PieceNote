using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    public class ListNode
    {
        public int val;
        public ListNode next;
        public ListNode(int val = 0, ListNode next = null)
        {
            this.val = val;
            this.next = next;
        }
    }

    internal class PairSum_2130
    {
        public int PairSum(ListNode head)
        {
            ListNode tail;
            List<ListNode> reverserOrder = new List<ListNode>();

            ListNode current = head;
            while (current.next != null)
            {
                reverserOrder.Add(current);
                current = current.next;
            }
            reverserOrder.Add(current); // last item

            int maxValue = int.MinValue;

            for (int i = 0; i < reverserOrder.Count/2; i++)
            {
                if (reverserOrder[i].val + reverserOrder[reverserOrder.Count-1-i].val > maxValue)
                {
                    maxValue = reverserOrder[i].val + reverserOrder[reverserOrder.Count - 1 - i].val;
                }
            }

            return maxValue;
        }

    }
}
