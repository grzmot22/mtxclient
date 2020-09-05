#pragma once

#ifndef MTX_EVENTS_PINNED_EVENTS_HPP
#define MTX_EVENTS_PINNED_EVENTS_HPP

#include <json.hpp>
#include <string>

namespace mtx
{
        namespace events
        {
                namespace state
                {

                        struct PinnedEvents
                        {
                                std::vector<std::string> pinned;
                        };

                        void
                        from_json(const json &obj, PinnedEvents &event);

                        void
                        to_json(json &obj, const PinnedEvents &event);

                } // namespace state
        }         // namespace events
} // namespace mtx
