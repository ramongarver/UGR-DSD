const http = require("http");
const url = require('url');
const fs = require("fs");
const path = require("path");

const MongoClient = require('mongodb').MongoClient;
const MongoServer = require('mongodb').Server;

const Socketio = require("socket.io");

const mimeTypes = {
    "html": "text/html",
    "jpeg": "image/jpeg",
    "jpg": "image/jpeg",
    "png": "image/png",
    "js": "text/javascript",
    "css": "text/css",
    "swf": "application/x-shockwave-flash"
};

// El servidor ofrece la página cliente.html por defecto al conectarse
let httpServer = http.createServer(
    function (request, response) {
        let uri = url.parse(request.url).pathname;
        if (uri == "/") uri = "/cliente.html";
        let fname = path.join(process.cwd(), uri);
        fs.exists(fname, function (exists) {
            if (exists) {
                fs.readFile(fname, function (err, data) {
                    if (!err) {
                        let extension = path.extname(fname).split(".")[1];
                        let mimeType = mimeTypes[extension];
                        response.writeHead(200, mimeType);
                        response.write(data);
                        response.end();
                    } else {
                        response.writeHead(200, {"Content-Type": "text/plain"});
                        response.write('Error de lectura en el fichero: ' + uri);
                        response.end();
                    }
                });
            } else {
                console.log("Petición invalida: " + uri);
                response.writeHead(200, {"Content-Type": "text/plain"});
                response.write('404 Not Found\n');
                response.end();
            }
        });
    }
);

// Estados posibles de los diferentes objetos controlables
const EstadosPersiana = {ABIERTA: "Abierta", CERRADA: "Cerrada"};
const EstadosAireAcondicionado = {ENCENDIDO: "Encendido", APAGADO: "Apagado"};
const EstadosLuz = {ENCENDIDA: "Encendida", APAGADA: "Apagada"}
const EstadosCalefactor = {ENCENDIDO: "Encendido", APAGADO: "Apagado"};
const EstadosHumidificador = {ENCENDIDO: "Encendido", APAGADO: "Apagado"};

// Estados iniciales de los diferentes objetos controlables
let estadoPersiana = EstadosPersiana.ABIERTA;
let estadoAireAcondicionado = EstadosAireAcondicionado.ENCENDIDO;
let estadoLuz = EstadosLuz.ENCENDIDA;
let estadoCalefactor = EstadosCalefactor.APAGADO;
let estadoHumidificador = EstadosHumidificador.ENCENDIDO;

