using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Perhaps.Engine
{
    class ConsoleLogger : ILoggerSubsystem
    {
        public void Log(string meesage)
        {
            string formulatedMsg = $"{meesage}";
            Console.WriteLine(formulatedMsg);
        }
    }

    public static class EngineLogger
    {
        private static ILoggerSubsystem mSubSystem;

        public static ILoggerSubsystem _loggerSubsystem 
        {
            get
            {
                if(mSubSystem == null)
                {
                    mSubSystem = new ConsoleLogger();
                }

                return mSubSystem;
            }
            set
            {
                mSubSystem = value;
            }
        }


        public static void Log(string message)
        {
            _loggerSubsystem.Log(message);
        }
    }
}
