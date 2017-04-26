
#include <Rcpp.h>
using namespace Rcpp;
#include "ikg_pc.hpp" // Support for IKG point clouds




// [[Rcpp::export]]
DataFrame cpp_readPLY(std::string filename, bool verbose ) {
  

  ikg::ScanReader sr;
  sr.read(filename, verbose);
  size_t num_records = sr.z.size();

  
  NumericVector x(num_records);
  NumericVector y(num_records);
  NumericVector z(num_records);
  NumericVector run_id(num_records);
  NumericVector time(num_records);
  NumericVector head_x(num_records);
  NumericVector head_y(num_records);
  NumericVector head_z(num_records);


  for(size_t i=0; i < num_records; i++)
  {
       x[i] = sr.vertices[i*2];
       y[i] = sr.vertices[i*2+1];
       z[i] = sr.z[i];
       run_id[i] = sr.run_id[i];
       time[i] = sr.time[i];
       head_x[i] = sr.heads[2*i];
       head_y[i] = sr.heads[2*i+1];
       head_z[i] = sr.head_z[i];
  }

  
  return (DataFrame::create (
      Named("X") = x,
      Named("Y") = y,
      Named("Z") = z,
      Named("run_id") = run_id,
      Named("time") = time,
      Named("headX") = head_x,
      Named("headY") = head_y,
      Named("headZ") = head_z  
  ));
}
