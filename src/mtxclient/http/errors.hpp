#pragma once

#ifndef MTXCLIENT_HTTP_ERRORS_HPP
#define MTXCLIENT_HTTP_ERRORS_HPP

#include "mtx/errors.hpp"
#include <boost_beast.hpp>

namespace mtx
{
        namespace http
        {

                //! Compound type that includes matrix & network related errors.
                struct ClientError
                {
                        //! Matrix client api related error.
                        mtx::errors::Error matrix_error;
                        //! Error code if a network related error occured.
                        boost::system::error_code error_code;
                        //! Status code of the associated http response.
                        boost::beast::http::status status_code;
                        //! Parsing response error.
                        std::string parse_error;
                };
        } // namespace http
} // namespace mtx
