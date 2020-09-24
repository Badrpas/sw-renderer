const chokidar = require('chokidar');
const express = require('express');
const path = require('path');

const app = express();

const http = require('http').createServer(app);
const io = require('socket.io')(http);

require('./c-watch')(io);

const clients = new Set();

io.on('connection', socket => {
  clients.add(socket);
  console.log('connection');

  socket.on('disconnect', () => {
    clients.delete(socket);
    console.log('disc');
  })
});

app.use(express.static(path.resolve(process.cwd(), 'public')));

app.get('/', (req, res) => {

  res.render('index.html');
});

http.listen(1234, () => {
  console.log('listening');
});

chokidar.watch(['./public/*.js', './public/*.html']).on('all', () => {
  io.emit('refresh:all');
});

chokidar.watch('./public/out.tga').on('change', () => {
  io.emit('refresh:out');
});