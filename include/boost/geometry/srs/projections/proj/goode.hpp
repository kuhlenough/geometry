#ifndef BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP

// Boost.Geometry - extensions-gis-projections (based on PROJ4)
// This file is automatically generated. DO NOT EDIT.

// Copyright (c) 2008-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// PROJ4 is converted to Boost.Geometry by Barend Gehrels

// Last updated version of proj: 4.9.1

// Original copyright notice:

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <boost/geometry/srs/projections/impl/base_static.hpp>
#include <boost/geometry/srs/projections/impl/base_dynamic.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/impl/factory_entry.hpp>
#include <boost/geometry/srs/projections/proj/gn_sinu.hpp>
#include <boost/geometry/srs/projections/proj/moll.hpp>

namespace boost { namespace geometry
{

namespace srs { namespace par4
{
    struct goode {};

}} //namespace srs::par4

namespace projections
{
    #ifndef DOXYGEN_NO_DETAIL
    namespace detail { namespace goode
    {

            static const double Y_COR = 0.05280;
            static const double PHI_LIM = .71093078197902358062;

            template <typename CalculationType, typename Parameters>
            struct par_goode
            {
                sinu_ellipsoid<CalculationType, Parameters>    sinu;
                moll_spheroid<CalculationType, Parameters>    moll;
                
                par_goode(const Parameters& par) : sinu(par), moll(par) {}
            };

            // template class, using CRTP to implement forward/inverse
            template <typename CalculationType, typename Parameters>
            struct base_goode_spheroid : public base_t_fi<base_goode_spheroid<CalculationType, Parameters>,
                     CalculationType, Parameters>
            {

                typedef CalculationType geographic_type;
                typedef CalculationType cartesian_type;

                par_goode<CalculationType, Parameters> m_proj_parm;

                inline base_goode_spheroid(const Parameters& par)
                    : base_t_fi<base_goode_spheroid<CalculationType, Parameters>,
                     CalculationType, Parameters>(*this, par), m_proj_parm(par) {}

                // FORWARD(s_forward)  spheroid
                // Project coordinates from geographic (lon, lat) to cartesian (x, y)
                inline void fwd(geographic_type& lp_lon, geographic_type& lp_lat, cartesian_type& xy_x, cartesian_type& xy_y) const
                {
                    if (fabs(lp_lat) <= PHI_LIM)
                        this->m_proj_parm.sinu.fwd(lp_lon, lp_lat, xy_x, xy_y);
                    else {
                        this->m_proj_parm.moll.fwd(lp_lon, lp_lat, xy_x, xy_y);
                        xy_y -= lp_lat >= 0.0 ? Y_COR : -Y_COR;
                    }
                }

                // INVERSE(s_inverse)  spheroid
                // Project coordinates from cartesian (x, y) to geographic (lon, lat)
                inline void inv(cartesian_type& xy_x, cartesian_type& xy_y, geographic_type& lp_lon, geographic_type& lp_lat) const
                {
                    if (fabs(xy_y) <= PHI_LIM)
                        this->m_proj_parm.sinu.inv(xy_x, xy_y, lp_lon, lp_lat);
                    else {
                        xy_y += xy_y >= 0.0 ? Y_COR : -Y_COR;
                        this->m_proj_parm.moll.inv(xy_x, xy_y, lp_lon, lp_lat);
                    }
                }

                static inline std::string get_name()
                {
                    return "goode_spheroid";
                }

            };

            // Goode Homolosine
            template <typename CalculationType, typename Parameters>
            void setup_goode(Parameters& par, par_goode<CalculationType, Parameters>& proj_parm)
            {
                par.es = 0.;
            }

    }} // namespace detail::goode
    #endif // doxygen

    /*!
        \brief Goode Homolosine projection
        \ingroup projections
        \tparam Geographic latlong point type
        \tparam Cartesian xy point type
        \tparam Parameters parameter type
        \par Projection characteristics
         - Pseudocylindrical
         - Spheroid
        \par Example
        \image html ex_goode.gif
    */
    template <typename CalculationType, typename Parameters>
    struct goode_spheroid : public detail::goode::base_goode_spheroid<CalculationType, Parameters>
    {
        inline goode_spheroid(const Parameters& par) : detail::goode::base_goode_spheroid<CalculationType, Parameters>(par)
        {
            detail::goode::setup_goode(this->m_par, this->m_proj_parm);
        }
    };

    #ifndef DOXYGEN_NO_DETAIL
    namespace detail
    {

        // Static projection
        BOOST_GEOMETRY_PROJECTIONS_DETAIL_STATIC_PROJECTION(srs::par4::goode, goode_spheroid, goode_spheroid)

        // Factory entry(s)
        template <typename CalculationType, typename Parameters>
        class goode_entry : public detail::factory_entry<CalculationType, Parameters>
        {
            public :
                virtual base_v<CalculationType, Parameters>* create_new(const Parameters& par) const
                {
                    return new base_v_fi<goode_spheroid<CalculationType, Parameters>, CalculationType, Parameters>(par);
                }
        };

        template <typename CalculationType, typename Parameters>
        inline void goode_init(detail::base_factory<CalculationType, Parameters>& factory)
        {
            factory.add_to_factory("goode", new goode_entry<CalculationType, Parameters>);
        }

    } // namespace detail
    #endif // doxygen

} // namespace projections

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_PROJECTIONS_GOODE_HPP

