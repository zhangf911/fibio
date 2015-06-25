//
//  server.hpp
//  fibio
//
//  Created by Chen Xu on 14-3-13.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#ifndef fibio_http_server_server_hpp
#define fibio_http_server_server_hpp

#include <memory>
#include <string>
#include <functional>
#include <system_error>
#include <fibio/stream/iostream.hpp>
#include <fibio/stream/ssl.hpp>
#include <fibio/http/server/request.hpp>
#include <fibio/http/server/response.hpp>

namespace fibio { namespace http {
    constexpr unsigned DEFAULT_MAX_KEEP_ALIVE=100;
#if defined(_WIN32)
    // NOTE: std::chrono::seconds constructor is not constexpr in VC
    static const timeout_type DEFAULT_TIMEOUT=std::chrono::seconds(60);
    static const timeout_type NO_TIMEOUT=std::chrono::seconds(0);
#else
    constexpr timeout_type DEFAULT_TIMEOUT=std::chrono::seconds(60);
    constexpr timeout_type NO_TIMEOUT=std::chrono::seconds(0);
#endif
    
    struct server_error : std::runtime_error {
        server_error(http_status_code c)
        : std::runtime_error("")
        , code(c) {}
        server_error(http_status_code c, const std::string &msg)
        : std::runtime_error(msg)
        , code(c) {}
        server_error(http_status_code c, const char *msg)
        : std::runtime_error(msg)
        , code(c) {}
        http_status_code code;
    };
    
    struct server {
        typedef fibio::http::server_request request;
        typedef fibio::http::server_response response;
        typedef std::function<bool(request &req,
                                   response &resp)> request_handler;
        
        struct settings {
            std::string address_="0.0.0.0";
            unsigned short port_=80;
            request_handler default_request_handler_=[](request &, response &)->bool{ return false; };
            timeout_type read_timeout_=DEFAULT_TIMEOUT;
            timeout_type write_timeout_=DEFAULT_TIMEOUT;
            unsigned max_keep_alive_=DEFAULT_MAX_KEEP_ALIVE;
            ssl::context *ctx_=nullptr;
        };

        server()=default;
        server(unsigned short p) { port(p); }
        server(const std::string &a, unsigned short p) { address(a).port(p); }
        ~server();
        
        server &address(const std::string &a) { s_.address_=a; return *this; }
        server &port(unsigned short p) { s_.port_=p; return *this; }
        server &ssl(ssl::context &c) { s_.ctx_=&c; return *this; }
        server &timeout(timeout_type t) { s_.read_timeout_=s_.write_timeout_=t; return *this; }
        server &max_keepalive(unsigned m) { s_.max_keep_alive_=m; return *this; }
        server &handler(request_handler h) { s_.default_request_handler_=h; return *this; }
        
        server &start();
        void stop();
        boost::system::error_code join();
        boost::system::error_code run() { return start().join(); }
        
        struct impl;
    private:
        void init_engine();
        bool ssl() const { return s_.ctx_; }
        settings s_;
        impl *engine_=nullptr;
        std::unique_ptr<fiber> servant_;
    };
}}  // End of namespace fibio::http

#endif
