#pragma once

#ifndef MTX_EVENTS_TAG_HPP
#define MTX_EVENTS_TAG_HPP

#include <json.hpp>
#include <string>

namespace mtx
{
        namespace events
        {
                namespace account_data
                {

                        //! Content for the `m.tag` room account_data event.
                        //! A tag is a short string a client can attach to a room for sorting or advanced functionality.
                        struct Tag
                        {
                                //! The tag list.
                                //! A tag can have arbitrary JSON data attached
                                std::map<std::string, json> tags;
                        };

                        void
                        from_json(const json &obj, Tag &content);

                        void
                        to_json(json &obj, const Tag &content);

                } // namespace account_data
        }         // namespace events
} // namespace mtx