// Headless Chrome smoke test of a Web export: node tools/smoke.js <export dir> <out prefix>
// Serves the folder, checks non-blank render + no console errors, plays a few taps and saves screenshots.
const { chromium } = require('playwright');
const http = require('http'), fs = require('fs'), path = require('path');
const dir = process.argv[2], out = process.argv[3];
const types = { '.html': 'text/html', '.js': 'application/javascript', '.wasm': 'application/wasm', '.png': 'image/png', '.jpg': 'image/jpeg', '.pck': 'application/octet-stream' };
const server = http.createServer((req, res) => {
  const p = path.join(dir, decodeURIComponent(req.url.split('?')[0]).replace(/^\/$/, '/index.html'));
  if (!fs.existsSync(p)) { res.writeHead(404); return res.end(); }
  res.writeHead(200, { 'Content-Type': types[path.extname(p)] || 'application/octet-stream' });
  fs.createReadStream(p).pipe(res);
}).listen(0);
(async () => {
  const port = server.address().port;
  const browser = await chromium.launch({ args: ['--use-gl=angle', '--use-angle=swiftshader', '--enable-unsafe-swiftshader', '--autoplay-policy=no-user-gesture-required'] });
  const W = 1280, H = 800;
  const page = await browser.newPage({ viewport: { width: W, height: H } });
  const errors = [], logs = [];
  page.on('console', m => { logs.push(m.type() + ': ' + m.text()); if (m.type() === 'error') errors.push(m.text()); });
  page.on('pageerror', e => errors.push('pageerror: ' + e.message));
  await page.goto(`http://localhost:${port}/index.html${process.argv[4] || ''}`);
  await page.waitForTimeout(15000);
  // design 960x640, stretch canvas_items + expand: scale by min ratio, centered
  const s = Math.min(W / 960, H / 640), ox = (W / s - 960) / 2, oy = (H / s - 640) / 2;
  const at = (x, y) => [(x + ox) * s, (y + oy) * s];
  const shot = async n => { await page.screenshot({ path: `${out}-${n}.png` }); };
  await shot('game');
  const buf = await page.screenshot();
  const { createHash } = require('crypto');
  // non-blank check: sample canvas pixels
  const stats = await page.evaluate(() => {
    const c = document.querySelector('canvas'); const t = document.createElement('canvas');
    t.width = 64; t.height = 40; const g = t.getContext('2d'); g.drawImage(c, 0, 0, 64, 40);
    const d = g.getImageData(0, 0, 64, 40).data; const set = new Set();
    for (let i = 0; i < d.length; i += 4) set.add((d[i] >> 4) + ',' + (d[i + 1] >> 4) + ',' + (d[i + 2] >> 4));
    return set.size;
  });
  // tap a card then drag it a bit (gameplay input), then open the theme menu and the rules
  let [x, y] = at(8 + 1.5 * 60, 640 - 3.5 * 80);
  await page.mouse.move(x, y); await page.mouse.down(); await page.mouse.move(x + 40, y + 10, { steps: 5 }); await page.mouse.up();
  await page.waitForTimeout(1200);
  [x, y] = at(902, 640 - 60); await page.mouse.click(x, y); await page.waitForTimeout(1500); await shot('menu-themes');
  [x, y] = at(770, 30); await page.mouse.click(x, y); await page.waitForTimeout(800);
  [x, y] = at(902, 640 - 268); await page.mouse.click(x, y); await page.waitForTimeout(1500); await shot('menu-rules');
  [x, y] = at(870, 80); await page.mouse.click(x, y); await page.waitForTimeout(800);
  await shot('after');
  console.log(JSON.stringify({ distinctColors: stats, errors, logs: logs.slice(-15) }, null, 1));
  await browser.close(); server.close();
  process.exit(errors.length || stats < 10 ? 1 : 0);
})();
