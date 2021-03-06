// Copyright 2010-2012 RethinkDB, all rights reserved.
#include "clustering/administration/http/server.hpp"

#include "clustering/administration/http/cyanide.hpp"
#include "clustering/administration/http/me_app.hpp"
#include "http/file_app.hpp"
#include "http/http.hpp"
#include "http/routing_app.hpp"
#include "rpc/semilattice/view/field.hpp"

administrative_http_server_manager_t::administrative_http_server_manager_t(
        const std::set<ip_address_t> &local_addresses,
        int port,
        const server_id_t &my_server_id,
        http_app_t *reql_app,
        std::string path)
{

    file_app.init(new file_http_app_t(path));

    me_app.init(new me_http_app_t(my_server_id));

#ifndef NDEBUG
    cyanide_app.init(new cyanide_http_app_t);
#endif

    std::map<std::string, http_app_t *> ajax_routes;
    ajax_routes["me"] = me_app.get();
    ajax_routes["reql"] = reql_app;
    DEBUG_ONLY_CODE(ajax_routes["cyanide"] = cyanide_app.get());
    ajax_routing_app.init(new routing_http_app_t(nullptr, ajax_routes));

    std::map<std::string, http_app_t *> root_routes;
    root_routes["ajax"] = ajax_routing_app.get();
    root_routing_app.init(new routing_http_app_t(file_app.get(), root_routes));

    server.init(new http_server_t(local_addresses, port, root_routing_app.get()));
}

administrative_http_server_manager_t::~administrative_http_server_manager_t() {
    /* This must be declared in the `.cc` file because the definitions of the
    destructors for the things in `scoped_ptr_t`s are not available from
    the `.hpp` file. */
}

int administrative_http_server_manager_t::get_port() const {
    return server->get_port();
}
