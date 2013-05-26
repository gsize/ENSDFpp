import java.util.ArrayList;
import java.io.*;
import java.awt.*;
import java.awt.geom.*;
import java.text.*;
import java.awt.image.*;
import java.awt.font.*;
import javax.imageio.*;
import javax.swing.ImageIcon;
import javax.swing.*;
import java.util.List;
import java.util.Arrays;


/**\file EPSCreator.java
   \author Rikard Lundmark
   \brief File containing the EPSCreator class.
*/


/**
This class contains information about what isotopes exist,
and what isotopes to draw with what color.
It also handles the drawing and creation of an EPS document.
\author Carl Toft, Philippe Klintefelt-Collet, Rikard Lundmark
*/
public class EPSCreator extends JFrame
{
    static private ArrayList<JIsotope> isotopeList;	// lists of isotopes, where the innermost list contains the name of the list and color codein
    // each list is drawn with a different color
    static private ArrayList<RGBVector> rgbVectorList;
    private int bottomLeftZ, bottomLeftA, upperRightZ, upperRightA;	// contains information on which part of the nuclide chart to draw
    private int bottomLeftN, upperRightN;				// number of neutrons in the bottom left and upper right isotopes
    private int width, height;			// holds the width and height of the epsdocument
    int isotopeWidth, isotopeHeight;
    Graphics2D graphics;						// EpsGraphics2D object that creates the eps document
    int preferredSizeOutside = 10;
    List<Integer> MagicNumbers;
    
     //!<Find minimum N for given Z.
    int findMinN(int Z /**Z*/)
    {
	int found = 10000;
	for(JIsotope i:isotopeList)
	    {
		if(i.getZ()==Z)
		    {
			if(i.getN()<found)
			    found=i.getN();
		    }
	    }
	if(found<bottomLeftN)
	    return bottomLeftN;
	return found;
    }
    
    int findMaxN(int Z) //!<Find maximum N for given Z.
    {
	int found = -10000;
	for(JIsotope i:isotopeList)
	    {
		if(i.getZ()==Z)
		    {
			if(i.getN()>found)
			    found=i.getN();
		    }
	    }
	if(found>upperRightN)
	    return upperRightN;
	return found;
    }
    
    int findMinZ(int N) //!<Find minimum Z for given N.
    {
	int found = 10000;
	for(JIsotope i:isotopeList)
	    {
		if(i.getN()==N)
		    {
			if(i.getZ()<found)
			    found=i.getZ();
		    }
	    }
	if(found<bottomLeftZ)
	    return bottomLeftZ;
	return found;
    }
    
    int findMaxZ(int N) //!<Find maximum Z for given N.
    {
	int found = -10000;
	for(JIsotope i:isotopeList)
	    {
		if(i.getN()==N)
		    {
			if(i.getZ()>found)
			    found=i.getZ();
		    }
	    }
	if(found>upperRightZ)
	    return upperRightZ;
	return found;
    }

    //!< accepts a list of lists of isotopes, each list will be drawn in a distinct color
    //!< the four integer arguments specify what part of the table of isotopes to draw
    //!< they are in order: Z and A of the isotope that should be drawn in the bottom left corner
    //!< and Z and A of the isotope that should be drawn in the upper right corner
    public EPSCreator(ArrayList<JIsotope> list, int blZ, int blA, int urZ, int urA)
    {
	isotopeList = new ArrayList<JIsotope>();
	//isotopeList = new ArrayList<JIsotope>();
	isotopeList = list;
	//rgbVectorList = rgbList;
	graphics = new EpsGraphics2D("epsdocument");
	setViewingArea(blZ, blA, urZ, urA);
        MagicNumbers = Arrays.asList(2, 8, 20, 28, 50, 82, 126, 152);
    }
    
    //!< accepts a list of lists of isotopes, each list will be drawn in a distinct color
    //!< with this constructor, what part of the table of isotopes should be drawn is not specified,
    //!< the entire table of isotopes will be drawn by default
    public EPSCreator(ArrayList<JIsotope> lists)
    {
	this(lists, 0, 0, 118, 293);
    }
    
    //!< sets what nuclides to draw (bottomLeftZ, bottomLeftA, upperRightZ, upperRightA)
    private void setViewingArea(int blZ, int blA, int urZ, int urA)
    {
	bottomLeftZ = blZ;
	bottomLeftA = blA;
	upperRightZ = urZ;
	upperRightA = urA;		
	upperRightN = upperRightA-upperRightZ;
	bottomLeftN = bottomLeftA-bottomLeftZ;
    }
    //!<Draw a line given input coordinates.
    private void drawLine(double x1, double x2, double y1, double y2)
    {
	Line2D lineToDraw = new Line2D.Double(x1,y1,x2,y2);
	graphics.draw(lineToDraw);
    }

