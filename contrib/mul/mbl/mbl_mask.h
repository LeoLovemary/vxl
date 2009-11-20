// This is mul/mbl/mbl_mask.h
#ifndef mbl_mask_h_
#define mbl_mask_h_
//:
// \file
// \author Barry Skellern
// \brief Class representing a binary mask, and related functions

#include <vcl_vector.h>
#include <vcl_stdexcept.h>
#include <vcl_iterator.h>
#include <vcl_string.h>

class vcl_ostream;
class vcl_istream;


//: Defines a binary mask
class mbl_mask : public vcl_vector<bool>
{
};

    //: Replace 'true' values in B with values taken from A. size of A must match 'true' count in B
void mbl_mask_on_mask(const mbl_mask & A, mbl_mask & B);


    //: Merge two input ranges according to a mask ('false' indicates element drawn from range 1, 'true' from range 2)
template <typename ForwardIterator>
void mbl_mask_merge_values(const mbl_mask & mask,
                           ForwardIterator first1, ForwardIterator last1,
                           ForwardIterator first2, ForwardIterator last2,
                           ForwardIterator result)
{
  if (vcl_distance(first1, last1) != mask.size() || vcl_distance(first2, last2) != mask.size())
    throw vcl_runtime_error("Values and mask lengths differ");

  for (unsigned n = 0 ; first1 != last1 ; ++first1, ++first2, ++n)
    *result++ = mask[n] ? *first2 : *first1;
}

    //: Apply a general logical operation between two masks
void mbl_mask_logic(const mbl_mask & A, mbl_mask & B, const vcl_string & operation);

    //: Apply an "AND" (rule 0001) logical operation between two masks
void mbl_mask_logic_and(const mbl_mask & A, mbl_mask & B);

    //: Apply an "OR" (rule 0111) logical operation between two masks
void mbl_mask_logic_or(const mbl_mask & A, mbl_mask & B);

    //: Apply an "XOR" (rule 0110) logical operation between two masks
void mbl_mask_logic_xor(const mbl_mask & A, mbl_mask & B);

    //: Apply a "NOR" (rule 1000) logical operation between two masks
void mbl_mask_logic_nor(const mbl_mask & A, mbl_mask & B);

    //: Apply an "XNOR" (rule 1001) logical operation between two masks
void mbl_mask_logic_xnor(const mbl_mask & A, mbl_mask & B);

    //: Apply an "NAND" (rule 1110) logical operation between two masks
void mbl_mask_logic_nand(const mbl_mask & A, mbl_mask & B);



    //: Apply a mask to a range of values. Result inserted at 'target'
template <typename ForwardIterator, typename InputIterator>
void mbl_apply_mask(const mbl_mask & mask, ForwardIterator first, ForwardIterator last, InputIterator target)
{
  if (vcl_distance(first, last) != mask.size())
    throw vcl_runtime_error("Values and mask lengths differ");

  for (unsigned n = 0 ; first != last ; ++first, ++n)
    if (mask[n]) *target++ = *first;
}

    //: Apply a mask to a vector, returning a new vector
template <typename T>
vcl_vector<T> mbl_apply_mask(const mbl_mask & mask, const vcl_vector<T> & values)
{
  vcl_vector<T> retval(values);
  mbl_apply_mask(mask, retval);
  return retval;
}

    //: Apply a mask to a vector in-place
template <typename T>
void mbl_apply_mask(const mbl_mask & mask, vcl_vector<T> & values)
{
  const unsigned n_in = values.size();
  if (mask.size() != n_in)
    throw vcl_runtime_error("Values and mask lengths differ");

  unsigned n_out = 0;
  for (unsigned i = 0 ; i < n_in ; ++i)
  {
    if (mask[i])
    {
      values[n_out] = values[i];
      ++n_out;
    }
  }
  values.resize(n_out);
}

    //: Save to file
void mbl_save_mask(const mbl_mask & mask, vcl_ostream & stream);

    //: Save to file
void mbl_save_mask(const mbl_mask & mask, const char * filename);

    //: Load from file
void mbl_load_mask(mbl_mask & mask, vcl_istream & stream);

    //: Load from file
void mbl_load_mask(mbl_mask & mask, const char * filename);




#endif // mbl_mask_h_
