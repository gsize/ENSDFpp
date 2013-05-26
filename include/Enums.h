/**\file Enums.h
   \author Rikard Lundmark
   \brief Defines the enums DecayType and RecordType
*/

#ifndef ENUM_DECAYTYPE
#define ENUM_DECAYTYPE //!<Inclusion guard

/**
   Defines the different decay types we use.
   \author Rikard Lundmark
   \note Only BetaPlus and BetaMinus at the moment.
 */
enum DecayType
  {
    BetaMinus, //!<A beta minus decay.
    BetaPlus //!< A beta plus decay.
  }; 
#endif

#ifndef ENUM_RECORDTYPE
#define ENUM_RECORDTYPE
#include "DataFileException.h"

/**
   Defines the different record types in ENSDF.
   \author Rikard Lundmark
 */
enum RecordType
  {
    IdentificationRecord_=0, //!<Corresponds to IdentificationRecord.
    HistoryRecord_=1, //!<Corresponds to HistoryRecord.
    CrossReferenceRecord_=2, //!<Corresponds to CrossReferenceRecord.
    CommentRecord_=3, //!<Corresponds to CommentRecord.
    ParentRecord_=4, //!<Corresponds to ParentRecord.
    NormalizationRecord_=5, //!<Corresponds to NormalizationRecord.
    ProductionNormalizationRecord_=6, //!<Corresponds to ProductionNormalizationRecord.
    LevelRecord_=7, //!<Corresponds to LevelRecord.
    BetaMinusRecord_=8, //!<Corresponds to BetaMinusRecord.
    BetaPlusRecord_=9, //!<Corresponds to BetaPlusRecord.
    AlphaRecord_=10, //!<Corresponds to AlphaRecord.
    DelayedParticleRecord_=11, //!<Corresponds to DelayedParticleRecord.
    GammaRecord_=12, //!<Corresponds to GammaRecord.
    QValueRecord_=13 //!<Corresponds to QValueRecord.
  };


inline RecordType intToEnum(int toConvert/**<The int to conver to a RecordType enum*/)
{
  switch(toConvert)
    {
    case IdentificationRecord_:
      return IdentificationRecord_;
    case HistoryRecord_:
      return HistoryRecord_;
    case CrossReferenceRecord_:
      return CrossReferenceRecord_;
    case CommentRecord_:
      return CommentRecord_;
    case ParentRecord_:
      return ParentRecord_;
    case NormalizationRecord_:
      return NormalizationRecord_;
    case ProductionNormalizationRecord_:
      return ProductionNormalizationRecord_;
    case LevelRecord_:
      return LevelRecord_;
    case BetaMinusRecord_:
      return BetaMinusRecord_;
    case BetaPlusRecord_:
      return BetaPlusRecord_;
    case AlphaRecord_:
      return AlphaRecord_;
    case DelayedParticleRecord_:
      return DelayedParticleRecord_;
    case GammaRecord_:
      return GammaRecord_;
    case QValueRecord_:
      return QValueRecord_;
    }
  throw DataFileException("You have called with an invalid number");
}//!<Converts an integer to an enum of type RecordType. \throws DataFileException if the number didn't correspond to anything in the enum.
#endif
