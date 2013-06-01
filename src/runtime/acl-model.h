#ifndef ACL_RUNTIME_QUERY_H_
#define ACL_RUNTIME_QUERY_H_

#include "openacl/open-acl.h"
#include <map>
_BEG_ACL

class Query {
public:
  void setParam(const String& param, const String& value) {
    params[param] = value;
  }
  void set(const String& query) {
    this.query = query;
  }
private:
  String query;
  std::map<String, String> params;
};

class QueryResult {
public:

};

class DbConnection {
  void connect(const String& host, const String& port, const String& user, const String& passwd);
public:
  static DbConnection getConnection(); 
  QueryResult executeQuery(const Query& query);
  void close();
};

_END_ACL
#endif
