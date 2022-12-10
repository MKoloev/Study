using System;
using System.Collections.Generic;
using NUnit.Framework;
using System.Text;


namespace xDlars
{

	[TestFixture]
	public class CodeAnalysisTests
	{
		[TestCase(" i", 0, 0)]
		public void TestStatusDefinitions(string line, int currentSymbol, int stateNumber)
		{
			State state = new State();
			CodeAnalysis analysis = new CodeAnalysis();
			Assert.AreEqual(analysis.StatusDefinitions(line, ref currentSymbol, state), stateNumber);
		}
	}


	class ExternalMethods
	{
		private List<StringBuilder> arrayVariables;
		private int positionVariables;
		
		public ExternalMethods()
		{
			arrayVariables = new List<StringBuilder>();
			positionVariables = 0;
		}

		public bool methodA(int numbeMethod, string symbool)
		{
			if (numbeMethod == 1)
				return A1(symbool);
			else
				return A2();
		}


		private bool A1(string symbool)
		{
			if (arrayVariables.Count == positionVariables)
				arrayVariables.Add(new StringBuilder(symbool));
			else
				arrayVariables[positionVariables].Append(symbool);
			return true;
		}

		private bool A2()
		{
		   // positionVariables++;
		   // return -1 == arrayVariables.IndexOf(arrayVariables[positionVariables], 0, positionVariables - 1);
			//arrayVariables.IndexOf(arrayVariables[positionVariables], 0, positionVariables)
			for (int i = 0; i < arrayVariables.Count - 1; i++)
			{
				if (0 == string.Compare(arrayVariables[i].ToString(), arrayVariables[positionVariables].ToString()))
					return false;
			}
			positionVariables++;
			return true;
		}
	}



	class CodeAnalysis
	{
		private void ErrorProcessing(int numberLines, int potpositionInLine)
		{
			throw new AccessViolationException("ошибка в " + (numberLines + 1).ToString() + " строке" + " в " + (potpositionInLine + 1).ToString() + " позиции");
		}

		public bool StartAnalysis(string lines)
		{
			int q = 0;
			int indexAlphabet = -1;
			State state = new State();
			ExternalMethods variables = new ExternalMethods();
			
			int lineNumber = 0;
			int linePosicion = 0;

			for (int i = 0; indexAlphabet != state.countState - 1; i++)
			{
				if (lines[i] == '\n')
				{
					lineNumber++;
					linePosicion = i;
				}
				int position = i;
				indexAlphabet = StatusDefinitions(lines, ref i, state);

				if (indexAlphabet == -1)
					ErrorProcessing(lineNumber, position - linePosicion - 1);

				if (!TransitionVerification(ref q, indexAlphabet, state, variables, lines.Substring(position, i - position + 1)))
					ErrorProcessing(lineNumber, position - linePosicion - 1);


				Console.WriteLine(indexAlphabet);
			}

			/*
			for (int i = 0; i < lines.Count; i++)
			{
				for (int j = 0; j < lines[i].Length; j++)
				{
					int positionJ = j;
					indexAlphabet = StatusDefinitions(lines[i], ref j, state);

					if (indexAlphabet == 14 && q == 0)
						break;

					if(indexAlphabet == 14 || indexAlphabet == -1)
							ErrorProcessing(i, positionJ);

					if (!TransitionVerification(ref q, indexAlphabet, state, variables, lines[i].Substring(positionJ, j - positionJ + 1)))
						ErrorProcessing(i, positionJ);


					Console.WriteLine(indexAlphabet);
				}
				if (indexAlphabet == 14 && q == 0)
					break;
			}*/


			return true;
		}


		public int StatusDefinitions(string line, ref int currentSymbol, State state)
		{
			int indexAlphabet = -1;
			for (int i = 0; i < state.rangeString.Length; i++)
			{
				foreach (var typeState in state.rangeString[i])
				{
					if (typeState.Length > 1 && typeState[1] == '-')
					{
						if ((int)typeState[0] <= (int)line[currentSymbol] && (int)typeState[2] >= (int)line[currentSymbol])
							indexAlphabet = i;
					}
					else if (typeState.Length == 1)
					{
						if (typeState[0] == line[currentSymbol])
							indexAlphabet = i;
					}
					else
					{
						if (typeState[0] == line[currentSymbol] && ((line.Length - currentSymbol) >= typeState.Length))
						{
							if (0 == string.Compare(typeState, line.Substring(currentSymbol, typeState.Length)))
							{
								indexAlphabet = i;
								currentSymbol += (typeState.Length - 1);
							}
						}
					}
				}
			}
			return indexAlphabet;
		}


		public bool TransitionVerification(ref int q, int stateNumberl, State state, ExternalMethods variables, string symbool)
		{
			bool output = true;
			if (state.delta[q, stateNumberl, 0] == -1)
				return false;
			else
			{
				if (state.delta[q, stateNumberl, 1] != 0)
					output =  variables.methodA(state.delta[q, stateNumberl, 1], symbool);
				q = state.delta[q, stateNumberl, 0];
			}
			return output;
		}

	}

}
