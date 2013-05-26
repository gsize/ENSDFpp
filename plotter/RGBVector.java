import java.util.*;


/**\file RGBVector.java
   \author Rikard Lundmark
   \brief File containing the RGBVector class.
*/


/**
This class consists of vectors holdig R G B color information.
\author Philippe Klintefelt-Collet, Rikard Lundmark
*/

public class RGBVector
{
	private int r;
	private int g;
	private int b;
	
	RGBVector(int rIn, int gIn, int bIn)
	{
		r = rIn;
		g = gIn;
		b = bIn;
	}
	
	public int getR()
	{
		return r;
	}
	
	public int getG()
	{
		return g;
	}
	
	public int getB()
	{
		return b;
	}
	
	public void setColor(int rIn, int gIn, int bIn)
	{
		r = rIn;
		g = gIn;
		b = bIn;
	}
	
	public void setR(int rIn)
	{
		r = rIn;
	}
	
	public void setG(int gIn)
	{
		g = gIn;		
	}
	
	public void setB(int bIn)
	{
		b = bIn;		
	}
}



