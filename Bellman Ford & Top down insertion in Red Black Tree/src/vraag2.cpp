#include "rzwknoop.h"

int main() 
{
  // We beginnen met een eenvoudige boom 
  std::cout << "Boom 1: " << std::endl;
  RZWboom<int> boom;
  int punten[10] = {8,4,2,1,3,6,5,7,12, 10}; 
  for (int i:punten) {
    boom.voegtoe_topdown(i);
  }
  boom.schrijf(std::cout);
  boom.tekenAlsBinaireBoom("boom1.dot");

  // 2de boom die iets groter is
  std::cout << "Boom 2: " << std::endl;
  RZWboom<int> boom2;
	for (int i = 0; i < 100; i++)
	{
    boom2.voegtoe_topdown(i);
	}
  boom2.schrijf(std::cout);
  boom2.tekenAlsBinaireBoom("boom2.dot");

  std::cout << "Done" << std::endl;

  return 0;
}