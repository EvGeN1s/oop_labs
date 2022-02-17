// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается
// и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaseString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument exception\n";
		std::cout << "Usage Replace.exe <inputfile.txt> <outputfile.txt> <search string> <replace string>\n";
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaseString = argv[4];

	return args;
}


void ReplaceStringInStreams(std::ifstream& input, std::ofstream& output, std::string searchString, std::string replaceString)
{	std::string str;
    
	while (getline(input, str))
	{
		unsigned int currSearcgingStrPos = 0;

		for (unsigned int i = 0; i < str.size(); i++)
		{
			std::cout << searchString[0];
		
			if (str[i] == searchString[currSearcgingStrPos])
			{
				currSearcgingStrPos++;
			}
			else
			{
				output.put(str[i]);
			}
				
			if (currSearcgingStrPos > searchString.size() - 1)
			{
				output << replaceString;
				currSearcgingStrPos = 0;
			}
			
		}	
		output << "\n";
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	
	if (!args)
	{
		return 1;
	}

	std::ifstream input;
	input.open(args->inputFileName);
	

	if (!input.is_open())
	{
		std::cout << "Can't open file '" << args->inputFileName << "' for reading\n";
		return 1;
	}

	std::ofstream output;

	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Can't open file '" << args->outputFileName << " for writing'\n";
		return 1;
	}

	std::string searchingStr = args->searchString;
	std::string replaceStr = args->replaseString;
	
	ReplaceStringInStreams(input, output, searchingStr, replaceStr);

	if (input.bad())
	{
		std::cout << "Failed to read inforamtion from file";
		return 1;
	}
	   
	if (!output.flush())
	{
		std::cout << "Failed to put information into file";
		return 1;
	}
	return 0;
}
