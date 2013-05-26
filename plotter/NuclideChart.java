import java.io.*;
import java.awt.*;
import java.awt.geom.*;
import java.text.*;
import java.awt.image.*;
import java.awt.font.*;
import javax.imageio.*;
import javax.swing.ImageIcon;
import javax.swing.*;
import java.util.ArrayList;

/**\file NuclideChart.java
   \author Rikard Lundmark
   \brief File containing the NuclideChart class.
*/


/**
   Main program.
   Holds the information of all nuclides and which nuclides to highlight and creates an Eps-file with an image of the table of nuclides.
   \author Philippe Klintefelt-Collet, Carl Toft, Rikard Lundmark
*/
public class NuclideChart
{    
    //!<accepts an array of strings consisting of a list of files with isotopes
    //!< args[0] should be a file with a list of all isotopes
    //!< the other files should be a list with isotopes to be colored according to the comments of isotopeLists, above
    public static void main(String[] args)
    {
	if(args.length == 0)
	    {
		printHelp();
		System.exit(0);
	    }
	
	IndataParameters myParameters = new IndataParameters(args);
	
	ArrayList<JIsotope> isotopeList  = readJIsotopeList(myParameters.getJIsotopeFiles(), myParameters.getRGBVectorList());

	EPSCreator myEPSCreator;
	if(!myParameters.getSectionSpecified())
	    myEPSCreator = new EPSCreator(isotopeList);
	else
	    {
		NuclideSquare mySquare = myParameters.getSection();
		myEPSCreator = new EPSCreator(isotopeList, mySquare.bottomLeftZ, mySquare.bottomLeftA, mySquare.upperRightZ, mySquare.upperRightA);
	    }

	myEPSCreator.createEPSDocument(myParameters.getFilename());		
    }
    

    //!< stores the isotopes listed in the argument "file" in a new isotopeList in the member
    //!< variable isotopeLists
    public static ArrayList<JIsotope> readJIsotopeList(ArrayList<String> iLists, ArrayList<RGBVector> rgbVec)
    {
	ArrayList<JIsotope> isotopeList = new ArrayList<JIsotope>();
	//	isotopeLists.add(new ArrayList<JIsotope>());	
	for(int i=0; i<iLists.size(); i++)
	    {
		
		int listIndex = 0;
		
		try
		    {
			BufferedReader in = new BufferedReader(new FileReader(iLists.get(i)));	
			String input = in.readLine();
			
			// read all lines and create an isotope object from each of them
			// and add it to the last isotopeList in isotopeLists
			// that is, the list in isotopeLists with index (isotopeLists.size()-1)
			while (input != null && input.length()>0)
			    {
				
				JIsotope localJIsotope;
			        boolean isInList = false;
				
				
				int index1 = 0, index2 = 0;			// indices of the first and second whitespace in the string
				
				// find the first and second whitespaces
				for (int j = 0; j < input.length(); j++)
				    {
					if (input.charAt(j) == ' ' && index1 == 0)
					    index1 = j;			
					else if (input.charAt(j) == ' ' && index1 != 0)
					    {
						index2 = j;
						break;
					    }
				    }
				
				// set the member variables
				int Z = Integer.parseInt(input.substring(0, index1));
				int A = Integer.parseInt(input.substring(index1+1, index2));
				int N = A-Z;
				
				String name = input.substring(index2+1);
				
				
				for(int k=0; k<isotopeList.size(); k++)
				    {
					if(name.equals(isotopeList.get(k).getName()) && A == isotopeList.get(k).getA())
					    {
						isInList = true;
						listIndex = k;
						break;
					    }
				    }
				
				if(isInList)
				    {
					isotopeList.get(listIndex).addColor(rgbVec.get(i));
				    }

				else
				    {
					localJIsotope = new JIsotope(Z, A, name, rgbVec.get(i));
					isotopeList.add(localJIsotope);
				    }
				input = in.readLine();
			    }
		    }
		
		catch (IOException e)
		    {
			System.out.println("Error reading file:" + listIndex);
		    }
	    }
	return isotopeList;
    }

    /*
    //!< prints all isotopeLists to the screen. For debug pusposes only.
    public static void printAllJIsotopeList()
    {
    for (int i = 0; i < isotopeList.size(); i++)
    	    {
    		System.out.println("JIsotope number " + i + ": " +isotopeList.get(i).getZ() +" "+ isotopeList.get(i).getA() + isotopeList.get(i).getName() + " " + isotopeList.get(i).getColorList().get(0).getR()+ " " + isotopeList.get(i).getColorList().get(0).getG()+ " " + isotopeList.get(i).getColorList().get(0).getB());
    	    }
    }
    */


