using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class ZigzagConvert_6
    {
        public string Convert(string s, int numRows)
        {
            if (numRows == 1)
            {
                return s;
            }

            List<StringBuilder> eachRowsContents = new List<StringBuilder>(numRows);
            for (int i = 0; i < numRows; i++)
            {
                eachRowsContents.Add(new StringBuilder());
            }


            int currentRowIndex = 0;
            bool zigzagDirectionIsDown = true;
            foreach (var singleChar in s)
            {
                eachRowsContents[currentRowIndex].Append(singleChar);

                if (zigzagDirectionIsDown)
                {
                    if (currentRowIndex == numRows - 1)
                    {
                        zigzagDirectionIsDown = false;
                        currentRowIndex--;
                    }
                    else
                    {
                        currentRowIndex++;
                    }
                }
                else
                {
                    if (currentRowIndex == 0)
                    {
                        zigzagDirectionIsDown = true;
                        currentRowIndex++;
                    }
                    else
                    {
                        currentRowIndex--;
                    }
                }
            }

            StringBuilder result = new StringBuilder();
            foreach (var rowContent in eachRowsContents)
            {
                result.Append(rowContent.ToString());
            }

            return result.ToString();
        }
    }
}
