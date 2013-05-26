#This is a makefile for compiling the ENSDF analyzing program and supplementary software.
#This makefile also specifies how the solution should be deployed to a server at Chalmers, using specific login details.
#(c) Rikard Lundmark 2011-2013. All rights reserved.

SHELL = /bin/sh

SRCDIR = source

INCDIR = include

TSTDIR = test

TSTSRCDIR = source

TSTINCDIR = include

BINDIR = bin

CC = g++ -Wl,--no-as-needed

CFLAGS = -lpthread -Wall -g -rdynamic -I $(INCDIR)

CFINALFLAGS = $(CFLAGS)

COPTIMIZEFLAGS = -lpthread -Wall -O3  -funroll-loops -I $(INCDIR)

CTESTFLAGS = -lpthread -Wall -g -rdynamic -I $(TSTDIR)/$(TSTINCDIR) -I $(INCDIR)

REMOTEADDR = friedel-o.fy.chalmers.se

WEBADDR = remote3.student.chalmers.se

RECORD=$(BINDIR)/AlphaRecord.o $(BINDIR)/BetaMinusRecord.o $(BINDIR)/BetaPlusRecord.o $(BINDIR)/BetaRecordWrapper.o $(BINDIR)/CommentRecord.o $(BINDIR)/CrossReferenceRecord.o $(BINDIR)/DelayedParticleRecord.o $(BINDIR)/GammaRecord.o $(BINDIR)/HistoryRecord.o $(BINDIR)/IdentificationRecord.o $(BINDIR)/LevelRecordChildrenWrapper.o $(BINDIR)/LevelRecord.o $(BINDIR)/NormalizationRecord.o $(BINDIR)/ParentRecord.o $(BINDIR)/ParentRecordChildrenWrapper.o $(BINDIR)/ProductionNormalizationRecord.o $(BINDIR)/QValueRecordChildrenWrapper.o $(BINDIR)/QValueRecord.o $(BINDIR)/Record.o $(BINDIR)/ReferenceRecord.o $(BINDIR)/NormalizationRecordChildrenWrapper.o


#Also automatically run the unit tests after making the files, of course.
all: directory ENSDF++ $(BINDIR)/RunTests MassPrinter ParticleInstablePrinter BetaStablePrinter
	$(BINDIR)/./RunTests
#	$(BINDIR)/./DataFileException_TEST.t
#	$(BINDIR)/./Isotop_TEST.t
#	$(BINDIR)/./Dataset_TEST.t
#	$(BINDIR)/./ENSDF_TEST.t
#	$(BINDIR)/./Record_TEST.t


directory: 
	+ (mkdir -p $(BINDIR))

