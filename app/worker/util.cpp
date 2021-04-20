#ifdef __cplusplus
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <ios>
    #include <cstring>
#endif

#include "../include/util.h"
#include "../include/helper.h"

char* read_file(const char* _PATH_) {
	std::fstream FILE_F;
    std::string _TEMP_, _BUFF_;
    FILE_F.open((std::string)_PATH_, std::ios::in);

    /* CHECK */
    switch(IF_T(!FILE_F.is_open()))
    {
        case IF_TRUE:
        {
            std::cout << "Can't open file: " << _PATH_ << std::endl;
        }
        break;
    }

    {
        bool itsFirst = true;
        while(!FILE_F.eof()) {
            getline(FILE_F, _TEMP_);
            /* CHECK */
            switch(IF_T(_TEMP_ != " "))
            {
                case IF_TRUE:
                {
                    switch(IF_T(itsFirst))
                    {
                        case IF_TRUE:
                        {
                            _BUFF_ += _TEMP_;
                            itsFirst = false;
                        }
                        break;
                        case IF_FALSE:
                        {
                            _BUFF_ += '\n' + _TEMP_;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    
    FILE_F.close();

    /* TODO: return char* */
    char* _TEMP_CHAR = new char[_BUFF_.length() + 1];

    /*
     * Old script
     *
     * strcpy_s(_TEMP_CHAR, _BUFF_.length() + 1, _BUFF_.c_str());
     * _strupr_s(_TEMP_CHAR, _BUFF_.length() + 1);
     *
     */
    strcpy(_TEMP_CHAR, _BUFF_.c_str());

    return _TEMP_CHAR;
}