// Courtesy of Daniel Elliott
#include <string>

struct Gadget 
{
  std::string name;
  int age;
  std::string city;
};

class Widget 
{
  public:
  //this will get called by constructor 2
  Widget(Gadget&& gadget) : myGadget(std::move(gadget)){}

  //Constructor 2: Calls Constructor 1 with a Immediately invoked lambda
  // makes a Gadget from the arguments. Can do complicated stuff in lambda
  // even before constructor body is entered.
  Widget(std::string name, int age, std::string city ) : Widget(
        [&]()
        {
            Gadget tmpGadget {name, age, city};
            return tmpGadget;
        }()
  ){}

  private :
  Gadget myGadget;
};