#The maximum optimization... not for testing, no unit tests are compiled or executed. 
optimize: $(INCDIR)/Enums.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h $(INCDIR)/AlphaRecord.h $(INCDIR)/BetaMinusRecord.h $(INCDIR)/BetaPlusRecord.h $(INCDIR)/BetaRecordWrapper.h $(INCDIR)/CommandLineArgument.h $(INCDIR)/CommandLineException.h $(INCDIR)/CommandLineInterpreter.h $(INCDIR)/CommentRecord.h $(INCDIR)/CrossReferenceRecord.h $(INCDIR)/DataFileException.h $(INCDIR)/DataQueryBetaGamma.h $(INCDIR)/DataQuery.h $(INCDIR)/DataQueryIsomer.h $(INCDIR)/Dataset.h $(INCDIR)/DelayedParticleRecord.h $(INCDIR)/ElementLookupTable.h $(INCDIR)/ENSDF.h $(INCDIR)/ENSDFProcessor.h $(INCDIR)/GammaRecord.h $(INCDIR)/HistoryRecord.h $(INCDIR)/IdentificationRecord.h $(INCDIR)/InterestingDecayBetaGamma.h $(INCDIR)/InterestingDecay.h $(INCDIR)/InterestingDecayIsomer.h $(INCDIR)/Isotop.h $(INCDIR)/LevelRecordChildrenWrapper.h $(INCDIR)/LevelRecord.h $(INCDIR)/Main.h $(INCDIR)/MassObject.h $(INCDIR)/NormalizationRecord.h $(INCDIR)/Nukleid.h $(INCDIR)/ParentRecordChildrenWrapper.h $(INCDIR)/ParentRecord.h $(INCDIR)/ProductionNormalizationRecord.h $(INCDIR)/QValueRecordChildrenWrapper.h $(INCDIR)/QValueRecord.h $(INCDIR)/Record.h $(INCDIR)/ReferenceRecord.h $(INCDIR)/VerbosePrinter.h $(INCDIR)/VerbosePrinterEventEnabled.h $(INCDIR)/MassTable.h $(INCDIR)/NormalizationRecordChildrenWrapper.h $(SRCDIR)/AlphaRecord.cpp $(SRCDIR)/BetaMinusRecord.cpp $(SRCDIR)/BetaPlusRecord.cpp $(SRCDIR)/BetaRecordWrapper.cpp $(SRCDIR)/CommandLineArgument.cpp $(SRCDIR)/CommandLineException.cpp $(SRCDIR)/CommandLineInterpreter.cpp $(SRCDIR)/CommentRecord.cpp $(SRCDIR)/CrossReferenceRecord.cpp $(SRCDIR)/DataFileException.cpp $(SRCDIR)/DataQueryBetaGamma.cpp $(SRCDIR)/DataQuery.cpp $(SRCDIR)/DataQueryIsomer.cpp $(SRCDIR)/Dataset.cpp $(SRCDIR)/DelayedParticleRecord.cpp $(SRCDIR)/ElementLookupTable.cpp $(SRCDIR)/ENSDF.cpp $(SRCDIR)/ENSDFProcessor.cpp $(SRCDIR)/GammaRecord.cpp $(SRCDIR)/HistoryRecord.cpp $(SRCDIR)/IdentificationRecord.cpp $(SRCDIR)/InterestingDecayBetaGamma.cpp $(SRCDIR)/InterestingDecay.cpp $(SRCDIR)/InterestingDecayIsomer.cpp $(SRCDIR)/Isotop.cpp $(SRCDIR)/LevelRecordChildrenWrapper.cpp $(SRCDIR)/LevelRecord.cpp $(SRCDIR)/Main.cpp $(SRCDIR)/MassObject.cpp $(SRCDIR)/NormalizationRecord.cpp $(SRCDIR)/Nukleid.cpp $(SRCDIR)/ParentRecordChildrenWrapper.cpp $(SRCDIR)/ParentRecord.cpp $(SRCDIR)/ProductionNormalizationRecord.cpp $(SRCDIR)/QValueRecordChildrenWrapper.cpp $(SRCDIR)/QValueRecord.cpp $(SRCDIR)/Record.cpp $(SRCDIR)/ReferenceRecord.cpp $(SRCDIR)/VerbosePrinter.cpp $(SRCDIR)/VerbosePrinterEventEnabled.cpp $(SRCDIR)/MassTable.cpp $(SRCDIR)/NormalizationRecordChildrenWrapper.cpp
	$(CC) $(COPTIMIZEFLAGS) $(SRCDIR)/AlphaRecord.cpp $(SRCDIR)/BetaMinusRecord.cpp $(SRCDIR)/BetaPlusRecord.cpp $(SRCDIR)/BetaRecordWrapper.cpp $(SRCDIR)/CommandLineArgument.cpp $(SRCDIR)/CommandLineException.cpp $(SRCDIR)/CommandLineInterpreter.cpp $(SRCDIR)/CommentRecord.cpp $(SRCDIR)/CrossReferenceRecord.cpp $(SRCDIR)/DataFileException.cpp $(SRCDIR)/DataQueryBetaGamma.cpp $(SRCDIR)/DataQuery.cpp $(SRCDIR)/DataQueryIsomer.cpp $(SRCDIR)/Dataset.cpp $(SRCDIR)/DelayedParticleRecord.cpp $(SRCDIR)/ElementLookupTable.cpp $(SRCDIR)/ENSDF.cpp $(SRCDIR)/ENSDFProcessor.cpp $(SRCDIR)/GammaRecord.cpp $(SRCDIR)/HistoryRecord.cpp $(SRCDIR)/IdentificationRecord.cpp $(SRCDIR)/InterestingDecayBetaGamma.cpp $(SRCDIR)/InterestingDecay.cpp $(SRCDIR)/InterestingDecayIsomer.cpp $(SRCDIR)/Isotop.cpp $(SRCDIR)/LevelRecordChildrenWrapper.cpp $(SRCDIR)/LevelRecord.cpp $(SRCDIR)/Main.cpp $(SRCDIR)/MassObject.cpp $(SRCDIR)/NormalizationRecord.cpp $(SRCDIR)/Nukleid.cpp $(SRCDIR)/ParentRecordChildrenWrapper.cpp $(SRCDIR)/ParentRecord.cpp $(SRCDIR)/ProductionNormalizationRecord.cpp $(SRCDIR)/QValueRecordChildrenWrapper.cpp $(SRCDIR)/QValueRecord.cpp $(SRCDIR)/Record.cpp $(SRCDIR)/ReferenceRecord.cpp $(SRCDIR)/VerbosePrinter.cpp $(SRCDIR)/VerbosePrinterEventEnabled.cpp $(SRCDIR)/MassTable.cpp $(SRCDIR)/NormalizationRecordChildrenWrapper.cpp -o ENSDF++

