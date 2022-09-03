/**
 * movie2.cpp
 * 2022-06-01 K.OHWADA
 */

// Selecting data from XML using XPath  
// original : https://github.com/PacktPublishing/The-Modern-Cpp-Challenge/blob/master/Chapter09/problem_74/main.cpp

#include <iostream>
#include <string>
#include "pugixml.hpp"


/**
 * xml_text
 */
   std::string xml_text = R"(
<?xml version="1.0"?>
<movies>
	<movie id="11001" title="The Matrix" year="1999" length="196">
		<cast>
			<role star="Keanu Reeves" name="Neo" />
			<role star="Laurence Fishburne" name="Morpheus" />
			<role star="Carrie-Anne Moss" name="Trinity" />
			<role star="Hugo Weaving" name="	Agent Smith" />
		</cast>
		<directors>
			<director name="Lana Wachowski" />
			<director name="Lilly Wachowski" />
		</directors>
		<writers>
			<writer name="Lana Wachowski" />
			<writer name="Lilly Wachowski" />
		</writers>
	</movie>
	<movie id="9871" title="Forrest Gump" year="1994" length="202">
		<cast>
			<role star="Tom Hanks" name="Forrest Gump" />
			<role star="Sally Field" name="Mrs. Gump" />
			<role star="Robin Wright" name="Jenny Curran" />
			<role star="Mykelti Williamson" name="Bubba Blue" />
		</cast>
		<directors>
			<director name="Robert Zemeckis" />
		</directors>
		<writers>
			<writer name="Winston Groom" />
			<writer name="Eric Roth" />
		</writers>
	</movie>
</movies>
)";


/**
 * main
 */
int main()
{

const pugi::xpath_query  XPATH1("/movies/movie[@year>1995]");

const pugi::xpath_query  XPATH2("/movies/movie/cast/role[last()]");

   pugi::xml_document doc;
   if (doc.load_string(xml_text.c_str()))
   {
      try
      {
         auto titles = doc.select_nodes(XPATH1);

         for (auto it : titles)
         {
            std::cout << it.node().attribute("title").as_string() << std::endl;
         }
      }
      catch (pugi::xpath_exception const & e)
      {
         std::cout << e.result().description() << std::endl;
      }

      try
      {
         auto titles = doc.select_nodes(XPATH2);

         for (auto it : titles)
         {
            std::cout << it.node().attribute("star").as_string() << std::endl;
         }
      }
      catch (pugi::xpath_exception const & e)
      {
         std::cout << e.result().description() << std::endl;
      }
   }

	return 0;
}

// The Matrix
// Hugo Weaving
// Mykelti Williamson
