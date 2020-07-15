using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;

namespace Perhaps.Engine
{
    public static class Time
    {
        public static event Action<float> OnAvgDeltaUpdate;

        public static float Elapsed {get; private set;}
        public static float DeltaTime {get; private set;}
        public static float AverageDelta {get; private  set;}
        static Stopwatch sw;

        static Time()
        {
            sw = new Stopwatch();
        }

        static List<float> deltas = new List<float>();
        static float timer = 0f;
        public static void OnFrameStart()
        {
            sw.Stop();
            float delta = (float)sw.Elapsed.TotalSeconds;
            DeltaTime = delta;
            Elapsed += delta;
            deltas.Add(delta);
            timer += delta;
            
            if(timer >= 1f)
            {
                float sum = 0f;
                for (int i = 0; i < deltas.Count; i++)
                {
                    sum += deltas[i];
                }

                sum /= deltas.Count;
                AverageDelta = sum;
                deltas.Clear();
                if(OnAvgDeltaUpdate != null)
                {
                    OnAvgDeltaUpdate(AverageDelta);
                }

                timer = 0f;
            }

            sw.Restart();
        }
    }
}