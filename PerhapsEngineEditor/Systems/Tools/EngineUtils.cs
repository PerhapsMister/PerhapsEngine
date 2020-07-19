using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perhaps.Engine
{
    public static class EngineUtils
    {
        public static bool TryExecute(Action action, bool log = true)
        {
            try
            {
                action();
                return true;
            }
            catch(Exception e)
            {
                if (log)
                    Console.WriteLine(e.ToString());
                
                return false;
            }
        }

    }
}
