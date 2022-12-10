using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace RegexAnalysis
{
	class VariableIndex
	{
		public string variable = null;
		public int index = -1;

		public VariableIndex(string v, int i)
		{
			variable = v;
			index = i;
		}
	}

	class AllVariables
	{
		private List<string> arrayVariables;
		private string[] typeVariables = {
			"sbyte", "short", "int", "long", "byte", "ushort", "uint", "ulong", "float", "double",
			"decimal", "bool", "char", "string", "object"};

		public AllVariables()
		{
			arrayVariables = new List<string>();
		}

		//если -1 нет ошибок, иначе ошибка в возврвшаемом индексе индексе
		public int Variables(Match match)
		{
			var newVariables = new List<VariableIndex>();

			//для первой переменной
			if (match.Groups["VariableName"].Value.Length > 0)
				newVariables.Add(new VariableIndex(FirstVariables(match),
												   match.Groups["VariableName"].Index));

			for (int i = 0; i < match.Groups["Name"].Captures.Count; i++)
				newVariables.Add(new VariableIndex(match.Groups["Name"].Captures[i].Value,
												   match.Groups["Name"].Captures[i].Index));

			return CheckVariebles(newVariables);
		}

		//Обработка первой переменной в строке, на присутствие '@'
		private string FirstVariables(Match match)
		{
			var GroupBracketsQuestionsDog = match.Groups["Array"];
			var variableName = match.Groups["VariableName"].Value;

			if (GroupBracketsQuestionsDog.Captures.Count > 0 && GroupBracketsQuestionsDog.Value.Length > 0)
				if (GroupBracketsQuestionsDog.Value[GroupBracketsQuestionsDog.Value.Length - 1] == '@')
					variableName = "@" + variableName;

			return variableName;
		}

		//Проверяет на неповторение
		private int CheckVariebles(List<VariableIndex> newVariables)
		{
			foreach (var variable in newVariables)
			{
				if (variable.variable[0] == '@')
				{
					variable.variable = variable.variable.Remove(0, 1);
					variable.index++;
				}
				else
				{
					if (Array.IndexOf(typeVariables, variable.variable) != -1)
						return variable.index;
				}

				if (arrayVariables.IndexOf(variable.variable) == -1)
					arrayVariables.Add(variable.variable);
				else
					return variable.index;
			}

			return -1;
		}
	}
}
