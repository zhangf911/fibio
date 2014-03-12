TODO List for Fiberized.IO
==========================

BUGS
----
* scheduler::add_thread caused problem

Core
----

* Refine `FIBERIZED_MAIN` macro if we have to determin thread number before starting scheduler
* Complete `fibio::io::{udp, local_stream, local_datagram}`
* Make sure size-restricted stream can work (for HTTP reques/resqonse body reader and Redis client)
* Make sure `fibio::condition_variable` and `std::condition_variable` can be used to communicate between `fiber` and `not-a-fiber`
    * Make sure `not-a-fiber` can notify `fiber` via `fibio::condition_variable`
    * Make sure `fiber` can notify `not-a-fiber` via `std::condition_variable`
    * Make `concurrent_queue` work between `fiber` and `not-a-fiber`
* Shared mutex(RWLock)
* Barrier
* Future support
* Fiber constructor with variadic arguments
* Logging

Protocol
--------

* Test drive, start with a simple Redis client
* HTTP client
* HTTP server framework
    * Session store
    * WebSocket
    * RESTful service
* HTTP request router for HTTP server
* Connection pool
* SSL/HTTPS support

Utilities
---------

* Serialization
    * JSON
    * XML
    * BSON
* Stream with compression
    * zlib
    * bzip2
    * snappy
* Database driver
    * Redis driver
    * MongoDB driver(?)
    * MySQL driver(?)
    * Cassandra driver(?)
* RPC framework
    * Thrift
    * Protocol buffer based
* Template engine for HTTP server
* Fiber-local-allocator(?)
* fiber-local allocated containers(?)

Scriptable
----------

* [Lua](http://www.lua.org)/[LuaJIT](http://luajit.org) binding via [LuaWrapper](https://github.com/Tomaka17/luawrapper)
* [ChaiScript](https://github.com/ChaiScript/ChaiScript) binding
* [V8](https://code.google.com/p/v8/) binding(?)