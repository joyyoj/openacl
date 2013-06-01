<?php

$acl_home =realpath(dirname(__FILE__) . "/..");
$thrift = getenv("THRIFT_HOME") . "/bin/thrift";
$cmd = "$thrift -gen cpp -out $acl_home/src/gen-cpp $acl_home/OpenAcl.thrift";
exec($cmd);

