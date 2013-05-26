/**\file Child.h
   \author Rikard Lundmark
   \brief Contains the Child template.
   \ingroup Database
   \ingroup RecordWrappers
*/

using namespace std;

#ifndef NULL //!<Define if undefined.
#define NULL 0
#endif

#ifndef CHILD_H
#define CHILD_H //!<Inclusion guard.
template <class T>
/** Implemented by all classes which are children that can be added to ChildAddable.
    \author Rikard Lundmark
    \ingroup Database
*/
class Child
{
 public:
  Child(T * toSet)
    {
      myT = toSet;
      if(myT!=NULL)
	myT->addChild(this);
    } //!<Constructor, registers the Child with the ChildAddable if the ChildAddable is not NULL.

  ~Child()
    {
      if(myT!=NULL)
	myT->removeChild(this);
      myT=NULL;
    } //!<Destructor, unregisters the Child with the ChildAddabe if the ChildAddable is not NULL.

  virtual T * getChildAddable() const
  {
    return myT;
  } //!< Returns the ChildAddable associated with this Child.
  
  void parentDestroyed()
  {
    myT = NULL;
  } //!< Called by the ChildAddable with which this Child is associated, if the ChildAddable is destroyed. It instructs this Child to forget that it had a ChildAddable.

  bool operator== (const T& rhs) const
  {
    if((myT!=NULL) && rhs.myT==NULL)
      return false;
    if((myT==NULL) && rhs.myT!=NULL)
      return false;
    if(myT==NULL && rhs.myT==NULL)
      return true;
    if(myT!=NULL && rhs.myT!=NULL)
      return *myT==*(rhs.myT);
  } //!< Equals operator.
  
 private:
  T * myT; //!< The ChildAddable object associated with this Child.
};
#endif