    //!<Print a help message concerning the usage of the software.
    private static void printHelp()
    {
	System.out.println("Program to draw a nuclide chart from given input nuclide lists.");
	System.out.println("Usage: java NuclideChart <Output file> [-n BottomLeftZ BottomLeftA UpperRightZ UpperRightA] [allNuclidesFile R1 G1 B1] [stableJIsotopes R2 G2 B2] n*[additionalNuclideList Ri Gi Bi]");
	System.out.println("Parameters:");
	System.out.println("<Output file>: EPS file to print to. Will be overwritten if it exists.");
	System.out.println("-n BottomLeftZ BottomLeftA UpperRightZ UpperRightA: plot only the square between the nuclide with A and Z as BottomLeftA and BottomLeftZ, and A and Z as UpperRightZ and UpperRightA.");
	System.out.println("allNuclidesFile: File containing all nuclides for the chart.");
	System.out.println("Ri, Gi, Bi: R, G and B components of coloring for that specific isotope list.");
	System.out.println("stableJIsotopes: File containing all stable isotopes.");
	System.out.println("additionalNuclideList: list containing additional nuclear data for coloring purposes.");
	/*
	System.out.println("In order to plot the entire nuclide chart, type the following command line arguments in the given order and press \"Enter\":");
	System.out.println();
	System.out.println("1 Type the name of the .txt file containing ALL nuclides, followed by its RGB coloring code on the form \"R G B\".");
	System.out.println();
	System.out.println("2 (Optional) Enter the name of the .txt file containing all stable isotopes, followed by its RGB coloring code on the form \"R G B\".");
	System.out.println();
	System.out.println("3 Type the names of all remaining .txt files to be plotted, each followed by its respective RGB coloring code on the form \"R G B\".");	
	System.out.println();
	System.out.println("In order to plot a specific region of the nuclide chart, BEFORE the above mentioned, also type:");
	System.out.println();
	System.out.println("\"-n BottomLeftZ BottomLeftA UpperRightZ UpperRightA\", where the last four arguments specify the specific region to be viewed in the way that their names indicate.");
	*/
    }
}
    
class IndataParameters
{
    private String filename;
    public String getFilename(){return filename;}
    private boolean sectionSpecified;
    public boolean getSectionSpecified(){return sectionSpecified;}
    private NuclideSquare section;
    public NuclideSquare getSection(){return new NuclideSquare(section);}
    private ArrayList<RGBVector> rgbVectorList;
    public ArrayList<RGBVector> getRGBVectorList(){ return new ArrayList<RGBVector>(rgbVectorList);}
    private ArrayList<String> isotopeFiles;
    public ArrayList<String> getJIsotopeFiles(){ return new ArrayList<String>(isotopeFiles);}


    public IndataParameters(String[] args)
    {
	rgbVectorList = new ArrayList<RGBVector>();
	isotopeFiles = new ArrayList<String>();

	filename = args[0];
	int ptr = 1; //!<Point to next position to parse.

	if (args[ptr].equalsIgnoreCase("-n"))
	    {
		sectionSpecified = true;
		ptr=6;
		section = new NuclideSquare();
		try
		    {
			section.bottomLeftZ = Integer.parseInt(args[2]);
			section.bottomLeftA = Integer.parseInt(args[3]);
			section.upperRightZ = Integer.parseInt(args[4]);
			section.upperRightA = Integer.parseInt(args[5]);
		    }
		catch(NumberFormatException ex)
		    {
			System.out.println("Error in parsing limits.");
			System.exit(1);
		    }
	    }
	else
	    {
		sectionSpecified = false;
	    }

	for (int i=ptr; i < args.length; i=i+4) //Var fjärde härifrån är en xxx.txt-fil
	    {
		isotopeFiles.add(args[i]);
	    }
	
	for (int i=ptr+1; i < args.length; i=i+4) //överväg i+4
	    {
		int r, g, b;
		try
		    {
			rgbVectorList.add(new RGBVector(Integer.parseInt(args[i]),Integer.parseInt(args[i+1]),Integer.parseInt(args[i+2])));
		    }
		catch(NumberFormatException ex)
		    {
			System.out.println("Error in parsing rgb vectors.");
			System.exit(1);
		    }
	    }
	
    }
}

//!<A bundle of four integers with a copy constructor.
class NuclideSquare
{
    public int bottomLeftZ;
    public int bottomLeftA;
    public int upperRightZ;
    public int upperRightA;
    
    public NuclideSquare()
    {
	bottomLeftZ = 0;
	bottomLeftA = 0;
	upperRightZ = 0;
	upperRightA = 0;
    }

    public NuclideSquare(NuclideSquare toCopy)
    {
	this.bottomLeftZ = toCopy.bottomLeftZ;
	this.bottomLeftA = toCopy.bottomLeftA;
	this.upperRightZ = toCopy.upperRightZ;
	this.upperRightA = toCopy.upperRightA;
    }
}