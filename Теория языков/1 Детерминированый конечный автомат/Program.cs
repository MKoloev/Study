using System;
using System.Collections.Generic;
using System.IO;

namespace xDlars
{

    public class State
    {
        public string[][] rangeString = {
            new [] { " ", "\t", "\n", "\r"},
            new [] { "a-z", "A-Z"},
            new [] { "0-9"},
            new [] { "["},
            new [] { "]"},
            new [] { "_"},
            new [] { "?"},
            new [] { ";"},
            new [] { ","},
            new [] { "."},
            new [] { "@"},
            new [] { "System"},
            new [] { "Sbyte", "Int16", "Int32", "Int64", "Byte", "UInt16", "UInt32", "UInt64", "Single", "Double", "Decimal", "Boolean", "Char", "String", "Object" },
            new [] { "sbyte", "short", "int", "long", "byte", "ushort", "uint", "ulong", "float", "double", "decimal", "bool", "char", "string", "object"},
            new [] { "\0" }
                };

        public int countState = 15;
        public int[,,] delta =
        { //    ' '      A        0        [        ]        _        ?        ;        ,        .       @        S        S         i    
            {{ 0, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 1, 0}, { 2, 0}, { 5, 0} , { 5, 0}, {99, 0}},//0
            {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 2, 0}, { 5, 0} , {-1, 0}, {-1, 0}},//1
            {{ 2, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 3, 0}, {-1, 0}, {-1, 0}, {-1, 0} , {-1, 0}, {-1, 0}},//2
            {{ 3, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 4, 0}, {-1, 0}, { 5, 0} , {-1, 0}, {-1, 0}},//3
            {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 5, 0} , {-1, 0}, {-1, 0}},//4
            {{ 6, 0}, {-1, 0}, {-1, 0}, { 7, 0}, {-1, 0}, {-1, 0}, { 8, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 9, 1}, {-1, 0}, {-1, 0} , {-1, 0}, {-1, 0}},//5
            {{ 6, 0}, {10, 1}, {-1, 0}, { 7, 0}, {-1, 0}, {10, 1}, { 8, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 9, 1}, {10, 1}, {10, 1} , {13, 1}, {-1, 0}},//6
            {{ 7, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 6, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 7, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} , {-1, 0}, {-1, 0}},//7
            {{ 6, 0}, {10, 1}, {-1, 0}, { 7, 0}, {-1, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 9, 1}, {10, 1}, {10, 1} , {13, 1}, {-1, 0}},//8
            {{-1, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {10, 1}, {10, 1} , {10, 1}, {-1, 0}},//9
            {{11, 2}, {10, 1}, {10, 1}, {-1, 0}, {-1, 0}, {10, 1}, {-1, 0}, { 0, 2}, {12, 2}, {-1, 0}, {-1, 0}, {10, 1}, {10, 1} , {10, 1}, {-1, 0}},//10
            {{11, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 0, 0}, {12, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} , {-1, 0}, {-1, 0}},//11
            {{12, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, { 9, 1}, {10, 1}, {10, 1} , {13, 1}, {-1, 0}},//12
            {{-1, 0}, {10, 1}, {10, 1}, {-1, 0}, {-1, 0}, {10, 1}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} , {-1, 0}, {-1, 0}} //13
        };
        //{{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0} , {-1, 0}}
    }



    class Program
    {
        static void Main()
        {
            //File.ReadAllLines
            string file = File.ReadAllText("Cod.txt") + "\0";
            //List<string> lines = new List<string>() { file };
            //int size = ReadFail("Cod.txt", lines);

            //foreach (var n in lines)
            //    Console.WriteLine(n);
            Console.WriteLine(file);

            CodeAnalysis analysis = new CodeAnalysis();
            analysis.StartAnalysis(file);
        }



        static int ReadFail(string pathToFile, List<string> lines)
        {
            string line = "0";
            int size = 0;
            try
            {
                StreamReader sr = new StreamReader(pathToFile);

                while (true)
                {
                    line = sr.ReadLine();
                    if (line == null)
                        break;
                    else
                        lines.Add(line);
                    size++;
                }
                //close the file
                sr.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.Message);
            }
            finally
            {
                Console.WriteLine("Executing finally block.");
            }
            return size;
        }
    }
}
