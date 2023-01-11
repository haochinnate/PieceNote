using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Leetcode
{
    internal class LevelOrderBottom_107
    {
        List<IList<int>> results = new List<IList<int>>();
        List<TreeNode> processOrder = new List<TreeNode>();
        public IList<IList<int>> LevelOrderBottom(TreeNode root)
        {
            if (root == null)
            {
                return results;
            }

            processOrder.Add(root);
            while (processOrder.Count !=0)
            {
                int size = processOrder.Count;

                List<int> level = new List<int>();

                for (int i = 0; i < size; i++)
                {
                    var currentNode = processOrder[0];
                    processOrder.RemoveAt(0);

                    if (currentNode.left != null)
                    {
                        processOrder.Add(currentNode.left);
                    }
                    if (currentNode.right != null)
                    {
                        processOrder.Add(currentNode.right);
                    }

                    level.Add(currentNode.val);
                }
                results.Add(level);
            }

            results.Reverse();
            return results;
        }
      
    }
}
