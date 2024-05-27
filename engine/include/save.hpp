#ifndef SAVE_HPP
#define SAVE_HPP

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_ext.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include "parse.hpp"
#include "Camera.hpp"

void savetoFile(std::string original_scene, const Camera& cam);

#endif
