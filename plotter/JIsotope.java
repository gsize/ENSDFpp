
/**\file JIsotope.java
   \author Rikard Lundmark
   \brief File containing the JIsotope class.
*/


/*
The isotope class is used to store information about an isotope.
It contains a name (string) as well as number of protons, neutrons and
mass number (ints). It has methods to set number of protons and mass number
and its name.
\author Philippe Klintefelt-Collet, Carl Toft, Rikard Lundmark
*/
import java.util.ArrayList;

/** Contains information about a specific isotope to be drawn, including color.*/
public class JIsotope
{
    private int A, Z, N;		// mass, number of protons, number of neutrons
    private String name;
    private ArrayList<RGBVector> colorList;

	
    //!<info should be of the form:
    //!<"Z A chemical_element_name" where
    //!<Z is the number of protons, A the mass number and chemical_element_name
    //!<is the abbreviated form of the elemnts name (H for hydrogen, Si for silicon etc. 
    public JIsotope(int Z, int A, String name)
    {
	colorList = new ArrayList<RGBVector>();	
	this.Z = Z;
	this.A = A;
	N = A-Z;
	this.name = name;
    }
    
    public JIsotope(int Z, int A, String name, RGBVector rgbVector)
    {
	this(Z, A, name);
	addColor(rgbVector);
    }
    
    public void addColor(RGBVector rgbVector)
    {
	colorList.add(rgbVector);
    }
    
    public ArrayList<RGBVector> getColorList()
    {
	return new ArrayList<RGBVector>(colorList);
    }
    
    //!< returns number of protons
    public int getZ()
    {
	return Z;
    }
    
    //!< returns mass number
    public int getA()
    {
	return A;
    }
    
    //!< returns number of neutrons
    public int getN()
    {
	return N;
    }
    
    //!< returns abbreviated form of element name (H for hydrogen, Si for silicon etc).
    public String getName()
    {
	return name;
    }
    
    //Skulle kunna skrivas som equals(Object o), vilket vore snyggare.
    public boolean equals(Object o) 
    {
	if(!(o instanceof JIsotope))
	    {
		System.out.println("You failed to compare JIsotopes with JIsotope's equals(Object o)-method, and I didn't care to make an exception.");
	    }
	return Z == ((JIsotope)o).getZ() && N == ((JIsotope)o).getN();
    }
}
