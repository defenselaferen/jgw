#include <iostream>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>

#include "../app/include/jgw_compile.h"
#include "../app/include/structure.h"
#include "../app/include/frequency.h"
#include "../app/include/fileshelp.h"

// make variable settings
const char* expressionToParse = "";
const std::string WHITESPACE = " \n\r\t\f\v";

int JGW_COMPILE::main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		StartCompile(argv[i]);
	}
	return 0;
}

void JGW_COMPILE::splitFunctionOne(std::string& fillFile, std::vector<std::string>& allCode, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	while ((pos = fillFile.find(delimiter)) != std::string::npos) {
	    token = fillFile.substr(0, pos);
	    allCode.push_back(token);
	    fillFile.erase(0, pos + delimiter.length());
	}
	allCode.push_back(fillFile);
}

void JGW_COMPILE::StartCompile(std::string nameFile)
{
	FILESHELP FSH_I(nameFile.c_str());

	std::string fillFile = FSH_I.getFile();
	std::vector<std::string> allCode;

	splitFunctionOne(fillFile, allCode, ",");

	for(int i = 0; i < allCode.size(); i += 2)
	{
		allCode[i] = trim(allCode[i]);
		std::vector<std::string> delimitu;

		splitFunctionOne(allCode[i], delimitu, " ");

		int sizelength = delimitu.size();
		freq f_FREQS(true);

		for(int j = 0; j < sizelength; j++)
		{
			for(int k = 0; k < LengthPolar; k++)
			{
				delimitu[j] = trim(delimitu[j]);
				if(delimitu[j] == trim(polar[k]))
				{
					#ifdef _DEV
						std::cout << i + 1<< ". " << delimitu[j] << " | " << f_FREQS.solf[polar[k]] << std::endl;
					#endif
					delimitu[j] = f_FREQS.solf[polar[k]];
					break;
				}
			}
		}

		std::string _BUFFER_S = "";
		for(int j = 0; j < delimitu.size(); j++)
		{
			_BUFFER_S += delimitu[j];
		}
		allCode[i] = _BUFFER_S;
	}

	for(int i = 0; i < allCode.size(); i+= 2)
	{
		char *cstr = new char[allCode[i].length() + 1];
		strcpy(cstr, allCode[i].c_str());
		expressionToParse = cstr;

		allCode[i] = std::to_string(expression());
	}

	int index_compile = 1;

	std::vector<compileSound> inCompileSound;
	
	double Temp_S_HZ;
	float Temp_D_DURATION;

	for(int i = 0; i < allCode.size(); i += 2)
	{
		if((Temp_D_DURATION == atof(allCode[i + 1].c_str())) &&
			(Temp_S_HZ == atof(allCode[i].c_str()))) {
			inCompileSound[((int)inCompileSound.size()) - 1].duplicate += 1;
		} else {
			compileSound cpls;
			cpls.S_HZ = atof(allCode[i].c_str());
			cpls.D_DURATION = atof(allCode[i + 1].c_str());

			Temp_S_HZ = atof(allCode[i].c_str());
			Temp_D_DURATION = atof(allCode[i + 1].c_str());

			inCompileSound.push_back(cpls);
			index_compile += 1;
		}
	}

	std::fstream outputFile;
	outputFile.open(nameFile + ".bnm", std::ios::trunc | std::ios::out | std::ios::binary);
	for(int i = 0; i < inCompileSound.size(); i++)
	{
		outputFile.write((char*)&inCompileSound[i], sizeof(compileSound));
	}
	outputFile.close();
}

char peek()
{
    return *expressionToParse;
}

char get()
{
    return *expressionToParse++;
}

int number()
{
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9')
    {
        result = 10*result + get() - '0';
    }
    return result;
}

int factor()
{
    if (peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '(')
    {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    }
    else if (peek() == '-')
    {
        get();
        return -factor();
    }
    return 0; // error
}

int term()
{
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

int expression()
{
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}