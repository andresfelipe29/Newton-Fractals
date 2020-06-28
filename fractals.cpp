#include <iostream>
#include <fstream>
#include <complex>
#include <array>
#include <string>

typedef std::complex<double> complex;

// Mandelbrot scales
const double minR = -2.5, maxR = 1.0;
const double minI = -1.0, maxI = 1.0;

// Image Parameters
const int width = 675, height = 675, maxRGB = 255;

// Method Parameters
const float tolerance = 0.00001;
const int maxiter = 100;

complex f(complex z);
complex deriv(complex z);
double map_to_real(int x);
double map_to_imaginary(int y);

int main()
{ 
  std::ofstream img("fractal.ppm"); // Open file for printing

  img << "P3" << std::endl; // Setup the image characteristics
  img << width << " " << height << std::endl;
  img << maxRGB << std::endl;

  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
      complex z(map_to_real(x), map_to_imaginary(y)); // map the pixel to the imaginary plane
      
      for(int i = 0; i < maxiter; i++){ 
	if(std::abs(f(z)) < tolerance){ // Color the pixel if z converges fast enough to a root
	  int red = 255 - i*i % 255;
	  int green = 255 - i*i % 255;
	  int blue = 255 - i*i % 255;
	  img << red << " " << green << " " << blue << std::endl;
	  break;
	  }
	z = z - f(z)/deriv(z); // Newton's Method
      }
      if(std::abs(f(z)) > tolerance){
	img << 0 << " " << 0 << " " << 0 << std::endl;
      }
      
    }
  }

  img.close(); // Close file
  
  return 0;
}

complex f(complex z)
{
  return std::pow(z, 3) - 1.; // Complex polynomial
}

complex deriv(complex z)
{
  return 3.*z*z; // derivative of f
}

double map_to_real(int x) // map the column to a real value
{
  double range = maxR - minR;
  //[0, width] -> [0, range]
  return x * (range/width) + minR;
}

double map_to_imaginary(int y) // map the row to an imaginary value
{
  double range = maxI - minI;
  //[0, height] -> [0, range]
  return y * (range/height) + minI;
}
