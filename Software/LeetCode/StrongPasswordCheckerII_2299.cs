using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Leetcode
{
    internal class StrongPasswordCheckerII_2299
    {
        public bool StrongPasswordCheckerII(string password)
        {
            if (password.Length < 8)
            {
                return false;
            }

            bool lowerCaseExist = false;
            bool upperCaseExist = false;
            bool digitExist = false;
            bool specialCharExist = false;

            for (int i = 0; i < password.Length; i++)
            {
                if (!lowerCaseExist)
                {
                    if (char.IsLower(password[i]))
                    {
                        lowerCaseExist = true;
                    }
                }

                if (!upperCaseExist)
                {
                    if (char.IsUpper(password[i]))
                    {
                        upperCaseExist = true;
                    }
                }

                if (!digitExist)
                {
                    if (char.IsDigit(password[i]))
                    {
                        digitExist = true;
                    }
                }

                if (!specialCharExist)
                {
                    if ("!@#$%^&*()-+".Contains(password[i]))
                    {
                        specialCharExist = true;
                    }
                }

                // adjacent position character is same
                if (i+1 < password.Length)
                {
                    if (password[i] == password[i+1])
                    {
                        return false;
                    }
                }
            }

            return lowerCaseExist && upperCaseExist && digitExist && specialCharExist;
        }

    }
}
