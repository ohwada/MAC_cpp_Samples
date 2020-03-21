/**
 * RawLoader Sample
 * 2020-02-01 K.OHWADA
 */

#include <string>

#include "parse_filename.hpp"


bool parse_raw_file_param(std::string filename, int &width, int &height, bool &alphaFlag);

std::vector<std::string> split(std::string str, char del);

int str2i(std::string str);

