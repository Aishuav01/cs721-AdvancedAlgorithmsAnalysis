// Aishwarya Ajay Venkatesha
#include <iostream>
#include <fstream>    // For input and output files
#include <algorithm>  // Needed for sort()
#include <map>        // Needed for map<double, double> bst
#include <cstring>
using namespace std;

class Point
{  public:
      void setMaximal(){
         maximal = true;
      }  // Sets maximal to true: The point is maximal

      double getX() const{ return x;}
      double getY() const{ return y;}

      bool getMaximal() const{ return maximal; }

      bool operator<(const Point& p) const{
         if(this->z < p.z){
            return true;
         }
         else if(this->z == p.z){
            if(this->getY() < p.y){
               return true;
            }
            else if((this->getY() == p.y) && (this->getX() < p.x)){
               return true;
            }
            else{
               return false;
            }
         }
         else{
            return false;
         }
      }
      // Returns (*this < p)

      friend istream& operator>>(istream& ISObj, Point& p);
      // Inputs a single point: Its x, y and z coords

      friend ostream& operator<<(ostream& OSObj, const Point& p);
      // Outputs a single point: Its x, y and z coords

   private:
      double x = 0, y = 0, z = 0;  // Coords of the point
      bool maximal = false;        // Whether the point is maximal
};

typedef map<double, double> mapdd;

void inputPoints(ifstream& infile, Point* points, int* numPoints);
void findMaximal(Point* points, int numPoints, int* maxNum);
void printMaximal(ofstream& outfile, Point* points, int numPoints, int maxNum);

int main(int argc, char *argv[])
{  if (argc != 3)
   {  // Error check
      cout<<"Invalid number of input arguments, expected 3 got " << argc << ".";
   }

   ifstream infile(argv[1]);
   ofstream outfile(argv[2]);

   for (int i=1; i<=10; i++)  // Iterate on 10 sets of points
   {  
      int numPoints = 0;  // Number of points in the i-th set
      Point points[1000]; // points[0..(numPoints-1)]
      inputPoints(infile, points, &numPoints); // Reads the i-th input set
      sort(points,points+numPoints);          // Sorts points[0..(numPoints-1)]
      int maxNum = 0;     // Number of maximal points in the i-th set
      findMaximal(points,numPoints,&maxNum);   // Finds the maximal points
      outfile << "Output for " << i << "-th Set of Points\n";

      printMaximal(outfile,points,numPoints,maxNum );
   }

   infile.close();
}

void inputPoints( ifstream& infile, Point* points, int* numPoints )// Inputs all the points into points[]
{   
   string dummy;
   getline(infile,dummy);
   char temo_char_array[5];
   strcpy(temo_char_array, dummy.c_str());
   *numPoints = atoi(temo_char_array);
   for(int i = 0; i<*numPoints; i++){
         infile >> points[i];
   }
   getline(infile,dummy);
   return;
}

std::istream& operator>>(std::istream& ISObj, Point& p){
		ISObj >> p.x >> p.y >> p.z;
		 return ISObj;
	 }
std::ostream& operator<<(std::ostream&  OSObj, const Point& p){
		 OSObj <<" " <<  p.x << " " <<  p.y << " " << p.z ; 
		 return OSObj;
	 }


void printMaximal(ofstream& outfile, Point* points, int numPoints, int maxNum)// Outputs the maximal elements in points[]
{  
   outfile << "Input Size = " << numPoints << endl;
   outfile << "MaxNum = " << maxNum << endl << endl;
   outfile << "Maxima(S)\n";

   for (int i=0; i < numPoints; ++i)
      if (points[i].getMaximal())
         outfile << i << endl ;
   outfile << "\n--------------------------------------------\n\n";
   return;
}

void findMaximal(Point* points, int numPoints, int* maxNum)
// Finds the maximal elements in points[0..(numPoints-1)]
{  mapdd bst;  // Keeps the 2-d maxima (in the (x,y)-plane)
               // of the points seen so far.
               // Keeps (key=y_coord, value=x_coord) pairs.
   bst[1.0] = 0.0;  // Inserts (key 1.0, value 0.0) into bst
   *maxNum = 0;

   double xcoord, ycoord;
   for (int i = numPoints-1; i >= 0; i--)
   {  xcoord = points[i].getX();
      ycoord = points[i].getY();

      mapdd::iterator successor = bst.upper_bound(ycoord);
      
      if( ycoord < successor->first  ){
         
         if( xcoord >= successor->second  )
         {
            mapdd::iterator pred = successor;
           
            while( (pred != bst.begin()) && (pred ->second  < xcoord) )
            {
              if( pred->first < ycoord){
              mapdd::iterator temp = pred;
              --pred ; 
              bst.erase(temp);              
              }      
              else{
                 --pred ; 
              }               
            }    
            bst[ycoord] = xcoord;
            points[i].setMaximal(); 
            *maxNum+=1;

            if(  (pred == bst.begin()) && (pred->second  < xcoord) && ( pred->first < ycoord)){
            mapdd::iterator temp = pred;
            --pred ;
            bst.erase(temp);
            }
         }
      }
   }

   return;   

}
