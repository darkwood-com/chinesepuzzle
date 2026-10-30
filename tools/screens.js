// Store screenshots from the Web export with a mid-game save injected in localStorage.
// node tools/screens.js <export dir> <out dir>
const { chromium } = require('playwright');
const http = require('http'), fs = require('fs'), path = require('path');
const dir = process.argv[2], outDir = process.argv[3];
const types = { '.html': 'text/html', '.js': 'application/javascript', '.wasm': 'application/wasm', '.png': 'image/png' };
const server = http.createServer((req, res) => {
  const p = path.join(dir, decodeURIComponent(req.url.split('?')[0]).replace(/^\/$/, '/index.html'));
  if (!fs.existsSync(p)) { res.writeHead(404); return res.end(); }
  res.writeHead(200, { 'Content-Type': types[path.extname(p)] || 'application/octet-stream' });
  fs.createReadStream(p).pipe(res);
}).listen(0);

// Mid-game position: solved board scrambled with reverse moves (seeded), so every row is partly sorted.
function scramble(seed, steps) {
  let s = seed; const rnd = n => { s = (s * 16807) % 2147483647; return s % n; };
  const b = []; for (let i = 0; i < 8; i++) { b.push([]); for (let j = 0; j < 14; j++) b[i].push(j < 13 ? (i % 4) * 13 + j : -1); }
  const next = (c, p) => c >= 0 && p >= 0 && Math.floor(c / 13) === Math.floor(p / 13) && c % 13 === p % 13 + 1;
  let last = null;
  for (let k = 0; k < steps; k++) {
    const cand = [], gaps = [];
    for (let i = 0; i < 8; i++) for (let j = 0; j < 14; j++) {
      const c = b[i][j];
      if (c < 0) gaps.push([i, j]); else if ((j === 0 && c % 13 === 0) || (j > 0 && next(c, b[i][j - 1]))) cand.push([i, j]);
    }
    if (!cand.length) break;
    const g = cand[rnd(cand.length)], p = gaps[rnd(gaps.length)];
    const t = b[g[0]][g[1]]; b[g[0]][g[1]] = b[p[0]][p[1]]; b[p[0]][p[1]] = t;
    last = [p, g];
  }
  return { board: b, move: last };
}

(async () => {
  const port = server.address().port;
  const browser = await chromium.launch({ args: ['--use-gl=angle', '--use-angle=swiftshader', '--enable-unsafe-swiftshader'] });
  const W = 1440, H = 960, s = 1.5;
  const at = (x, y) => [x * s, y * s];
  const bp = (i, j) => at(8 + (0.5 + j) * 60, 640 - (0.5 + i) * 80);
  async function open(theme, cardLayout, seed, steps) {
    const { board, move } = scramble(seed, steps);
    const save = JSON.stringify({ theme, card_layout: cardLayout, sound_on: false, init_board: board, moves: [] });
    const page = await browser.newPage({ viewport: { width: W, height: H } });
    const errors = [];
    page.on('console', m => { if (m.type() === 'error') errors.push(m.text()); });
    await page.addInitScript(v => localStorage.setItem('chinesepuzzle.data', v), save);
    await page.goto(`http://localhost:${port}/index.html`);
    await page.waitForTimeout(16000);
    return { page, move, errors };
  }
  const shots = [];
  let r = await open('classic', false, 7, 45);
  await r.page.screenshot({ path: `${outDir}/screenshot-1-game.png` }); shots.push('screenshot-1-game.png');
  // drag a card over a valid slot (green hint) and hold for the screenshot
  const [from, to] = r.move; let [x, y] = bp(from[0], from[1]); const [tx, ty] = bp(to[0], to[1]);
  await r.page.mouse.move(x, y); await r.page.mouse.down(); await r.page.mouse.move(tx + 4, ty + 4, { steps: 12 });
  await r.page.waitForTimeout(400);
  await r.page.screenshot({ path: `${outDir}/screenshot-2-drag.png` }); shots.push('screenshot-2-drag.png');
  await r.page.mouse.up(); await r.page.waitForTimeout(1200);
  const errs = [...r.errors];
  await r.page.close();
  r = await open('spring', true, 11, 45);
  [x, y] = at(902, 580); await r.page.mouse.click(x, y); await r.page.waitForTimeout(1500);
  await r.page.screenshot({ path: `${outDir}/screenshot-3-themes.png` }); shots.push('screenshot-3-themes.png');
  errs.push(...r.errors);
  console.log(JSON.stringify({ shots, errors: errs }));
  await browser.close(); server.close();
})();
