using System;
using System.IO;
using System.Collections;

namespace Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\r\n\r\n");
            Console.WriteLine("<h1>Environment Variables</h1>");
            foreach (DictionaryEntry v in Environment.GetEnvironmentVariables())
                Console.WriteLine("<hr><b>{0}</b>:{1}", v.Key, v.Value);
        }
    }
}