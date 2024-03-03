#ifndef PARSE_HPP
#define PARSE_HPP

#include "../../lib/rapidxml-1.13/rapidxml.hpp"
#include "Configuration.hpp"
#include "parse.hpp"

#include <string>

Configuration parseConfig(std::string filename);

#endif  // PARSE_HPP