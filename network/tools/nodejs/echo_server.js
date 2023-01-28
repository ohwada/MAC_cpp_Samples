// 2022-10-01 K.OHWADA
// echo_server.js
// https://kazuhira-r.hatenablog.com/entry/20170912/1505227491

const net = require("net");

const args = process.argv.slice(2);

const port = args.length > 0 ? parseInt(args[0]) : 1234;

const logger = fun => console.log(`[${new Date()}] ${fun.call(null)}`);

const server = net.createServer(socket => {
    logger(() => `accept client = ${socket.remotePort}`);

    socket.setEncoding("utf8");  // as String

    socket.on("data", (data) => {
        const recvData = data;
        const trimmedData = data.trim();

        // logger(() => `receive data[${trimmedData}]`);
        console.info( `r: ${trimmedData}`);

        socket.write(`${recvData}`);
    });

    socket.on("close", () => logger(() => `disconnect client = ${socket.remoteAddress}:${socket.remotePort}`));
});

server.on("error", err => { throw err; });
server.on("close", () => logger(() => "Echo Server, Shutdown"));

server.listen({ host: "localhost", port: port }, () => {
    logger(() => `Echo Server[${port}], Startup`);
});

// Echo Server[1234], Startup