optimizedeploy: optimize
	+ make upload
	@ echo 'Remote compiling at' $(REMOTEADDR)
	@ (./portknock.sh $(REMOTEADDR) && ssh -l riklund $(REMOTEADDR) 'make optimize -j 5');


#The main program
ENSDF++: $(RECORD) $(BINDIR)/Dataset.o $(BINDIR)/ENSDF.o $(BINDIR)/Isotop.o $(BINDIR)/Main.o $(BINDIR)/Nukleid.o $(BINDIR)/DataFileException.o $(BINDIR)/DataQuery.o $(BINDIR)/DataQueryBetaGamma.o $(BINDIR)/DataQueryIsomer.o $(BINDIR)/InterestingDecay.o $(BINDIR)/InterestingDecayBetaGamma.o $(BINDIR)/InterestingDecayIsomer.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/CommandLineInterpreter.o $(BINDIR)/CommandLineArgument.o $(BINDIR)/ENSDFProcessor.o $(BINDIR)/CommandLineException.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o 
	$(CC) $(CFINALFLAGS) $(RECORD) $(BINDIR)/Dataset.o $(BINDIR)/ENSDF.o $(BINDIR)/Isotop.o $(BINDIR)/Main.o $(BINDIR)/Nukleid.o $(BINDIR)/DataFileException.o $(BINDIR)/DataQuery.o $(BINDIR)/DataQueryBetaGamma.o $(BINDIR)/DataQueryIsomer.o $(BINDIR)/InterestingDecay.o $(BINDIR)/InterestingDecayBetaGamma.o $(BINDIR)/InterestingDecayIsomer.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/CommandLineInterpreter.o $(BINDIR)/CommandLineArgument.o $(BINDIR)/ENSDFProcessor.o $(BINDIR)/CommandLineException.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o -o ENSDF++


MassPrinter: $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/MassPrinter.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o
	$(CC) $(CFINALFLAGS) $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/MassPrinter.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o -o MassPrinter

ParticleInstablePrinter: $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/ParticleInstablePrinter.o $(BINDIR)/HalfLifeEstimator.o
	$(CC) $(CFINALFLAGS) $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/ParticleInstablePrinter.o $(BINDIR)/HalfLifeEstimator.o -o ParticleInstablePrinter 

BetaStablePrinter: $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/BetaStablePrinter.o $(BINDIR)/HalfLifeEstimator.o
	$(CC) $(CFINALFLAGS) $(BINDIR)/MassTable.o $(BINDIR)/MassObject.o $(BINDIR)/DataFileException.o $(BINDIR)/Nukleid.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/BetaStablePrinter.o $(BINDIR)/HalfLifeEstimator.o -o BetaStablePrinter


unique: $(SRCDIR)/Unique.cpp $(INCDIR)/Unique.h
	$(CC) $(COPTIMIZEFLAGS) $(SRCDIR)/Unique.cpp -o unique



