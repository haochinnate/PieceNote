using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class ValidParentheses_20
    {
        public bool IsValid(string s)
        {
            Stack<char> stack = new Stack<char>();
            foreach (var parentheses in s)
            {
                if (parentheses == '(' || parentheses == '[' || parentheses == '{')
                {
                    stack.Push(parentheses);
                }
                else if (parentheses == ')')
                {
                    if (stack.Count == 0) return false;
                    var top = stack.Pop();

                    if (top == '(')
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }

                }
                else if (parentheses == ']')
                {
                    if (stack.Count == 0) return false;
                    var top = stack.Pop();

                    if (top == '[')
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }

                }
                else if (parentheses == '}')
                {
                    if (stack.Count == 0) return false;
                    var top = stack.Pop();

                    if (top == '{')
                    {
                        continue;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            return stack.Count == 0;
        }
    }
}
