const HEADER_SIZE = 18;

export default (canvas) => {
  const context = canvas.getContext('2d');
  let initialized = false;
  let pixel = [];
  let x = 0;
  let y = 0;
  let width, height;

  return new WritableStream({
    async write(chunk) {
      let shift = 0;
      if (!initialized) {
        initialized = true;
        shift = HEADER_SIZE;
        const header = new Uint8Array(HEADER_SIZE);
        for (let i = 0; i < HEADER_SIZE; i++) {
          header[i] = chunk[i];
        }
        canvas.width = width = header[12] + (header[13] << 8);
        canvas.height = height = header[14] + (header[15] << 8);
        console.log(`${width}x${height}`)
      }
      const data = new Uint8Array(chunk.buffer, shift);
      for (const byte of data) {
        pixel.unshift(byte);
        if (pixel.length === 3) {
          context.fillStyle = `rgb(${pixel.join(',')})`;
          context.fillRect(x++, y, 1, 1);
          if (x === width) {
            x = 0; y++;
          }
          pixel = [];
        }
      }
    }
  });
}