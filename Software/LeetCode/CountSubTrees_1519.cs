using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class CountSubTrees_1519
    {
        Dictionary<int, List<int>> graph = new Dictionary<int, List<int>>();
        List<int> results;

        public int[] CountSubTrees(int n, int[][] edges, string labels)
        {
            results= new List<int>(n);
            for (int i = 0; i < n; i++)
            {
                results.Add(0);
            }

            CreateGraph(n, edges);
            
            DFS(0, 0, labels);

            return results.ToArray();
        }
        

        private Dictionary<char, int> DFS(int nodeIdx, int cost, string labels)
        {
            Dictionary<char, int> currentNodeResult = new Dictionary<char, int>();
            if (currentNodeResult.ContainsKey(labels[nodeIdx]))
            {
                currentNodeResult[labels[nodeIdx]]++;
            }
            else
            {
                currentNodeResult.Add(labels[nodeIdx], 1);
            }


            foreach (var childIndex in graph[nodeIdx])
            {
                if (graph.ContainsKey(childIndex))
                {
                    graph[childIndex].Remove(nodeIdx);
                }
                var childResult = DFS(childIndex, labels[nodeIdx], labels);
                foreach (var pair in childResult)
                {
                    if (currentNodeResult.ContainsKey(pair.Key))
                    {
                        currentNodeResult[pair.Key] += pair.Value;
                    }
                    else
                    {
                        currentNodeResult.Add(pair.Key, pair.Value);
                    }

                }
            }

            results[nodeIdx] = currentNodeResult[labels[nodeIdx]];

            return currentNodeResult;   
        }

        private void CreateGraph(int nodeCount, int[][] edges)
        {
            for (int i = 0; i < nodeCount; i++)
            {
                graph[i] = new List<int>();
            }

            for (int i = 0; i < edges.Length; i++)
            {
                var edge = edges[i];
                graph[edge[0]].Add(edge[1]);
                graph[edge[1]].Add(edge[0]);
                //if (graph.ContainsKey(edge[0]) && graph.ContainsKey(edge[1]))
                //{
                //    graph[edge[0]].Add(edge[1]);
                //}
                //else if (!graph.ContainsKey(edge[0]) && !graph.ContainsKey(edge[1]))
                //{
                //    graph[edge[0]].Add(edge[1]);
                //}
                //else if (graph.ContainsKey(edge[0]) && !graph.ContainsKey(edge[1]))
                //{
                //    graph[edge[0]].Add(edge[1]);
                //}
                //else if (!graph.ContainsKey(edge[0]) && graph.ContainsKey(edge[1]))
                //{
                //    graph[edge[1]].Add(edge[0]);
                //}
            }
        }
    }
}
