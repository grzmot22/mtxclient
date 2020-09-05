#pragma once

#ifndef MTX_RESPONSES_VERSION_HPP
#define MTX_RESPONSES_VERSION_HPP

#include <json.hpp>

namespace mtx
{
        namespace responses
        {

                //! Response from the `GET /_matrix/client/versions` endpoint.
                //
                //! Gets the versions of the specification supported by the server.
                struct Versions
                {
                        //! The supported versions.
                        std::vector<std::string> versions;
                };

                void
                from_json(const nlohmann::json &obj, Versions &response);
        } // namespace responses
} // namespace mtx
