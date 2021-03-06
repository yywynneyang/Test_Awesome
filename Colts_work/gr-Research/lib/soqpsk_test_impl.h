/* -*- c++ -*- */
/*
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_RESEARCH_SOQPSK_TEST_IMPL_H
#define INCLUDED_RESEARCH_SOQPSK_TEST_IMPL_H

#include <Research/soqpsk_test.h>

namespace gr {
  namespace Research {

    class soqpsk_test_impl : public soqpsk_test
    {
     private:
      // Nothing to declare in this block.
        int d_test_var;
     public:
      soqpsk_test_impl(int test_var);
      ~soqpsk_test_impl();

    void soqpsk_test_impl::forecast(int noutput_items, gr_vector_int &ninput_items_required);

    void soqpsk_test_impl::rotation(double x,
        double y,
        double &xr,
        double &yr);


      // Where all the action really happens
      int general_work(int noutput_items,
        gr_vector_int &ninput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace Research
} // namespace gr

#endif /* INCLUDED_RESEARCH_SOQPSK_TEST_IMPL_H */

