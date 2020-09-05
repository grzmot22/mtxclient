#pragma once

#ifndef MTX_EVENTS_NAME_HPP
#define MTX_EVENTS_NAME_HPP

#include <json.hpp>
#include <string>

namespace mtx
{
        namespace events
        {
                namespace state
                {

                        struct Name
                        {
                                std::string name;
                        };

                        void
                        from_json(const json &obj, Name &event);

                        void
                        to_json(json &obj, const Name &event);

                } // namespace state
        }         // namespace events
} // namespace mtx
