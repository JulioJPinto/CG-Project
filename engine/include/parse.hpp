#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

#include "../../lib/rapidxml-1.13/rapidxml.hpp"
#include "Configuration.hpp"
#include "parse.hpp"

Configuration parseConfig(std::string filename);

Group parseGroup(rapidxml::xml_node<>* groupNode);

void parseTransform(rapidxml::xml_node<>* transformNode, Group& group);

void parseModels(rapidxml::xml_node<>* modelsNode, Group& group);

#endif  // PARSE_HPP