    //!< draws the entire nuclide chart with colours according to the lists in isotopeLists
    private void drawNuclideChart()
	{
	    for (int i=0; i < isotopeList.size(); i++) 
		{
		    drawJIsotope(isotopeList.get(i), (Graphics)graphics);
		}
	    
	    //Stroke drawingStroke = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{30}, 0);
	    graphics.setStroke(new BasicStroke(3));
	    graphics.setColor(new Color(72, 61, 139));

	    //drawMagicLines();
	    drawNewMagicLines();
	}
    //!<Returns the width within boundaries.
    private double widthBoundaryCheck(double toCheck)
    {
	if(toCheck<0)
	    return 0;
	if(toCheck>width)
	    return width;
	return toCheck;
    }
    //!<Returns the height within boundaries.
    private double heightBoundaryCheck(double toCheck)
    {
	if(toCheck<0)
	    return 0;
	if(toCheck>height)
	    return height;
	return toCheck;
    }

    //!<Draw magic lines.
    private void drawNewMagicLines()
    {
	for(Integer i:MagicNumbers)
	    {
		for(int k = 0; k<2; ++k)
		    {
			//first fix A on magic number. -> vertical line
			if(bottomLeftN <= i+k && upperRightN+1 >=i+k) //OK to draw line
			    {
				drawLine(widthBoundaryCheck(isotopeWidth*(i+k-bottomLeftN)),
					 widthBoundaryCheck(isotopeWidth*(i+k-bottomLeftN)),
					 heightBoundaryCheck(height-isotopeHeight*(- bottomLeftZ +preferredSizeOutside + findMaxZ(i)+1)),
					 heightBoundaryCheck(height-isotopeHeight*(- bottomLeftZ-preferredSizeOutside + findMinZ(i))));
			    }
			//fix Z on magic number -> horizontal line.
			if(bottomLeftZ <= i+k && upperRightZ+1 >=i+k) //OK to draw line.
			    {
				drawLine(widthBoundaryCheck(isotopeWidth*(-bottomLeftN + findMinN(i)-preferredSizeOutside)),
					 widthBoundaryCheck(isotopeWidth*(- bottomLeftN + findMaxN(i)+preferredSizeOutside)),
					 heightBoundaryCheck(height-isotopeHeight*(i+k-bottomLeftZ)),
					 heightBoundaryCheck(height-isotopeHeight*(i+k-bottomLeftZ)));
			    }
		    }
	    }
    }
    
