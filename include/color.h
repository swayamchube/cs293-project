#ifndef _COLOR_INCLUDED_
#define _COLOR_INCLUDED_
#include "simplecpp"

namespace simplecpp{
class COLR{
protected:
	std::map<std::string, glm::vec3> clr;
	std::map<std::string, glm::vec3> :: iterator it;
public:
    COLR();
		void init();
		
		glm::vec3 getColor(std::string c);

};

}

#endif
