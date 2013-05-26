#include "VerbosePrinterEventEnabled.h"

VerbosePrinterEventEnabled::VerbosePrinterEventEnabled()
{
  myPrinter = NULL;
}

VerbosePrinterEventEnabled::~VerbosePrinterEventEnabled()
{
  removeListener();
}

void VerbosePrinterEventEnabled::registerListener(VerbosePrinter * Listener)
{
  myPrinter = Listener;
  if(myPrinter!=NULL)
    {
      myPrinter->registerConnectedEventClass(this);
    }
  for(list<VerbosePrinterEventEnabled *>::iterator it = children.begin(); it!=children.end(); it++)
    {
      if((*it)!=NULL)
	(*it)->registerListener(Listener);
    }
}

void VerbosePrinterEventEnabled::removeListener()
{
  if(myPrinter!=NULL)
    {
      myPrinter->unRegisterConnectedEventClass(this);
    }
  myPrinter = NULL;
}

void VerbosePrinterEventEnabled::registerChild(VerbosePrinterEventEnabled * child)
{
  children.push_back(child);
}

bool VerbosePrinterEventEnabled::vPrint(int verbosityLevel, const char* message, ...) const
{
  if(myPrinter!=NULL)
    {
      va_list args;
      va_start(args, message);
      myPrinter->va_print(verbosityLevel, message, args);
      va_end(args);
      return true;
    }
  return false;
}
