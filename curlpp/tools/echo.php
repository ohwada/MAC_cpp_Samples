<?php
// 2020-07-01 K.OHWADA
// echo back basic auth, method, header,  post data

// basic auth
$arg_method = 'REQUEST_METHOD';
$arg_user = 'PHP_AUTH_USER';
$arg_pw = 'PHP_AUTH_PW';
if (isset($_SERVER[$arg_user])) {
    echo "Hello '{$_SERVER[$arg_user]}' \n";
    echo "You entered '{$_SERVER [$arg_pw]}' as your password.  \n \n ";
}

// method
echo " $arg_method : $_SERVER[$arg_method] <br/> \n";

// header
foreach ( getallheaders() as $key => $value ) {
    echo "$key : $value <br/> \n";
}
echo "\n";

// post data
$post_data = file_get_contents('php://input');
if (!empty($post_data)) {
    echo "data: \n";
    echo " $post_data \n";
}
?>
