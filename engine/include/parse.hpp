#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

#include "Configuration.hpp"
#include "curves.hpp"
#include <rapidxml/rapidxml.hpp>

Configuration parseConfig(std::string filename);

Group parseGroup(rapidxml::xml_node<>* groupNode);

void parseTransform(rapidxml::xml_node<>* transformNode, Group& group);

void parseModels(rapidxml::xml_node<>* modelsNode, Group& group);

#endif  // PARSE_HPP