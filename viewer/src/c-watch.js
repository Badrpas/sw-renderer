const chokidar = require('chokidar');
const which = require('which');
const { spawn } = require('child_process');

const cmake_path = which.sync('cmake');
const project_path = require('path').resolve(process.cwd(), '..');
console.log(cmake_path)

async function compile(io) {
  const p = spawn(cmake_path, [
    '-DCMAKE_BUILD_TYPE=Debug',
    '-G',
    'CodeBlocks - NMake Makefiles',
    project_path
  ]);

  p.stdout.on('data', data => {
    io.emit('compile:stdout', data.toString());
  });

  p.stderr.on('data', data => {
    io.emit('compile:stderr', data.toString());
  });

  return new Promise(resolve => {
    p.on('close', resolve);
  });
}

module.exports = async io => {
  let inProgress = false;
  chokidar.watch(['../*.c', '../*.h']).on('change', async () => {
    if (inProgress) return;
    inProgress = true;

    io.emit('compile:start');
    await compile(io);
    io.emit('compile:end');

    inProgress = false;
  });
}