$(BINDIR)/RunTests: $(TSTDIR)/$(TSTSRCDIR)/RunTests.cpp $(TSTDIR)/$(TSTINCDIR)/RunTests.h $(BINDIR)/DataFileException.o $(BINDIR)/DataFileException_TEST.o $(RECORD) $(BINDIR)/Dataset.o $(BINDIR)/Isotop.o $(BINDIR)/Nukleid.o $(BINDIR)/Isotop_TEST.o $(BINDIR)/ENSDF_TEST.o $(BINDIR)/ENSDF.o $(BINDIR)/Record_TEST.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/Dataset_TEST.o $(BINDIR)/GenericUnitTest.o
	$(CC) $(CTESTFLAGS) $(TSTDIR)/$(TSTSRCDIR)/RunTests.cpp $(TSTDIR)/$(TSTINCDIR)/RunTests.h $(BINDIR)/DataFileException.o $(BINDIR)/DataFileException_TEST.o $(RECORD) $(BINDIR)/Dataset.o $(BINDIR)/Isotop.o $(BINDIR)/Nukleid.o $(BINDIR)/Isotop_TEST.o $(BINDIR)/ENSDF_TEST.o $(BINDIR)/Record_TEST.o $(BINDIR)/ElementLookupTable.o $(BINDIR)/VerbosePrinter.o $(BINDIR)/VerbosePrinterEventEnabled.o $(BINDIR)/Dataset_TEST.o $(BINDIR)/GenericUnitTest.o $(BINDIR)/ENSDF.o -o $(BINDIR)/RunTests



$(BINDIR)/HalfLifeEstimator.o: $(SRCDIR)/HalfLifeEstimator.cpp $(INCDIR)/HalfLifeEstimator.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/HalfLifeEstimator.cpp -o $(BINDIR)/HalfLifeEstimator.o

$(BINDIR)/AlphaRecord.o: $(SRCDIR)/AlphaRecord.cpp $(INCDIR)/AlphaRecord.h $(INCDIR)/Child.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/AlphaRecord.cpp -o $(BINDIR)/AlphaRecord.o

$(BINDIR)/BetaMinusRecord.o: $(SRCDIR)/BetaMinusRecord.cpp $(INCDIR)/BetaMinusRecord.h $(INCDIR)/Child.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/BetaMinusRecord.cpp -o $(BINDIR)/BetaMinusRecord.o

$(BINDIR)/BetaPlusRecord.o: $(SRCDIR)/BetaPlusRecord.cpp $(INCDIR)/BetaPlusRecord.h $(INCDIR)/Child.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/BetaPlusRecord.cpp -o $(BINDIR)/BetaPlusRecord.o

$(BINDIR)/BetaRecordWrapper.o: $(SRCDIR)/BetaRecordWrapper.cpp $(INCDIR)/BetaRecordWrapper.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/BetaRecordWrapper.cpp -o $(BINDIR)/BetaRecordWrapper.o

$(BINDIR)/DataQuery.o: $(SRCDIR)/DataQuery.cpp $(INCDIR)/DataQuery.h $(INCDIR)/Enums.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DataQuery.cpp -o $(BINDIR)/DataQuery.o

$(BINDIR)/DataQueryBetaGamma.o: $(SRCDIR)/DataQueryBetaGamma.cpp $(INCDIR)/DataQueryBetaGamma.h $(INCDIR)/Enums.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DataQueryBetaGamma.cpp -o $(BINDIR)/DataQueryBetaGamma.o

$(BINDIR)/DataQueryIsomer.o: $(SRCDIR)/DataQueryIsomer.cpp $(INCDIR)/DataQueryIsomer.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DataQueryIsomer.cpp -o $(BINDIR)/DataQueryIsomer.o

$(BINDIR)/CommentRecord.o: $(SRCDIR)/CommentRecord.cpp $(INCDIR)/CommentRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommentRecord.cpp -o $(BINDIR)/CommentRecord.o

$(BINDIR)/CrossReferenceRecord.o: $(SRCDIR)/CrossReferenceRecord.cpp $(INCDIR)/CrossReferenceRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CrossReferenceRecord.cpp -o $(BINDIR)/CrossReferenceRecord.o

$(BINDIR)/DataFileException.o: $(SRCDIR)/DataFileException.cpp $(INCDIR)/DataFileException.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DataFileException.cpp -o $(BINDIR)/DataFileException.o

$(BINDIR)/GenericUnitTest.o: $(TSTDIR)/$(TSTSRCDIR)/GenericUnitTest.cpp $(TSTDIR)/$(TSTINCDIR)/GenericUnitTest.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/GenericUnitTest.cpp -o $(BINDIR)/GenericUnitTest.o

$(BINDIR)/DataFileException_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/DataFileException_TEST.cpp $(TSTDIR)/$(TSTINCDIR)/DataFileException_TEST.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/DataFileException_TEST.cpp -o $(BINDIR)/DataFileException_TEST.o

