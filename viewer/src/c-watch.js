const chokidar = require('chokidar');
const which = require('which');
const {spawn, spawnSync} = require('child_process');
const fs = require('fs');
const path = require('path');

const cmake_executable = which.sync('cmake');
const project_path = path.resolve(process.cwd(), '..');
console.log(cmake_executable)

const CL_PATH = 'C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.25.28610/bin/HostX86/x86/';
const ENV = Object.create(process.env);
ENV.PATH = ENV.PATH + ';' + CL_PATH;

const ls_result = fs.readdirSync(project_path);
const CMAKE_DIRNAME = 'cmake-build-debug';
const build_dir_path = path.resolve(project_path, CMAKE_DIRNAME);
const executable_path = path.resolve(build_dir_path, 'render_my_way.exe');
const GENERATOR = 'CodeBlocks - NMake Makefiles';
const cmake_args = [
  '-DCMAKE_BUILD_TYPE=Debug',
  '-G', GENERATOR,
  '..'
];
const spawn_args = [
  cmake_executable,
  cmake_args, {
    cwd: build_dir_path,
    env: ENV,
  }
]


// if (!ls_result.includes(CMAKE_DIRNAME)) {
//   fs.mkdirSync(build_dir_path);
// }
// if (!fs.readdirSync(build_dir_path).length) {
//   console.log('making build dir');
//
//   let retries = 5;
//
//   function generate() {
//     if (!retries--) return;
//     const p = spawnSync(...spawn_args);
//     if (p.status) {
//       console.log(p.stderr.toString());
//       return generate();
//     }
//     console.log(p.stdout.toString());
//     console.log('done making build dir');
//   }
// }

async function compile(io) {
  const p = spawn(cmake_executable, [
    '--build',
    build_dir_path,
    '--target',
    'render_my_way'
  ], { cwd: build_dir_path, env: ENV, });

  return execute(p, io, 'compile');
}
async function execute (p, io, name) {
  io.emit(name + ':start');
  p.stdout.on('data', data => {
    io.emit(name + ':stdout', data.toString());
  });

  p.stderr.on('data', data => {
    io.emit(name + ':stderr', data.toString());
  });

  return new Promise((resolve, reject) => {
    p.on('close', (code) => {
      if (code === 0) resolve()
      else reject(code);
    });
  }).then(() => io.emit(name + ':end'));
}

async function run (io) {
  const p = spawn(executable_path, { cwd: build_dir_path, env: ENV, });
  return execute(p, io, 'run');
}

module.exports = async io => {
  let inProgress = false;
  chokidar.watch(['../*.c', '../*.h']).on('change', async () => {
    if (inProgress) return;
    inProgress = true;

    try {
      await compile(io);
    } catch (e) {
      console.error('compile exited with: ', e);
      inProgress = false;
      return;
    }
    await run(io);

    io.emit('refresh:out');

    inProgress = false;
  });
}