    //!<Draw a JIsotope.
    private void drawJIsotope(JIsotope iso, Graphics g)
    {
	// don't draw anything if the isotope is outside of the viewing area
	if (iso.getZ() < bottomLeftZ || iso.getZ() > upperRightZ || iso.getN() < bottomLeftN || iso.getN() > upperRightN)
	    return;

	//defining constants.
	int liningThickness = 10;
	int massXIndent = 15;
	int massYIndent = 20;
	int nameXIndent = 16;
	int nameYIndent = 29; 

	//Screen coordinates of upper left corner of isotope. 
	int x = (iso.getN()-bottomLeftN)*isotopeWidth;
	int y = height-(iso.getZ()-bottomLeftZ+1)*isotopeHeight;
	
	Font font = new Font("Arial", Font.PLAIN, 10);
	g.setFont(font);
	String isotopeName = iso.getName().substring(0,1) + iso.getName().substring(1).toLowerCase();
	Boolean oneUsed = false;
	if(iso.getColorList().size()>1)
	    if(iso.getColorList().get(1).getR() == 0 && iso.getColorList().get(1).getG() == 0 && iso.getColorList().get(1).getB() == 0)
		{

		    g.setColor(Color.black);
		    g.fillRect(x, y, isotopeWidth, isotopeHeight);
		    oneUsed = true;
		}
	
	switch(iso.getColorList().size())
	    {
	    case 1:
		g.setColor(new Color(iso.getColorList().get(0).getR(), iso.getColorList().get(0).getG(), iso.getColorList().get(0).getB()));
		g.fillRect(x, y, isotopeWidth, isotopeHeight);
		break;
	    case 2:
		int switcha = 1;
		if(oneUsed) switcha=0;
		g.setColor(new Color(iso.getColorList().get(switcha).getR(), iso.getColorList().get(switcha).getG(), iso.getColorList().get(switcha).getB()));
		if(oneUsed) 			
		    g.fillRect(x+liningThickness, y+liningThickness, isotopeWidth-2*liningThickness, isotopeHeight-2*liningThickness);
		else 
		    g.fillRect(x,y,isotopeWidth, isotopeHeight);
		break;
	    case 3:
		if(oneUsed)
		    {
			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			g.fillRect(x+liningThickness, y+liningThickness, isotopeWidth-2*liningThickness, isotopeHeight-2*liningThickness);
		    }
		else
		    {
			g.setColor(new Color(iso.getColorList().get(1).getR(), iso.getColorList().get(1).getG(), iso.getColorList().get(1).getB()));
			int xpoints0[] = {x, x, x + isotopeWidth};
			int ypoints0[] = {y, y + isotopeHeight, y + isotopeHeight};
			g.fillPolygon(xpoints0, ypoints0, 3);
			
			
			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			int xpoints1[] = {x, x + isotopeWidth, x + isotopeWidth};
			int ypoints1[] = {y, y, y + isotopeHeight};
			g.fillPolygon(xpoints1, ypoints1, 3);

		}
		break;
	    case 4:
		if(oneUsed)
		    {
			g.setColor(new Color(iso.getColorList().get(1).getR(), iso.getColorList().get(1).getG(), iso.getColorList().get(1).getB()));
			int xpoints0[] = {x+liningThickness, x+liningThickness, x + isotopeWidth-liningThickness};
			int ypoints0[] = {y+liningThickness, y + isotopeHeight-liningThickness, y + isotopeHeight-liningThickness};
			g.fillPolygon(xpoints0, ypoints0, 3);

			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			int xpoints1[] = {x+liningThickness, x + isotopeWidth-liningThickness, x + isotopeWidth-liningThickness};
			int ypoints1[] = {y+liningThickness, y+liningThickness, y + isotopeHeight-liningThickness};
			g.fillPolygon(xpoints1, ypoints1, 3);
		    }
		else
		    {
			g.setColor(new Color(iso.getColorList().get(1).getR(), iso.getColorList().get(1).getG(), iso.getColorList().get(1).getB()));
			int[] xpoints0 = {x, x, x + isotopeWidth};
			int[] ypoints0 = {y, y + isotopeHeight, y + isotopeHeight};
			g.fillPolygon(xpoints0, ypoints0, 3);
			
			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			int[] xpoints1 = {x, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints1 = {y, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints1, ypoints1, 3);
			
			g.setColor(new Color(iso.getColorList().get(3).getR(), iso.getColorList().get(3).getG(), iso.getColorList().get(3).getB()));
			int[] xpoints2 = {x + isotopeWidth, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints2 = {y + isotopeHeight, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints2, ypoints2, 3);

			
		    }
		break;
	    case 5:
		if(oneUsed)
		    {
			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			int[] xpoints0 = {x, x, x + isotopeWidth};
			int[] ypoints0 = {y, y + isotopeHeight, y + isotopeHeight};
			g.fillPolygon(xpoints0, ypoints0, 3);
			
			g.setColor(new Color(iso.getColorList().get(3).getR(), iso.getColorList().get(3).getG(), iso.getColorList().get(3).getB()));
			int[] xpoints1 = {x, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints1 = {y, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints1, ypoints1, 3);
			
			g.setColor(new Color(iso.getColorList().get(4).getR(), iso.getColorList().get(4).getG(), iso.getColorList().get(4).getB()));
			int[] xpoints2 = {x + isotopeWidth, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints2 = {y + isotopeHeight, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints2, ypoints2, 3);

		    }
		
		else
		    {
			g.setColor(new Color(iso.getColorList().get(1).getR(), iso.getColorList().get(1).getG(), iso.getColorList().get(1).getB()));
			int[] xpoints0 = {x, x, x + isotopeWidth/2};
			int[] ypoints0 = {y, y + isotopeHeight, y + isotopeHeight/2};
			g.fillPolygon(xpoints0, ypoints0, 3);
			
			g.setColor(new Color(iso.getColorList().get(2).getR(), iso.getColorList().get(2).getG(), iso.getColorList().get(2).getB()));
			int[] xpoints1 = {x, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints1 = {y, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints1, ypoints1, 3);
			
			g.setColor(new Color(iso.getColorList().get(3).getR(), iso.getColorList().get(3).getG(), iso.getColorList().get(3).getB()));
			int[] xpoints2 = {x + isotopeWidth, x + isotopeWidth, x + isotopeWidth/2};
			int[] ypoints2 = {y+isotopeHeight, y, y + isotopeHeight/2};
			g.fillPolygon(xpoints2, ypoints2, 3);
			
			g.setColor(new Color(iso.getColorList().get(4).getR(), iso.getColorList().get(4).getG(), iso.getColorList().get(4).getB()));
			int[] xpoints3 = {x, x + isotopeWidth/2, x + isotopeWidth};
			int[] ypoints3 = {y + isotopeHeight,  y + isotopeHeight/2, y + isotopeHeight};
			g.fillPolygon(xpoints3, ypoints3, 3);			
			
		    }
		break;
	    default:
		System.out.println("Too many color lists.");
	    }
			
	g.setColor(Color.black);
	g.drawRect(x, y, isotopeWidth, isotopeHeight);
	g.drawString(iso.getA()+"", x+massXIndent, y+massYIndent);
	g.drawString(isotopeName, x+nameXIndent, y+nameYIndent);

    }
    
    //!< creates the EPS document
    public void createEPSDocument(String filename)
    {
	isotopeWidth = 50;
	isotopeHeight = 50;
	
	width = isotopeWidth*(upperRightN-bottomLeftN+1);
	height = isotopeHeight*(upperRightZ-bottomLeftZ+1);
	
	drawNuclideChart();		
	
	try
	    {
		BufferedWriter out = new BufferedWriter(new FileWriter(filename, false));
		out.write(graphics.toString());
		out.close();
	    }
	catch(IOException e)
	    {
		System.out.println("Error creating EPS document!");
	    }
    } 
}