$(BINDIR)/Dataset.o: $(SRCDIR)/Dataset.cpp $(INCDIR)/Dataset.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/Dataset.cpp -o $(BINDIR)/Dataset.o

$(BINDIR)/Dataset_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/Dataset_TEST.cpp $(TSTDIR)/$(TSTINCDIR)/Dataset_TEST.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/Dataset_TEST.cpp -o $(BINDIR)/Dataset_TEST.o

$(BINDIR)/DelayedParticleRecord.o: $(SRCDIR)/DelayedParticleRecord.cpp $(INCDIR)/DelayedParticleRecord.h $(INCDIR)/Child.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/DelayedParticleRecord.cpp -o $(BINDIR)/DelayedParticleRecord.o

$(BINDIR)/ENSDF.o: $(SRCDIR)/ENSDF.cpp $(INCDIR)/ENSDF.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ENSDF.cpp -o $(BINDIR)/ENSDF.o

$(BINDIR)/ENSDF_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/ENSDF_TEST.cpp $(TSTDIR)/$(TSTINCDIR)/ENSDF_TEST.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/ENSDF_TEST.cpp -o $(BINDIR)/ENSDF_TEST.o

$(BINDIR)/GammaRecord.o: $(SRCDIR)/GammaRecord.cpp $(INCDIR)/GammaRecord.h $(INCDIR)/Child.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/GammaRecord.cpp -o $(BINDIR)/GammaRecord.o

$(BINDIR)/HistoryRecord.o: $(SRCDIR)/HistoryRecord.cpp $(INCDIR)/HistoryRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/HistoryRecord.cpp -o $(BINDIR)/HistoryRecord.o

$(BINDIR)/IdentificationRecord.o : $(SRCDIR)/IdentificationRecord.cpp $(INCDIR)/IdentificationRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/IdentificationRecord.cpp -o $(BINDIR)/IdentificationRecord.o

$(BINDIR)/InterestingDecay.o: $(SRCDIR)/InterestingDecay.cpp $(INCDIR)/InterestingDecay.h $(INCDIR)/Enums.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/InterestingDecay.cpp -o $(BINDIR)/InterestingDecay.o

$(BINDIR)/InterestingDecayBetaGamma.o: $(SRCDIR)/InterestingDecayBetaGamma.cpp $(INCDIR)/InterestingDecayBetaGamma.h $(INCDIR)/Enums.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/InterestingDecayBetaGamma.cpp -o $(BINDIR)/InterestingDecayBetaGamma.o

$(BINDIR)/InterestingDecayIsomer.o: $(SRCDIR)/InterestingDecayIsomer.cpp $(INCDIR)/InterestingDecayIsomer.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/InterestingDecayIsomer.cpp -o $(BINDIR)/InterestingDecayIsomer.o

$(BINDIR)/Isotop.o: $(SRCDIR)/Isotop.cpp $(INCDIR)/Isotop.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/Isotop.cpp -o $(BINDIR)/Isotop.o

$(BINDIR)/Isotop_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/Isotop_TEST.cpp $(TSTDIR)/$(TSTINCDIR)/Isotop_TEST.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/Isotop_TEST.cpp -o $(BINDIR)/Isotop_TEST.o

$(BINDIR)/LevelRecordChildrenWrapper.o: $(SRCDIR)/LevelRecordChildrenWrapper.cpp $(INCDIR)/LevelRecordChildrenWrapper.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/LevelRecordChildrenWrapper.cpp -o $(BINDIR)/LevelRecordChildrenWrapper.o

$(BINDIR)/LevelRecord.o: $(SRCDIR)/LevelRecord.cpp $(INCDIR)/LevelRecord.h $(INCDIR)/DoubleMath.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/LevelRecord.cpp -o $(BINDIR)/LevelRecord.o

$(BINDIR)/Main.o: $(SRCDIR)/Main.cpp $(INCDIR)/Main.h $(INCDIR)/Enums.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/Main.cpp -o $(BINDIR)/Main.o

$(BINDIR)/NormalizationRecord.o: $(SRCDIR)/NormalizationRecord.cpp $(INCDIR)/NormalizationRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/NormalizationRecord.cpp -o $(BINDIR)/NormalizationRecord.o

