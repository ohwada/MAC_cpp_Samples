// 2022-10-01 K.OHWADA
// echo_client.js
// https://kazuhira-r.hatenablog.com/entry/20170912/1505227491

const net = require("net");

const util = require('util');

const sleep = require('sleep');

const args = process.argv.slice(2);


const FORMAT = "test %d";

const SLEEP = 1; // 1 sec

const DATA_LIMIT = 10;

let data_cnt = 0;

let host = "localhost";
let port = 1234;
let message = "Hello";


if (args.length > 2) {
    host = args[0];
    port = parseInt(args[1]);
    message = args[2];
} else if (args.length > 1) {
    // host = "localhost";
    port = parseInt(args[0]);
    message = args[1];
}

const logger = fun => console.log(`[${new Date()}] ${fun.call(null)}`);

const client = net.createConnection({ host: host, port: port }, () => {
    logger(() => "start client");
});

client.on("connect", () => {
    logger(() => `connected server[${host}:${client.remotePort}]`);

// send first message
    const msg = util.format(FORMAT, data_cnt);
    client.write(msg);

    // logger(() => `send message[${message}]`);
});

client.on("data", data => {
    // logger(() => `receive message[${data}]`);
        console.info( `r: ${data}`);

    data_cnt ++;
    if(data_cnt > DATA_LIMIT){
        console.info( `destroy`);
        client.destroy();
        return;
    }

    const msg = util.format(FORMAT, data_cnt);
    sleep.sleep(SLEEP);
    client.write(msg);
});

client.on("close", () => logger(() => "disconnect server"));

