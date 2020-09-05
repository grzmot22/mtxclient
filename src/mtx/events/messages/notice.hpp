#pragma once

#ifndef MTX_EVENTS_MESSAGES_NOTICE_HPP
#define MTX_EVENTS_MESSAGES_NOTICE_HPP

#include <json.hpp>
#include <string>

namespace mtx
{
        namespace events
        {
                namespace msg
                {

                        struct Notice
                        {
                                // The notice text to send.
                                std::string body;
                                // Must be 'm.notice'.
                                std::string msgtype;
                                //! We only handle org.matrix.custom.html.
                                std::string format;
                                //! HTML formatted message.
                                std::string formatted_body;
                        };

                        void
                        from_json(const json &obj, Notice &content);

                        void
                        to_json(json &obj, const Notice &content);

                } // namespace msg
        }         // namespace events
} // namespace mtx
