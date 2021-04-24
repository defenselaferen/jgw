#include "../include/CCM_Header.h"
#include "../include/ccm.h"

void input(std::string& refrench, std::string printS) {
    std::cout << printS;
    std::getline(std::cin, refrench);
}

typedef void (*voidFunction)();
typedef void (*voidFunctions)(std::vector<std::string>&);

std::array<std::string, 4> itsCommand = {
    "ls", "clear", "pwd", "exit"
};

std::array<std::string, 1> itsCommandSecond = {
    "cd"
};

std::array<std::string, 4> itsProgranREPL = {
    "node", "python3", "python", "zsh"
};

// including header for exec1
#include "../include/exec1.h"

// including header for exec2
#include "../include/exec2.h"

// including header ls
#include "../include/ls.h"

// including header for clear
#include "../include/clear.h"

// include header for pwd
#include "../include/pwd.h"

// include header for exit
#include "../include/exit.h"

// include header for cd
#include "../include/cd.h"

class itsProgram {
    private:
        bool run = false;
        std::map<std::string, voidFunction> myVoid;
        std::map<std::string, voidFunctions> myVoidParam;
        void Register() {
            this->myVoid["ls"] = ls;
            this->myVoid["clear"] = clear;
            this->myVoid["pwd"] = pwd;
            this->myVoid["exit"] = exit;

            this->myVoidParam["cd"] = cd;
        }
    public:
        itsProgram()
            : run(true) {
                this->Register();
            }
        void Take(std::string& exece) {
            if(this->run == false) {
                std::cout << "error" << std::endl;
                return;
            } else {
                bool itsCommands = false;
                int bct = 1;
                for(unsigned int i = 0; i < sizeof(itsCommand) / sizeof(std::string); i++) {
                    if(exece == itsCommand[i]) {
                        itsCommands = true;
                        bct = 1;
                    }
                }
                if(itsCommands == false) {
                    #ifdef _WIN32
                        std::vector<std::string> pwrt;
                    #else
                        std::vector<std::string> pwrt = {"NULL"};
                    #endif
                    #ifdef _WIN32
                    #else
                    int iSee = 0;
                    #endif
                    std::string _BufferExece = exece;
                    std::string delimiter = " ";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = _BufferExece.find(delimiter)) != std::string::npos) {
                        token = _BufferExece.substr(0, pos);
                        #ifdef _WIN32
                            pwrt.push_back(token);
                        #else
                            if(iSee == 0) {
                                pwrt[0] = token;
                                iSee += 1;
                            } else {
                                pwrt.push_back(token);
                            }
                        #endif
                        _BufferExece.erase(0, pos + delimiter.length());
                    }
                    pwrt.push_back(_BufferExece);
                    for(unsigned int i = 0; i < sizeof(std::string) / sizeof(itsCommandSecond); i++) {
                        if(pwrt[0] == itsCommandSecond[i]) {
                            itsCommands = true;
                            bct = 2;
                        }
                    }
                    if(bct == 2) {
                        this->myVoidParam[pwrt[0]](pwrt);
                    }
                }
                if(itsCommands == true) {
                    if(bct == 1) {
                        this->myVoid[exece]();
                    }
                    bct = 1;
                } else {
                    bool Its = false;
                    for(unsigned int i = 0; i < sizeof(itsProgranREPL) / sizeof(std::string); i++) {
                        if(itsProgranREPL[i] == exece) {
                            Its = true;
                            break;
                        }
                    }
                    if(Its == true) {
                        {
                            auto temp = system(exece.c_str());
                        }
                    } else {
                        bool runOk = false;
                        #include "../include/color.h"
                        try {
                            std::string _Buff = exec1(exece.c_str());
                            #ifdef _WIN32
                                getColor(14);
                            #else
                                getColor(_Buff, F_YELLOW);
                            #endif
                            std::cout << _Buff << std::endl;
                            #ifdef _WIN32
                                getColor(15);
                            #else
                                getColor(_Buff, reseting);
                            #endif
                            runOk = true;
                        } catch(...) {
                            try {
                                std::string _Buff = exec2(exece.c_str());
                                #ifdef _WIN32
                                    getColor(14);
                                #else
                                    getColor(_Buff, F_YELLOW);
                                #endif
                                std::cout << _Buff << std::endl;
                                #ifdef _WIN32
                                    getColor(15);
                                #else
                                    getColor(_Buff, reseting);
                                #endif
                                runOk = true;
                            } catch(...) {
                                runOk = false;
                            }
                        }
                        if(runOk == false) {
                            std::cout << "Error " << exece << std::endl;
                        }
                    }
                }
            }
        }
};

void ExecutableRun(std::string& command) {
    itsProgram* trdc = new itsProgram();
    trdc->Take(command);
}