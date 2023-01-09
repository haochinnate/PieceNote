using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    public class TreeNode
    {
        public int val;
        public TreeNode left;
        public TreeNode right;
        public TreeNode(int val = 0, TreeNode left = null, TreeNode right = null)
        {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }
    internal class EvaluateBooleanBinaryTree_2331
    {
        public bool EvaluateTree(TreeNode root)
        {
            if (root.val == 0)
            {
                return false;
            }
            else if (root.val == 1)
            {
                return true;
            }
            else if (root.val == 2)
            {
                bool leftResult = EvaluateTree(root.left);
                bool rightResult = EvaluateTree(root.right);
                if (leftResult || rightResult)
                {
                    return true;
                }
                else
                {
                    return leftResult || rightResult;
                }
            }
            else if (root.val == 3)
            {

                bool leftResult = EvaluateTree(root.left);
                bool rightResult = EvaluateTree(root.right);
                
                return leftResult && rightResult;
            }

            return false;
        }
    }
}
