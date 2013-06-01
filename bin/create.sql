create table tbl_user(
  user_id bigint(11) NOT NULL AUTO_INCREMENT,
  user_type int(4),
  user_name varchar(64),
  passwd varchar(128),
  user_info text,
  PRIMARY KEY (user_id)
);

create table tbl_role (
  role_id bigint(11) NOT NULL AUTO_INCREMENT,
  role_type int(4),
  role_name varchar(64),
  role_info text, 
  unique key role_key(role_name),
  PRIMARY KEY (role_id)
);

create table tbl_user_role (
  assign_id bigint(11) NOT NULL AUTO_INCREMENT,
  user_id bigint(11),
  role_id bigint(11),
  expire_time timestamp,
  unique key assign_key(user_id, role_id),
  PRIMARY KEY(assign_id)
);

create table tbl_entity(
  entity_id bigint(11) NOT NULL AUTO_INCREMENT,
  scheme varchar(12),
  path varchar(256), 
  query varchar(1024),
  PRIMARY KEY (entity_id)
);

create table tbl_privilege (
  priv_id bigint(11) NOT NULL AUTO_INCREMENT,
  role_id bigint(11),
  entity_id bigint(11),
  priv_code int(4), 
  expire_time timestamp,
  PRIMARY KEY(priv_id)
);

create table tbl_audit(
  audit_id bigint(11) NOT NULL AUTO_INCREMENT,
  user_id bigint(11),
  entity_id bigint(11),
  action varchar(64),
  access_time date,
  detail text,
  PRIMARY KEY(audit_id)
);

create table tbl_role_acl(
  role_acl_id bigint(11) NOT NULL AUTO_INCREMENT,
  is_dirty smallint(4),
  role_id bigint(11),
  priv_tree blob,
  PRIMARY KEY(role_acl_id)
);

create table tbl_user_acl(
  user_acl_id bigint(11) NOT NULL AUTO_INCREMENT,
  is_dirty smallint(4),
  user_id bigint(11),
  priv_tree blob,
  PRIMARY KEY(user_acl_id)
);


