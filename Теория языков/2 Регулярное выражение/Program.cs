using System;
using System.Text.RegularExpressions;
using System.IO;

namespace RegexAnalysis
{
	class Program
	{
		static void ErrorProcessing(int index, string str)
		{
			int potpositionInLine = 1;
			int numberLines = 0;

			for (int i = 0; i < str.Length && i < index; i++)
			{
				if (str[i] == '\n')
				{
					numberLines++;
					potpositionInLine = 0;
				}
				potpositionInLine++;
			}
			Error(numberLines, potpositionInLine);
		}

		static void Error(int numberLines, int potpositionInLine)
		{
			throw new AccessViolationException("ошибка в " + (numberLines + 1).ToString() + " строке" + " в " + (potpositionInLine).ToString() + " позиции");
		}

		//Удаляет пробелы, переносы строки, табуляцию в конце текста
		static string DeleteTheLastSpaces(string str)
		{
			for (int i = str.Length - 1; i >= 0; i--)
				if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\r')
					str = str.Substring(0, str.Length - 1);
				else
					break;

			return str;
		}

		static void Main(string[] args)
		{
			string regular = File.ReadAllText("regex.txt");
			string str = File.ReadAllText("str.txt");

			DeleteTheLastSpaces(str);

			Regex regex = new Regex(@regular);
			MatchCollection matches = regex.Matches(str);

			AllVariables variables = new AllVariables();

			foreach (Match m in matches)
			{
				if (m.Groups["error"].Captures.Count > 0)
					ErrorProcessing(m.Groups["error"].Captures[0].Index, str);

				int index = variables.Variables(m);

				if (index != -1)
					ErrorProcessing(index, str);
			}
			Console.WriteLine("OK");
		}
	}
}
