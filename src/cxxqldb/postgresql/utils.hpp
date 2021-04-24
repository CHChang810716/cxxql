#pragma once
#include <string>
#include <optional>
#include <fmt/format.h>
#include <memory>

namespace cxxqldb::postgresql {

template<class Name, class Value>
void push_config_mem(
  std::string& info,
  const Name& name, 
  const std::optional<Value>& value
) {
  if(!value) return;
  std::string next;
  if constexpr(std::is_same_v<Value, bool>) {
    next = fmt::format(" {}={:d}", name, value.value());
  } else if constexpr(std::is_same_v<Value, std::string>){
    next = fmt::format(" {}='{}'", name, value.value());
  } else {
    next = fmt::format(" {}={}", name, value.value());
  }
  info += (next.c_str() + (int)(info.empty()));
}

struct conn_deletor {
  void operator()(PGconn* ptr) const {
    PQfinish(ptr);
  }
};

struct result_deletor {
  void operator()(PGresult* ptr) const {
    PQclear(ptr);
  }
};

using conn_ptr   = std::unique_ptr<PGconn, conn_deletor>;
using result_ptr = std::shared_ptr<PGresult>;

template<class StdStr>
auto base_connect(const StdStr& info) {
  auto* conn = PQconnectdb(info.c_str());
  auto ec = PQstatus(conn);
  if(ec != CONNECTION_OK) {
    throw std::runtime_error(
      fmt::format(
        "postgresql db connect failed: {}", 
        PQerrorMessage(conn)
      )
    );
  }
  return conn_ptr {conn, conn_deletor{}};
}

template<class ConnPtr, class StdStr>
auto base_exec(
  ConnPtr&      conn, 
  const StdStr& sql,
  ExecStatusType success_code
) {
  auto* res = PQexec(conn.get(), sql.c_str());
  auto ec = PQresultStatus(res);
  if(ec != success_code) {
    throw std::runtime_error(fmt::format(
      "postgresql query failed: {}, reason: {}", 
      sql, PQerrorMessage(conn.get())
    ));
  }
  return result_ptr(res, result_deletor{});
}
  
} // namespace cxxqldb::postgresql

#define CXXQL_PG_PUSH_CONF_MEM(info, conf, name) \
  push_config_mem(info, #name, conf.name)
