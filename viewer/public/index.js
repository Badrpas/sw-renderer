import createRenderer from './renderer.js';

const socket = io();

function getCanvas () {
  if (getCanvas._canvas) getCanvas._canvas.remove();

  getCanvas._canvas = document.createElement('canvas');

  document.body.append(getCanvas._canvas);

  return getCanvas._canvas;
}

async function refreshTga() {
  const canvas = getCanvas();
  const renderer = createRenderer(canvas);
  const { body } = await fetch('/out.tga');
  body.pipeTo(renderer);
}

refreshTga();

socket.on('connect', () => {
  console.log('connected');
})

socket.on('disconnect', () => {
  console.log('disconnected');
});

socket.on('refresh:all', () => {
  console.log('refr')
  window.location.reload();
});

socket.on('refresh:out', () => {
  refreshTga();
});

function proc(name) {
  let stderr = '';
  let stdout = '';
  socket.on(name + ':start', () => {
    console.log(name + ' start');
    stderr = '';
    stdout = '';
  });
  socket.on(name + ':stdout', (data) => {
    stdout += data;
  });
  socket.on(name + ':stderr', (data) => {
    stderr += data;
  });
  socket.on(name + ':end', () => {
    stdout && console.log(stdout);
    stderr && console.warn(stderr);
    stderr = stdout = '';
  });
}
proc('compile');
proc('run');