let mongoClient = new MongoClient(new MongoServer('localhost', 27017));
// Conexión a la base de datos
mongoClient.connect("mongodb://localhost:27017/domoticaDB", function (err, db) {
    httpServer.listen(8080);
    let io = Socketio(httpServer);

    db.createCollection("sensores", function (err, collection) {
        io.sockets.on('connection', function (client) {
            // Suscripción al estado de los sensores - Evento 'publicar-estados-sensores'
            client.on('publicar-estados-sensores', function (datosSensores) {
                // Insertamos los datos recibidos de los sensores en la colección
                collection.insert(datosSensores, {safe: true}, function (err, result) {});

                // Publicación del estado de los sensores a todos los clientes - Evento 'actualizar-estados-sensores'
                io.sockets.emit('actualizar-estados-sensores',
                    "Temperatura - " + datosSensores.temperatura +
                    "ºC | Luminosidad - " + datosSensores.luminosidad +
                    " Lux | Humedad - " + datosSensores.humedad +
                    " % | Fecha - " + datosSensores.fecha);

                // Publicación del estado del sensor de temperatura - Evento 'estado-temperatura'
                io.sockets.emit('estado-temperatura', datosSensores.temperatura);
                // Publicación del estado del sensor de luminosidad - Evento 'estado-luminosidad'
                io.sockets.emit('estado-luminosidad', datosSensores.luminosidad);
                // Publicación del estado del sensor de humedad - Evento 'estado-humedad'
                io.sockets.emit('estado-humedad', datosSensores.humedad)
            });

            // Suscripción a la petición de la última información de los sensores por parte del cliente
            // Evento - 'ultima-informacion-sensores'
            client.on('ultima-informacion-sensores', function () {
                collection.find().sort({_id: -1}).limit(1).forEach(function (datosSensores) {
                    client.emit('actualizar-estados-sensores',
                        "Temperatura - " + datosSensores.temperatura +
                        "ºC | Luminosidad - " + datosSensores.luminosidad +
                        " Lux | Humedad - " + datosSensores.humedad +
                        " % | Fecha - " + datosSensores.fecha);
                });
            });

            // Suscripción a la petición de la última información de temperatura del sensor por parte del agente
            // Evento - 'obtener-temperatura'
            client.on('obtener-temperatura', function () {
                collection.find().sort({_id: -1}).limit(1).forEach(function (datosSensores) {
                    // Publicación del estado del sensor de temperatura al agente - Evento 'estado-temperatura'
                    client.emit('estado-temperatura', datosSensores.temperatura);
                });
            });

            // Suscripción a la petición de la última información de luminosidad del sensor por parte del agente
            // Evento - 'obtener-luminosidad'
            client.on('obtener-luminosidad', function () {
                collection.find().sort({_id: -1}).limit(1).forEach(function (datosSensores) {
                    // Publicación del estado del sensor de luminosidad al agente - Evento 'estado-luminosidad'
                    client.emit('estado-luminosidad', datosSensores.luminosidad);
                });
            });

            // Suscripción a la petición de la última información de humedad del sensor por parte del agente
            // Evento - 'obtener-humedad'
            client.on('obtener-humedad', function () {
                collection.find().sort({_id: -1}).limit(1).forEach(function (datosSensores) {
                    // Publicación del estado del sensor de humedad  al agente - Evento 'estado-humedad'
                    client.emit('estado-humedad', datosSensores.humedad);
                });
            });

            // Suscripción al cierre de la persiana por el agente - Evento 'cerrar-persiana'
            client.on('cerrar-persiana', function () {
                estadoPersiana = EstadosPersiana.CERRADA;

                // Publicación al cliente del estado de la persiana - Evento 'estado-persiana'
                io.sockets.emit('estado-persiana', estadoPersiana);
                console.log("Cambiado el estado de la persiana a: " + estadoPersiana);
            });

            // Suscripción al cambio del estado de la persiana por el cliente - Evento 'cambiar-estado-persiana'
            client.on('cambiar-estado-persiana', function () {
                if (estadoPersiana == EstadosPersiana.ABIERTA)
                    estadoPersiana = EstadosPersiana.CERRADA;
                else
                    estadoPersiana = EstadosPersiana.ABIERTA;

                // Publicación al cliente del estado de la persiana - Evento 'estado-persiana'
                io.sockets.emit('estado-persiana', estadoPersiana);
                console.log("Cambiado el estado de la persiana a: " + estadoPersiana);
            });

            // Suscripción al cambio del estado del aire acondicionado por el cliente - Evento 'cambiar-estado-aire-acondicionado'
            client.on('cambiar-estado-aire-acondicionado', function () {
                if (estadoAireAcondicionado == EstadosAireAcondicionado.ENCENDIDO)
                    estadoAireAcondicionado = EstadosAireAcondicionado.APAGADO;
                else
                    estadoAireAcondicionado = EstadosAireAcondicionado.ENCENDIDO;

                // Publicación al cliente del estado del aire acondicionado - Evento 'estado-aire-acondicionado'
                io.sockets.emit('estado-aire-acondicionado', estadoAireAcondicionado);
                console.log("Cambiado el estado del aire acondicionado a: " + estadoAireAcondicionado);
            });

            // Suscripción al cambio del estado de la luz por el cliente - Evento 'cambiar-estado-luz'
            client.on('cambiar-estado-luz', function () {
                if (estadoLuz == EstadosLuz.ENCENDIDA)
                    estadoLuz = EstadosLuz.APAGADA;
                else
                    estadoLuz = EstadosLuz.ENCENDIDA;

                // Publicación al cliente del estado de la luz - Evento 'estado-luz'
                io.sockets.emit('estado-luz', estadoLuz);
                console.log("Cambiado el estado de la luz a: " + estadoLuz);
            });

            // Suscripción al cambio del estado del calefactor por el cliente - Evento 'cambiar-estado-calefactor'
            client.on('cambiar-estado-calefactor', function () {
                if (estadoCalefactor == EstadosCalefactor.ENCENDIDO)
                    estadoCalefactor = EstadosCalefactor.APAGADO;
                else
                    estadoCalefactor = EstadosCalefactor.ENCENDIDO;

                // Publicación al cliente del estado del calefactor - Evento 'estado-calefactor'
                io.sockets.emit('estado-calefactor', estadoCalefactor);
                console.log("Cambiado el estado del calefactor a: " + estadoCalefactor);
            });

            // Suscripción al cambio del estado del humidificador por el cliente - Evento 'cambiar-estado-humidificador'
            client.on('cambiar-estado-humidificador', function () {
                if (estadoHumidificador == EstadosHumidificador.ENCENDIDO)
                    estadoHumidificador = EstadosHumidificador.APAGADO;
                else
                    estadoHumidificador = EstadosHumidificador.ENCENDIDO;

                // Publicación al cliente del estado del humidificador - Evento 'estado-humidificador'
                io.sockets.emit('estado-humidificador', estadoHumidificador);
                console.log("Cambiado el estado del humidificador a: " + estadoHumidificador);
            });

            // Suscripción a petición del estado de la persiana
            client.on('obtener-estado-persiana', function () {
                client.emit('estado-persiana', estadoPersiana);
            });
            // Suscripción a petición del estado del aire acondicionado
            client.on('obtener-estado-aire-acondicionado', function () {
                client.emit('estado-aire-acondicionado', estadoAireAcondicionado);
            });
            // Suscripción a petición del estado de la luz
            client.on('obtener-estado-luz', function () {
                client.emit('estado-luz', estadoLuz);
            });
            // Suscripción a petición del estado del calefactor
            client.on('obtener-estado-calefactor', function () {
                client.emit('estado-calefactor', estadoCalefactor);
            });
            // Suscripción a petición del estado del humidificador
            client.on('obtener-estado-humidificador', function () {
                client.emit('estado-humidificador', estadoHumidificador);
            });

            // Suscripción a la alerta de temperatura del agente
            // Evento - 'alerta-temperatura'
            client.on('alerta-temperatura', function (temperatura) {
                // Publicación de actualización de advertencia de temperatura - Evento 'advertencia-temperatura'
                io.sockets.emit('advertencia-temperatura', temperatura);
            });

            // Suscripción a la alerta de luminosidad del agente
            // Evento - 'alerta-luminosidad'
            client.on('alerta-luminosidad', function (luminosidad) {
                // Publicación de actualización de advertencia de temperatura - Evento 'advertencia-luminosidad'
                io.sockets.emit('advertencia-luminosidad', luminosidad);
            });
        });
    });
});

console.log("Servicio Domótico iniciado");