$(BINDIR)/Nukleid.o: $(SRCDIR)/Nukleid.cpp $(INCDIR)/Nukleid.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/Nukleid.cpp -o $(BINDIR)/Nukleid.o

$(BINDIR)/ParentRecordChildrenWrapper.o: $(SRCDIR)/ParentRecordChildrenWrapper.cpp $(INCDIR)/ParentRecordChildrenWrapper.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ParentRecordChildrenWrapper.cpp -o $(BINDIR)/ParentRecordChildrenWrapper.o

$(BINDIR)/ParentRecord.o: $(SRCDIR)/ParentRecord.cpp $(INCDIR)/ParentRecord.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ParentRecord.cpp -o $(BINDIR)/ParentRecord.o

$(BINDIR)/ProductionNormalizationRecord.o: $(SRCDIR)/ProductionNormalizationRecord.cpp $(INCDIR)/ProductionNormalizationRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ProductionNormalizationRecord.cpp -o $(BINDIR)/ProductionNormalizationRecord.o

$(BINDIR)/QValueRecord.o: $(SRCDIR)/QValueRecord.cpp $(INCDIR)/QValueRecord.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/QValueRecord.cpp -o $(BINDIR)/QValueRecord.o

$(BINDIR)/QValueRecordChildrenWrapper.o: $(SRCDIR)/QValueRecordChildrenWrapper.cpp $(INCDIR)/QValueRecordChildrenWrapper.h $(INCDIR)/Child.h $(INCDIR)/ChildAddable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/QValueRecordChildrenWrapper.cpp -o $(BINDIR)/QValueRecordChildrenWrapper.o

$(BINDIR)/Record.o: $(SRCDIR)/Record.cpp $(INCDIR)/Record.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/Record.cpp -o $(BINDIR)/Record.o

$(BINDIR)/Record_TEST.o: $(TSTDIR)/$(TSTSRCDIR)/Record_TEST.cpp $(TSTDIR)/$(TSTINCDIR)/Record_TEST.h
	$(CC) $(CTESTFLAGS) -c $(TSTDIR)/$(TSTSRCDIR)/Record_TEST.cpp -o $(BINDIR)/Record_TEST.o

$(BINDIR)/ReferenceRecord.o: $(SRCDIR)/ReferenceRecord.cpp $(INCDIR)/ReferenceRecord.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ReferenceRecord.cpp -o $(BINDIR)/ReferenceRecord.o

$(BINDIR)/ElementLookupTable.o: $(SRCDIR)/ElementLookupTable.cpp $(INCDIR)/ElementLookupTable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ElementLookupTable.cpp -o $(BINDIR)/ElementLookupTable.o

$(BINDIR)/MassObject.o: $(SRCDIR)/MassObject.cpp $(INCDIR)/MassObject.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/MassObject.cpp -o $(BINDIR)/MassObject.o

$(BINDIR)/MassTable.o: $(SRCDIR)/MassTable.cpp $(INCDIR)/MassTable.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/MassTable.cpp -o $(BINDIR)/MassTable.o

$(BINDIR)/MassPrinter.o: $(SRCDIR)/MassPrinter.cpp $(INCDIR)/MassPrinter.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/MassPrinter.cpp -o $(BINDIR)/MassPrinter.o

$(BINDIR)/CommandLineArgument.o: $(SRCDIR)/CommandLineArgument.cpp $(INCDIR)/CommandLineArgument.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineArgument.cpp -o $(BINDIR)/CommandLineArgument.o

$(BINDIR)/CommandLineInterpreter.o: $(SRCDIR)/CommandLineInterpreter.cpp $(INCDIR)/CommandLineInterpreter.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineInterpreter.cpp -o $(BINDIR)/CommandLineInterpreter.o

$(BINDIR)/ENSDFProcessor.o: $(SRCDIR)/ENSDFProcessor.cpp $(INCDIR)/ENSDFProcessor.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ENSDFProcessor.cpp -o $(BINDIR)/ENSDFProcessor.o

$(BINDIR)/CommandLineException.o: $(INCDIR)/CommandLineException.h $(SRCDIR)/CommandLineException.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/CommandLineException.cpp -o $(BINDIR)/CommandLineException.o

