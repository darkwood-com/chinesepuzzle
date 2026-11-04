// Regression test for the shipped GamePix export inside a real, resizable iframe.
// NODE_PATH=<playwright modules> node tools/verify-web.js Exports/GamePix /tmp/cpz-qa
const {chromium} = require('playwright');
const http = require('http'), fs = require('fs'), path = require('path'), assert = require('assert/strict');
const dir = path.resolve(process.argv[2]), out = process.argv[3];
fs.mkdirSync(out, {recursive:true});
const types={'.html':'text/html','.js':'application/javascript','.wasm':'application/wasm','.png':'image/png','.jpg':'image/jpeg'};
const server=http.createServer((req,res)=>{
  if(req.url==='/fixture') {res.setHeader('Content-Type','text/html'); return res.end('<body style="margin:0"><iframe style="border:0;width:800px;height:450px" src="/index.html"></iframe>');}
  const file=path.resolve(dir,'.'+decodeURIComponent(req.url.split('?')[0]));
  if(!file.startsWith(dir+path.sep)||!fs.existsSync(file)){res.writeHead(404);return res.end();}
  res.setHeader('Content-Type',types[path.extname(file)]||'application/octet-stream');fs.createReadStream(file).pipe(res);
});
(async()=>{
 await new Promise(r=>server.listen(0,'127.0.0.1',r));
 const browser=await chromium.launch({args:['--use-gl=angle','--use-angle=swiftshader','--enable-unsafe-swiftshader']});
 try{
 const context=await browser.newContext({viewport:{width:1500,height:1100},locale:'fr-FR',hasTouch:true});
 // GamePix owns storage synchronization in its player. Keep local UI fixtures
 // isolated; validate the real SDK separately through the platform Preview.
 await context.route('https://integration.gamepix.com/**', route=>route.fulfill({contentType:'application/javascript',body:'/* Standalone UI regression fixture. */'}));
 const board=Array.from({length:8},(_,i)=>Array.from({length:14},(_,j)=>j===0?-1:(i%4)*13+j-1));
 await context.addInitScript(save=>{if(!localStorage.getItem('chinesepuzzle.data'))localStorage.setItem('chinesepuzzle.data',JSON.stringify(save));},{init_board:board,moves:[],sound_on:false});
 const page=await context.newPage(), errors=[];
 page.on('pageerror',e=>errors.push(e.message));
 page.on('console',m=>{if(m.type()==='error')errors.push(m.text());});
 await page.goto(`http://127.0.0.1:${server.address().port}/fixture`);
 let frame=page.frames().find(f=>f.url().endsWith('/index.html'));
 await frame.waitForFunction(()=>document.querySelector('#loading')?.style.display==='none',null,{timeout:90000});
 await page.waitForTimeout(3000);
 let W=800,H=450;
 const at=(x,y)=>{const s=Math.min(W/960,H/640);return [(W-960*s)/2+x*s,(H-640*s)/2+y*s];};
 const click=async(x,y)=>{await page.mouse.click(...at(x,y));await page.waitForTimeout(750);};
 const cell=(i,j)=>[8+(j+.5)*60,640-(i+.5)*80];
 const save=()=>frame.evaluate(()=>JSON.parse(localStorage.getItem('chinesepuzzle.data')));
 const shot=async(n)=>page.locator('iframe').screenshot({path:path.join(out,n+'.png')});
 await shot('800x450-board');
 // Reject a non-Ace in the first column, then exercise a valid drag and undo.
 async function drag(from,to){await page.mouse.move(...at(...cell(...from)));await page.mouse.down();await page.mouse.move(...at(...cell(...to)),{steps:10});await page.mouse.up();await page.waitForTimeout(900);}
 await drag([0,2],[0,0]);assert.equal((await save()).moves.length,0);
 await drag([0,1],[0,0]);assert.equal((await save()).moves.length,1);
 assert.equal((await save()).theme,'classic');
 await click(902,268);assert.equal((await save()).moves.length,0);
 // Tap-to-move and persistence across reload.
 await click(...cell(0,1));await page.waitForTimeout(600);await click(...cell(0,0));await page.waitForTimeout(700);
 assert.equal((await save()).moves.length,1);
 await page.reload();frame=page.frames().find(f=>f.url().endsWith("/index.html"));await page.waitForTimeout(7000);assert.equal((await save()).moves.length,1);
 // Rules and all confirmation dialogs fit at the minimum supported size.
 await click(902,372);await shot('800x450-rules');await click(870,80);
 for(const [name,y] of [['new',60],['restart',164]]){await click(902,y);await shot('800x450-'+name);await click(380,420);}
 await click(902,476);assert.equal((await save()).sound_on,true);await click(902,476);
 await click(902,580);await shot('800x450-themes');
 const themes=['classic','chinese','polkadots','seamless','shullshearts','splash','spring','stripes','vivid'];
 for(let i=0;i<9;i++){await click(180+74+(i%3)*154+72,20+80+Math.floor(i/3)*125.2+57.6);assert.equal((await save()).theme,themes[i]);}
 await click(290,560);assert.equal((await save()).card_layout,true);
 // Restore classic and test resize while a dialog is open.
 await click(326,158);
 for(const [w,h] of [[1280,720],[960,640],[800,450],[450,800]]){
  W=w;H=h;await page.locator('iframe').evaluate((el,s)=>{el.style.width=s[0]+'px';el.style.height=s[1]+'px';},[w,h]);
  await page.waitForTimeout(700);await shot(`${w}x${h}-resized-themes`);
  const rect=await frame.locator('canvas').boundingBox();assert.equal(Math.round(rect.width),w);assert.equal(Math.round(rect.height),h);
 }
 W=800;H=450;
 await page.locator('iframe').evaluate(el=>{el.style.width='800px';el.style.height='450px';});
 await page.waitForTimeout(700);await click(770,30);await click(902,268);
 await page.touchscreen.tap(...at(...cell(0,1)));await page.waitForTimeout(750);
 await page.touchscreen.tap(...at(...cell(0,0)));await page.waitForTimeout(750);
 assert.equal((await save()).moves.length,1);
 await click(902,164);await click(580,420);await page.waitForTimeout(3000);
 assert.equal((await save()).moves.length,0);assert.deepEqual((await save()).init_board,board);
 await click(902,60);await click(580,420);await page.waitForTimeout(3000);
 assert.equal((await save()).moves.length,0);assert.notDeepEqual((await save()).init_board,board);
 assert.deepEqual(errors,[]);console.log(JSON.stringify({result:'PASS',checks:['invalid move','drag move','undo','tap move','save/reload','sound','nine themes','card layout','dialogs','iframe resize','touch input','restart confirmation','new game confirmation'],errors},null,2));
 }finally{await browser.close();server.close();}
})().catch(e=>{console.error(e);server.close();process.exit(1);});
