#pragma once
#include "config.hpp"
#include "utils.hpp"
#include <avalon/defer.hpp>
#include "dataset_range.hpp"
namespace cxxqldb::postgresql {

struct connection {
  connection(const config& cfg){
    std::string info;
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, host);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, hostaddr);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, port);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, dbname);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, user);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, password);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, passfile);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, connect_timeout);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, client_encoding);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, options);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, application_name);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, fallback_application_name);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, keepalives);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, keepalives_idle);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, keepalives_interval);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, keepalives_count);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslmode); 
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslcompression);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslcert);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslkey);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslrootcert);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, sslcrl);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, requirepeer);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, krbsrvname);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, gsslib);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, service);
    CXXQL_PG_PUSH_CONF_MEM(info, cfg, target_session_attrs);

    conn_ = PQconnectdb(info.c_str());
    if(PQstatus(conn_) != CONNECTION_OK) {
      throw std::runtime_error(fmt::format("postgresql db connect failed: {}", PQerrorMessage(conn_)));
    }
  }
  template<class ResultElem>
  auto select(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    auto* res = PQexec(conn_, sql.c_str());
    auto holder = avalon::defer([res](){
      PQclear(res);
    });
    return dataset_range<ResultElem>(res);
  }
  auto exec(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    auto* res = PQexec(conn_, sql.c_str());
    auto holder = avalon::defer([res](){
      PQclear(res);
    });
    auto ec = PQresultStatus(res);
    if(ec != PGRES_COMMAND_OK) {
      throw std::runtime_error(fmt::format("postgresql query(command) failed: {}", sql));
    }
  }
  ~connection() {
    PQfinish(conn_);
  }
private:
  PGconn* conn_ {nullptr};
  std::function<void(const std::string&)> dbglog;
};
  
} // namespace cxxqldb::postgresql
