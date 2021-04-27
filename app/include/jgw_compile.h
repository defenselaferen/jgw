#ifndef JGW_COMPILE_H
#define JGW_COMPILE_H

// micro variable
#define LengthPolar 60

// Function For Parser
char peek();
char get();
int expression();
int number();
int factor();
int term();
int expression();

// function for trim
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

class JGW_COMPILE {
private:
	// make variable settings
	std::string polar[LengthPolar] = {
		// Notes Array
		"Do1", "Re1", "Mi1",
		"Fa1", "So1", "La1",
		"Si1", 
		"Do2", "Re2", "Mi2",
		"Fa2", "So2", "La2",
		"Si2",
		"Do3", "Re3", "Mi3",
		"Fa3", "So3", "La3",
		"Si3",
		"Do4", "Re4", "Mi4",
		"Fa4", "So4", "La4",
		"Si4",
		"Do5", "Re5", "Mi5",
		"Fa5", "So5", "La5",
		"Si5",

		// Keys Array
		"K1_1", "K1_2", "K1_3",
		"K1_4", "K1_5",
		"K2_1", "K2_2", "K2_3",
		"K2_4", "K2_5",
		"K3_1", "K3_2", "K3_3",
		"K3_4", "K3_5",
		"K4_1", "K4_2", "K4_3",
		"K4_4", "K4_5",
		"K5_1", "K5_2", "K5_3",
		"K5_4", "K5_5",
	};
private:
	// function for split
	void splitFunctionOne(std::string& fillFile, std::vector<std::string>& allCode, std::string delimiter);

	// function start compile
	void StartCompile(std::string nameFile);
public:
	int main(int argc, const char** argv);
};

#endif // JGW_COMPILE_H