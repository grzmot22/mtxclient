#include "mtxclient/utils.hpp"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

#include <boost_algorithm_string.hpp>
#include <boost_iostreams_copy.hpp>
#include <boost_iostreams_detail_error.hpp>
#include <boost_iostreams_detail_forward.hpp>
#include <boost_iostreams_filter_gzip.hpp>
#include <boost_iostreams_filter_zlib.hpp>
#include <boost_iostreams_filtering_stream.hpp>
#include <boost_iostreams_traits.hpp>
#include <boost_random_random_device.hpp>
#include <boost_random_uniform_int_distribution.hpp>

mtx::client::utils::MxcUrl
mtx::client::utils::parse_mxc_url(const std::string &url)
{
        constexpr auto mxc_uri_protocol = "mxc://";
        MxcUrl res;

        if (url.find(mxc_uri_protocol) != 0)
                return res;

        auto str_left = url.substr(6);

        std::vector<std::string> parts;
        boost::split(parts, str_left, [](char c) { return c == '/'; });

        if (parts.size() != 2) {
                res.server = parts.at(0);
                return res;
        }

        res.server   = parts.at(0);
        res.media_id = parts.at(1);

        return res;
}

bool
mtx::client::utils::is_number(const std::string &s)
{
        return !s.empty() &&
               std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

std::string
mtx::client::utils::random_token(uint8_t len, bool with_symbols) noexcept
{
        std::string symbols = "!@#$%^&*()";
        std::string alphanumberic("abcdefghijklmnopqrstuvwxyz"
                                  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "1234567890");

        const auto chars = with_symbols ? alphanumberic + symbols : alphanumberic;

        boost::random::random_device rng;
        boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);

        std::string token;
        token.reserve(len);

        for (uint8_t i = 0; i < len; ++i)
                token.push_back(chars[index_dist(rng)]);

        return token;
}

std::string
mtx::client::utils::query_params(const std::map<std::string, std::string> &params) noexcept
{
        if (params.empty())
                return "";

        auto pb = params.cbegin();
        auto pe = params.cend();

        std::string data = pb->first + "=" + url_encode(pb->second);
        ++pb;

        if (pb == pe)
                return data;

        for (; pb != pe; ++pb)
                data += "&" + pb->first + "=" + url_encode(pb->second);

        return data;
}

std::string
mtx::client::utils::decompress(const boost::iostreams::array_source &src,
                               const std::string &type) noexcept
{
        boost::iostreams::filtering_istream is;
        is.set_auto_close(true);

        std::stringstream decompressed;

        if (type == "deflate")
                is.push(boost::iostreams::zlib_decompressor{});
        else if (type == "gzip")
                is.push(boost::iostreams::gzip_decompressor{});

        is.push(src);
        boost::iostreams::copy(is, decompressed);

        return decompressed.str();
}

std::string
mtx::client::utils::url_encode(const std::string &value) noexcept
{
        // https: // stackoverflow.com/questions/154536/encode-decode-urls-in-c
        std::ostringstream escaped;
        escaped.fill('0');
        escaped << std::hex;

        for (auto i = value.begin(), n = value.end(); i != n; ++i) {
                std::string::value_type c = (*i);

                // Keep alphanumeric and other accepted characters intact
                if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                        escaped << c;
                        continue;
                }

                // Any other characters are percent-encoded
                escaped << std::uppercase;
                escaped << '%' << std::setw(2) << int((unsigned char)c);
                escaped << std::nouppercase;
        }

        return escaped.str();
}
