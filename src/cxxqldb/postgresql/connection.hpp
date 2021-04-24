#pragma once
#include "injection.hpp"
#include "config.hpp"
#include "utils.hpp"
#include <avalon/defer.hpp>
#include "dataset_range.hpp"
#include <cxxql/db.hpp>
namespace cxxqldb::postgresql {

template<class Config>
struct connection : cxxql::db<connection<Config>>{
  connection(Config&& cfg){
    std::string info;
    {
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
    }
    conn_ = base_connect(info);
  }
  template<class ResultElem>
  auto select(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    auto res = base_exec(conn_, sql, PGRES_TUPLES_OK);
    return dataset_range<ResultElem>(std::move(res));
  }
  auto exec(const std::string& sql) {
    if(dbglog) {
      dbglog(fmt::format("exec: {}", sql));
    }
    auto res = base_exec(conn_, sql, PGRES_COMMAND_OK);
  }
  std::function<void(const std::string&)> dbglog;
private:
  conn_ptr conn_ {nullptr, conn_deletor{}};
};

template<class Config>
auto make_db(Config&& config) {
  return connection<Config>(std::forward<Config>(config));
}
  
} // namespace cxxqldb::postgresql
