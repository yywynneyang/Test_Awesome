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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "new_qpsk_demod_cb_impl.h"
#include <gnuradio/math.h>
#include <gnuradio/gr_complex.h>

namespace gr {
  namespace Research {

    new_qpsk_demod_cb::sptr
    new_qpsk_demod_cb::make(bool gray_code)
    {
      return gnuradio::get_initial_sptr
        (new new_qpsk_demod_cb_impl(gray_code));
    }

    /*
     * The private constructor
     */
    new_qpsk_demod_cb_impl::new_qpsk_demod_cb_impl(bool gray_code)
      : gr::block("new_qpsk_demod_cb",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make(1,1, sizeof(char))),
		d_gray_code(gray_code)
    {
	if(gray_code) {
		GR_LOG_DEBUG(d_debug_logger, "Gray code enabled. Derp.");
	} else {
		GR_LOG_DEBUG(d_debug_logger, "Gray code disabled. Derp.");
	}
    
    }

    /*
     * Our virtual destructor.
     */
    new_qpsk_demod_cb_impl::~new_qpsk_demod_cb_impl()
    {
    }

    

    void
    new_qpsk_demod_cb_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      
	unsigned int input_required = noutput_items;
	unsigned ninputs = ninput_items_required.size();
	for(unsigned i = 0 ; i < ninputs; i++)
	{
		ninput_items_required[i] = noutput_items;
	}
    }

	
    int
    new_qpsk_demod_cb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
	// These are the pointers to the input and output arrays
      const gr_complex *in = (const gr_complex *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>

	gr_complex origin = gr_complex(0,0);

	// Perform Minimum Likelyhood decoding over the input iq data to generate alphabets
	for ( int i = 0 ; i < noutput_items ; i++) {
		// ML dedcoder, determine the minimum distance from all constellation points
		out[i] = get_minimum_distances(in[i]);
	}

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

unsigned char
    new_qpsk_demod_cb_impl::get_minimum_distances(const gr_complex &sample)
    {
	if (d_gray_code) {
		unsigned char bit0 = 0;
		unsigned char bit1 = 0;

		// The two left quadrants (quadrature component < 0) have this bit set to 1
		if(sample.real() < 0) {
			bit0 = 0x01;
		}

		// The two lower quadrants (in-phase component < 0) have this bit set to 1
		if (sample.imag() < 0) {
			bit1 = 0x01 << 1;
		}
		return bit0 | bit1;
	} else {
		// Fro non-gray code, we can't simply decide on signs, so we check every single quadrant.
		if(sample.imag() >= 0 and sample.real() >= 0) {
			return 0x00;
		}
		else if (sample.imag() >= 0 and sample.real() < 0) {
			return 0x01;
		}
		else if (sample.imag() < 0 and sample.real() < 0) {
			return 0x02;
		}
		else if (sample.imag() < 0 and sample.real() >= 0) {
			return 0x03;
		}
	}
}


  } /* namespace Research */
} /* namespace gr */

