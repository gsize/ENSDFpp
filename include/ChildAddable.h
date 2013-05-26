/**\file ChildAddable.h
   \author Rikard Lundmark
   \brief Contains the ChildAddable template.
   \ingroup Database
   \ingroup RecordWrappers
*/


/** @defgroup RecordWrappers Record wrappers
 * These classes are used for wrapping records appropriately, so that they can be added to the appropriate classes.
 */


using namespace std;

#ifndef LIST
#define LIST //!<Inclusion guard
#include <list>
#endif

#ifndef CHILDADDABLE_H
#define CHILDADDABLE_H //!<Inclusion guard.
/** Implemented by all classes which can have classes implementing Child added to them. Used by for example NormalizationRecord.
    \author Rikard Lundmark
    \ingroup Database
 */
template <class T> 
class ChildAddable
{
 public:
  ChildAddable() 
    {

    } //!< Constructor. Does nothing.

  ~ChildAddable() 
    {
      for(typename list<T*>::iterator it  = myChildren.begin(); it!=myChildren.end(); it++)
	{
	  (*it)->parentDestroyed();
	}
      myChildren.clear();
    }//!< Essentially tells all children that their parent was destroyed, and that they should forget about it.

  list<T*> getChildren() const
    {
      return myChildren;
    } //!< Returns a list of all children added.

  void addChild(T * childPtr) 
  {
    myChildren.push_back(childPtr);
  } //!< Adds a child.

  void removeChild(T * childPtr) 
  {
    myChildren.remove(childPtr);
  }//!< Removes a child.

  bool operator==(const ChildAddable<T> & rhs) const
  {
    for(typename list<T*>::const_iterator it = myChildren.begin(); it!=myChildren.end(); it++)
      {
	bool found = false;
	for(typename list<T*>::const_iterator ir = rhs.myChildren.begin(); ir!=rhs.myChildren.end(); ir++)
	  {
	    if(*ir!=NULL && *it!=NULL)
	      {
		//TODO:
		//compare objects, not pointers to objects.
		if(*ir==*it)
		  found = true;
	      }
	  }
	if(!found)
	  return false;
      }
    return true;
  }   //!<Equals operator
 protected:
  list<T*> myChildren; //!< The children currently added to this ChildAddable.
};
#endif
