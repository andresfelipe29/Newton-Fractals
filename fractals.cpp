#include <fstream>
#include <complex>

typedef std::complex<double> complex;

complex f(complex z);
complex deriv(complex z);

int main()
{
  int width = 675, height = 675, maxRGB = 255;
  float tolerance = 0.00001;
  int maxiter = 100;
  
  std::ofstream img("fractal.ppm"); // Open file for printing

  img << "P3" << std::endl; // Setup the image characteristics
  img << width << " " << height << std::endl;
  img << maxRGB << std::endl;

  for(int y = 0; y < height; y++){
    for(int x = 0; x < width; x++){
      
      complex z(x, y); // Set z to the pixel coordinates
      for (int i = 0; i < maxiter; i++){ 
	if (std::abs(f(z)) < tolerance){ // Color the pixel if z converges fast enough to a root
	  int red = i % 255;
	  int green = i % 255;
	  int blue = i*i % 255;
	  img << red << " " << green << " " << blue << std::endl;
	  break;
	}
	z = z - f(z)/deriv(z); // Newton's Method
      }
      if(std::abs(f(z)) > tolerance){ // Color black if z does not converge
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