$(BINDIR)/VerbosePrinter.o: $(INCDIR)/VerbosePrinter.h $(SRCDIR)/VerbosePrinter.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/VerbosePrinter.cpp -o $(BINDIR)/VerbosePrinter.o

$(BINDIR)/VerbosePrinterEventEnabled.o: $(INCDIR)/VerbosePrinterEventEnabled.h $(SRCDIR)/VerbosePrinterEventEnabled.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/VerbosePrinterEventEnabled.cpp -o $(BINDIR)/VerbosePrinterEventEnabled.o

$(BINDIR)/NormalizationRecordChildrenWrapper.o: $(INCDIR)/NormalizationRecordChildrenWrapper.h $(SRCDIR)/NormalizationRecordChildrenWrapper.cpp
	$(CC) $(CFLAGS) -c $(SRCDIR)/NormalizationRecordChildrenWrapper.cpp -o $(BINDIR)/NormalizationRecordChildrenWrapper.o

$(BINDIR)/ParticleInstablePrinter.o: $(SRCDIR)/ParticleInstablePrinter.cpp $(INCDIR)/ParticleInstablePrinter.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/ParticleInstablePrinter.cpp -o $(BINDIR)/ParticleInstablePrinter.o

$(BINDIR)/BetaStablePrinter.o: $(SRCDIR)/BetaStablePrinter.cpp $(INCDIR)/BetaStablePrinter.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/BetaStablePrinter.cpp -o $(BINDIR)/BetaStablePrinter.o

clean: 
	-find . -type f -name "*~" -exec rm -f {} \;
	-find . -type f -name "*.o" -exec rm -f {} \;
	-find . -type f -name "\#*\#" -exec rm -f {} \;

cleanall: clean
	-rm -f BetaStablePrinter;
	-rm -f ENSDF++;
	-rm -f MassPrinter;
	-rm -f ParticleInstablePrinter;
	-rm -f unique;

upload: 
	@ echo 'Remote uploading to' $(REMOTEADDR)
	@ (./portknock.sh $(REMOTEADDR) && scp -p -r $(SRCDIR) riklund@$(REMOTEADDR):~/ENSDF/)
	@ (./portknock.sh $(REMOTEADDR) && scp -p -r $(INCDIR) riklund@$(REMOTEADDR):~/ENSDF/)
	@ (./portknock.sh $(REMOTEADDR) && scp -p -r $(TSTDIR) riklund@$(REMOTEADDR):~/ENSDF/)
	@ (./portknock.sh $(REMOTEADDR) && scp -p -r makefile riklund@$(REMOTEADDR):~/ENSDF/)

remotecompile:
	@ echo 'Remote compiling at' $(REMOTEADDR)
	@ (./portknock.sh $(REMOTEADDR) && ssh -l riklund $(REMOTEADDR) 'make -j 5');

docs: 
	@ doxygen doxyconf

deploy: all 
	+ make upload 
	+ make remotecompile

document:
	+ doxygen doxyconf
	+ (cd doc/latex/ && pdflatex refman.tex && cd ../..)

publish: 
	+ rm -f ENSDFpp.tar.gz
	+ mkdir -p ENSDFpp
	+ cp -r makefile ENSDFpp
	+ cp -r source ENSDFpp
	+ cp -r include ENSDFpp
	+ cp -r test ENSDFpp
	+ cp -r doc/latex/refman.pdf ENSDFpp/ReferenceManual.pdf
	+ cp -r plotter ENSDFpp
	+ (cd ENSDFpp/plotter && rm -rf *.eps)
	+ tar -cvzf ENSDFpp.tar.gz --exclude-vcs --exclude-backups ENSDFpp
	+ rm -rf ENSDFpp
	+ (mkdir -p ../Webbpage/ENSDF++/)
	+ (cp ENSDFpp.tar.gz ../Webbpage/ENSDF++)
	+ (cp -r doc/html/* ../Webbpage/ENSDF++)
#+ (ssh -l riklund $(WEBADDR) 'mkdir -p ~/www/ENSDF++')
#+ (scp -p -r doc/html/* riklund@$(WEBADDR):~/www/ENSDF++)
#+ (scp ENSDFpp.tar.gz riklund@$(WEBADDR):~/www/ENSDF++/ENSDFpp.tar.gz)
#+ (ssh -l riklund $(WEBADDR) 'chmod -R a+rx ~/www/ENSDF++')

total: clean deploy document publish