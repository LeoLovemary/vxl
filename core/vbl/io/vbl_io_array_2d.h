// This is core/vbl/io/vbl_io_array_2d.h
#ifndef vbl_io_array_2d_h
#define vbl_io_array_2d_h
//:
// \file
// \author K.Y.McGaul
// \date   22-Mar-2001

#include <vsl/vsl_fwd.h>
#include <vbl/vbl_array_2d.h>
#include <vcl_iosfwd.h>

//: Binary save vbl_array_2d to stream.
template <class T>
void vsl_b_write(vsl_b_ostream & os, const vbl_array_2d<T> & v);

//: Binary load vbl_sparse_matrix from stream.
template <class T>
void vsl_b_read(vsl_b_istream & is, vbl_array_2d<T> & v);

//: Print human readable summary of object to a stream
template <class T>
void vsl_print_summary(vcl_ostream & os,const vbl_array_2d<T> & b);

#endif // vbl_io_array_2d_h
