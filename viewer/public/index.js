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
  console.log('Need TGA refresh');
  refreshTga();
});