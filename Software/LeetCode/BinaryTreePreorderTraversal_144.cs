using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class BinaryTreePreorderTraversal_144
    {

        List<int> preorderTraversalResult = new List<int>();

        public IList<int> PreorderTraversal(TreeNode root)
        {
            if (root == null)
            {
                return new List<int>();
            }

            preorderTraversalResult.Add(root.val);

            if (root.left == null && root.right == null)
            {
                return new List<int>() { root.val };
            }

            PreorderTraversal(root.left);
            PreorderTraversal(root.right);

            return preorderTraversalResult;
        }

    }
}
