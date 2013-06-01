#ifndef OPEN_ACL_HANDLER_H_
#define OPEN_ACL_HANDLER_H_

#include <map>
#include "openacl/open-acl.h"
#include "openacl/gen-cpp/"
_BEG_ACL

class OpenAclHandler: public AclServiceIf {
public:
  OpenAclHandler() {
  }
  virtual ~OpenAclHandler() {}
  virtual void addUser(AuthStatus& _return, const UserInfo& userinfo, const AuditInfo& info);

  virtual void removeUser(AuthStatus& _return, const User& user, const AuditInfo& info); 

  virtual void addRole(AuthStatus& _return, const RoleInfo& roleInfo, const AuditInfo& info);

  virtual void removeRole(AuthStatus& _return, const Role& role, const AuditInfo& info);

  virtual void grantRoleToUser(AuthStatus& _return, const User& user, const Role& role, 
      const int64_t expireTime, const AuditInfo& info);

  virtual void grantPrivilegeToRole(AuthStatus& _return, const Role& role, 
      const std::vector<Privilege> & privilege, const int64_t expireTime, const AuditInfo& info);

  virtual void revokeRole(AuthStatus& _return, const User& user, const Role& role, const AuditInfo& info);

  virtual void revokePrivilege(AuthStatus& _return, const Role& role, const std::vector<Privilege> & privilege, const AuditInfo& info);

  virtual void authenticateUser(AuthStatus& _return, const User& user, const std::vector<Privilege> & privilege);

  virtual void authenticateRole(AuthStatus& _return, const Role& role, const std::vector<Privilege> & privilege);

  virtual void getRoleInfo(RoleInfo& _return, const Role& role);

  virtual void getUserInfo(UserInfo& _return, const User& user);

  virtual void getRolesByUser(std::vector<Role> & _return, const User& user);
  virtual void getPrivilegesByRole(std::vector<Privilege> & _return, const Role& role);
  virtual void getUsersHasRole(std::vector<UserInfo> & _return, const Role& role);
  virtual void getRolesHasPrivilege(std::vector<RoleInfo> & _return, const Privilege& privilege);
  virtual void addAuditInfo(const AuditInfo& info);
  virtual void getAuditInfo(std::vector<AuditInfo> & _return, const AuditCriteria& query);
protected:
  class QueryResult;
  QueryResult executeQuery(const Query& query);
  bool expireRole(Role role);
  bool expireUser(User user);
  AclTree& getNewestAclTreeByRoleId(int64 role_id);
  bool validateApiCaller(AuthStatus& result, string api);
  void updateUserAclTree(int64 user_id);
  void updateRoleAclTree(int64 role_id);

  String serializeAclTree();
  AclTree deserialzeAclTree(const AclTree& tree);

  AclTree& getNewestAclTreeByUserId(int64 user_id);

  User caller_;
  bool skipValidateApiCaller_;
  OpenAclHandler* callerAcl_;

  void beginBatch() {

  }

  void endBatch() {

  }
}; 
_END_ACL
#endif
