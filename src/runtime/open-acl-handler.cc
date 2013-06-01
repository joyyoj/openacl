#include "openacl/runtime/openacl-handler.h"
#include "openacl/runtime/openacl-model.h"
_BEG_ACL
 
class IdUtilities {
public:
  static Id getUserId(User& user);
  static Id getRoleId(Role& role);
};

  OpenAclHandler::~OpenAclHandler() {
  }

  void OpenAclHandler::addUser(AuthStatus& _return, const UserInfo& userinfo, const AuditInfo& info) {
    Query query;
    query.set("insert into tbl_user set user_type=:user_type, user_name=:user_name, passwd=:passwd, user_info=:user_info");
    query.setParam(":user_type", userinfo.user.user_type);
    query.setParam(":user_name", userinfo.user.user_name);
    query.setParam(":passwd", userinfo.passwd);
    query.setParam(":user_info", Utilities::jsonEncode(user_info.properties));
    updateStatus(_return, executeQuery(query)); 
  }

  void OpenAclHandler::removeUser(AuthStatus& _return, const User& user, const AuditInfo& info) {
    Query query;
    query.set("delete from tbl_user where user_type:=user_type, user_name=:user_name");
    query.setParam(":user_type", user.type);
    query.setParam(":user_name", user.name);
    updateStatus(_return, executeQuery(query)); 
  }

  void OpenAclHandler::addRole(AuthStatus& _return, const RoleInfo& roleInfo, const AuditInfo& info) {
    Query query;
    query.set("insert into tbl_role set role_type=:role_type, role_name=:role_name, role_info=:role_info");
    query.setParam(":role_type", roleInfo.type);
    updateStatus(_return, executeQuery(query)); 
  }

  void OpenAclHandler::removeRole(AuthStatus& _return, const Role& role, const AuditInfo& info) {
    Query query;
    query.set("delete from tbl_role where role_name=:role_name and role_type=:role_type");
    query.setParam(":role_type", role.type);
    updateStatus(_return, executeQuery(query)); 
  }

  void OpenAclHandler::grantRoleToUser(AuthStatus& _return, const User& user, const Role& role, 
      const int64_t expireTime, const AuditInfo& info) {
    Query query;
    query.set("insert into tbl_user_role set user_id=:user_id, role_id=:role_id"); 
    expireUser(user);
    updateStatus(_return, executeQuery(query));
  }

  void OpenAclHandler::grantPrivilegeToRole(AuthStatus& _return, const Role& role, 
      const std::vector<Privilege> & privilege, const int64_t expireTime, const AuditInfo& info) {
    Query query;
    query.set("insert into tbl_entity set scheme=:scheme, path=:path, query=:query");
    query.set("insert into tbl_privilege set role_id=:role_id, entity_id=:entity_id, priv_code=:priv_code");
    expireRole(role);
    updateStatus(_return, executeQuery(query));
  }

  void OpenAclHandler::revokeRole(AuthStatus& _return, const User& user, const Role& role, const AuditInfo& info) {
    Query query;
    query.set("delete from tbl_role where role_name=:role_name and role_type=:role_type");
  }

  void OpenAclHandler::revokePrivilege(AuthStatus& _return, const Role& role, const std::vector<Privilege> & privilege, const AuditInfo& info) {
  }

  void OpenAclHandler::authenticateUser(AuthStatus& _return, const User& user, const std::vector<Privilege> & privilege) {
    AclTree tree = getNewestAclTreeByUserId(IdUtilities::getUserId(user));
    tree.authenticateUser(privilege);
  }

  void OpenAclHandler::authenticateRole(AuthStatus& _return, const Role& role, const std::vector<Privilege> & privilege) {
    AclTree tree = getNewestAclTreeByRoleId(IdUtilities::getRoleId(user));
    tree.authenticateUser(privilege);
  }

  void OpenAclHandler::getRoleInfo(RoleInfo& _return, const Role& role) {
    Query query;
    query.set("select * from tbl_role where role_type=:role_type and role_name=:role_name");
  }

  void OpenAclHandler::getUserInfo(UserInfo& _return, const User& user) {
    Query query;
    query.set("select * from tbl_user where user_name=:user_name and user_type=:user_type");
  }

  void OpenAclHandler::getRolesByUser(std::vector<Role> & _return, const User& user) {
    Query query;
    query.set("select * from tbl_user_role t1 where user_id=");
  }

  void OpenAclHandler::getPrivilegesByRole(std::vector<Privilege> & _return, const Role& role) {
    Query query;
  }

  void OpenAclHandler::getUsersHasRole(std::vector<UserInfo> & _return, const Role& role) {

  }

  void OpenAclHandler::getRolesHasPrivilege(std::vector<RoleInfo> & _return, const Privilege& privilege) {

  }

  void OpenAclHandler::addAuditInfo(const AuditInfo& info) {

  }
  void OpenAclHandler::getAuditInfo(std::vector<AuditInfo> & _return, const AuditCriteria& query) {

  }

  void OpenAclHandler::open(const User& user, const std::string& password) {
    AuthStatus status;
    this->validateUser(status, user, password);
  }

  void OpenAclHandler::updateUserAclTree(int64 user_id) {
    std::vector<int64> role_list;
    std::vector<AclTree> acl_list;
    for (int i = 0; i < role_list.size(); ++i) {
      acl_list.push_back(getNewestAclTreeByRoleId(role_list[i]));
    }
    AclTree aclTree = mergeAclTree();
    Query query;
    query.set("update tbl_user_acl where ");
  }

  void OpenAclHandler::updateRoleAclTree(int64 role_id) {
    //get role acl tree
    //update tbl_role_acl
    query.set("select * from tbl_privilege t1 where role_id=:role_id");
  }

  AclTree& OpenAclHandler::getNewestAclTreeByUserId(int64 user_id) {
    //get user acl tree
    Query query;
    query.set("select * from tbl_user_acl where user_id=:user_id");
    //if is not dirty, return;
    QueryResult qs = executeQuery(query);  
    //reflush tree
    query.set("select role_id from tbl_user_role t1 join tbl_user t2 on t2.user_id=t1.user_id and t2.user_name=:user_name and t2.user_type=:user_type");   
  }

  bool OpenAclHandler::validateApiCaller(AuthStatus& result, string api) {
    if (!skipValidateApiCaller_) {
      AuthStatusHelper::Error(result, 1, "users do not pass");  
      return false;
    }
    Entity entity;
    entity.scheme = "api";
    entity.path = api;
    Privilege priv;
    priv.entities.push_back(entity);
    callerAcl_->authenticateUser(result, caller_, priv);
    return true;
  }


}
