/* -*- c++ -*- */
/*
 * Copyright 2017 Cillian O'Driscoll <cillian.odriscoll@gmail.com>
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef OSMOSDR_CONVERSION_HELPERS_H
#define OSMOSDR_CONVERSION_HELPERS_H 

#include <gnuradio/blocks/char_to_short.h>
#include <gnuradio/blocks/char_to_float.h>
#include <gnuradio/blocks/interleaved_char_to_complex.h>

#include <gnuradio/blocks/short_to_char.h>
#include <gnuradio/blocks/short_to_float.h>
#include <gnuradio/blocks/interleaved_short_to_complex.h>

#include <gnuradio/blocks/float_to_char.h>
#include <gnuradio/blocks/float_to_short.h>
//#include <gnuradio/blocks/complex_to_interleaved_char.h>
//#include <gnuradio/blocks/complex_to_interleaved_short.h>


inline gr::basic_block_sptr make_conversion_block( 
        std::string input_type,
        std::string output_type
        )
{
    gr::basic_block_sptr null_block;

    if( input_type == "i8" )
    {
        if(output_type == "i8")
        {
            return null_block;
        }
        else if( output_type == "i16" )
        {
            return gr::blocks::char_to_short::make();
        }
        else if( output_type == "f32" )
        {
            return gr::blocks::char_to_float::make( 1, 128.0f );
        }
    }
    else if( input_type == "i16" )
    {
        if( output_type == "i8" )
        {
            return gr::blocks::short_to_char::make();
        }
        else if( output_type == "i16" )
        {
            return null_block;
        }
        else if( output_type == "f32" )
        {
            return gr::blocks::short_to_float::make( 1, 2048.0f );
        }
        
    }
    else if( input_type == "f32" )
    {
        if( output_type == "i8" )
        {
            return gr::blocks::float_to_char::make( 1, 128.0f );
        }
        else if( output_type == "i16" )
        {
            return gr::blocks::float_to_short::make( 1, 2048.0f );
        }
        else if( output_type == "f32" )
        {
            return null_block;
        }
    }
    else if( input_type == "ic8" )
    {
        if( output_type == "ic8" )
        {
            return null_block;
        }
        else if( output_type == "ic16" )
        {
            return gr::blocks::char_to_short::make( 2 );
        }
        else if( output_type == "fc32" )
        {
            return gr::blocks::char_to_float::make( 2, 128.0f );
        }
    }
    else if( input_type == "ic16" )
    {
        if( output_type == "ic8" )
        {
            return gr::blocks::short_to_char::make( 2 );
        }
        else if( output_type == "ic16" )
        {
            return null_block;
        }
        else if( output_type == "fc32" )
        {
            return gr::blocks::short_to_float::make( 2, 2048.0f );
        }
    }
    else if( input_type == "fc32" )
    {
        if( output_type == "ic8" )
        {
            return gr::blocks::float_to_char::make( 2, 128.0f );
        }
        else if( output_type == "ic16" )
        {
            return gr::blocks::float_to_short::make( 2, 2048.0f );
        }
        else if( output_type == "fc32" )
        {
            return null_block;
        }
    }


    // If we make it to here the types are incompatible
    throw std::runtime_error("Incompatible data types: " + input_type
            + " - " + output_type );

    // Can't touch this
    return null_block;
}

#endif
