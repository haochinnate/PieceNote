using System;
using System.CodeDom;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class MinTime_1443
    {
        Dictionary<int, List<int>> graph = new Dictionary<int, List<int>>();
        Dictionary<int, bool> nodeIsVisited = new Dictionary<int, bool>();


        public int MinTime(int n, int[][] edges, IList<bool> hasApple)
        {
            CreateGraph(edges);
            return DFS(0, 0, hasApple);
        }

        private int DFS(int nodeIdx, int cost, IList<bool> hasApple)
        {
            if (nodeIsVisited[nodeIdx])
            {
                return 0;
            }
            nodeIsVisited[nodeIdx] = true;

            int childrenCost = 0;
            foreach (var childIndex in graph[nodeIdx])
            {
                childrenCost += DFS(childIndex, 2, hasApple);
            }

            if (childrenCost == 0 && !hasApple[nodeIdx])
            {
                return 0;
            }

            return childrenCost + cost;

        }

        private void CreateGraph(int[][] edges)
        {
            for (int i = 0; i < edges.Length; i++)
            {
                var edge = edges[i];
                if (!graph.ContainsKey(edge[0]))
                {
                    graph[edge[0]] = new List<int>() { edge[1] };
                    nodeIsVisited[edge[0]] = false;
                }
                else
                {
                    graph[edge[0]].Add(edge[1]);
                }

                if (!graph.ContainsKey(edge[1]))
                {
                    graph[edge[1]] = new List<int>() { edge[0] };
                    nodeIsVisited[edge[1]] = false;
                }
                else
                {
                    graph[edge[1]].Add(edge[0]);
                }
            }
        }
    }
}
