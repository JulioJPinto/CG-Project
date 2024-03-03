#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

#include "../../lib/rapidxml-1.13/rapidxml.hpp"
#include "Configuration.hpp"
#include "parse.hpp"

Configuration parseConfig(std::string filename);

#endif  // PARSE_HPP