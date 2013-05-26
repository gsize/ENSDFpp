/**\file VerbosePrinterEventEnabled.h
   \author Rikard Lundmark
   \brief Header file for the VerbosePrinterEventEnabled class.
*/
/**\file VerbosePrinterEventEnabled.cpp
   \author Rikard Lundmark
   \brief Source file for the VerbosePrinterEventEnabled class.
*/

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef STDARG_H
#define STDARG_H //!<Inclusion guard
#include <stdarg.h>
#endif

#include "VerbosePrinter.h"

#ifndef VERBOSEPRINTEREVENTENABLED_H
#define VERBOSEPRINTEREVENTENABLED_H
/**Classes using VerbosePrinter usually wants to implement this class.
   \author Rikard Lundmark
 */
class VerbosePrinterEventEnabled
{
 public:
  VerbosePrinterEventEnabled(); //!<Constructs the object.
  ~VerbosePrinterEventEnabled(); //!<Destroys the object.
  void registerListener(VerbosePrinter * Listener //!<The listener to register.
			);//!<Registers the VerbosePrinter listener with this object.
  void removeListener();  //!<Unregisters the listener.
 protected:
  VerbosePrinter * myPrinter; //!<Pointer to the registered VerbosePrinter, if any.
  bool vPrint(int verbosityLevel, //!<The verbosity level of this message. Used by the VerbosePrinter to determine if it should be printed or not.
	      const char* message, //!<The message to print.
	      ... //!<Any arguments to this message (like printf...).
	      ) const; //!<Called to print 
  void registerChild(VerbosePrinterEventEnabled * child //!<The child to add.
		     ); //!<Registers a child. If a VerbosePrinter is added, all children will also add it.
 private:
  list<VerbosePrinterEventEnabled *> children; //!<The registered children.
};
#endif
