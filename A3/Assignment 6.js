const http = require('http');
const fs = require('fs');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
	let htmlFile = '';
	switch(req.url) {
		case '/':
			htmlFile = 'index.html';
			break;
		case '/index':
			htmlFile = 'index.html';
			break;
		case '/introduction':
			htmlFile = 'introduction.html';
			break;
		default:
			break;
	}

	if(htmlFile)
		render(res, htmlFile);
});

function render(res, htmlFile) {
  	fs.stat(`./${htmlFile}`, (err, stats) => {
		res.statusCode = 200;
		res.setHeader('Content-Type', 'text/html');
  		if(stats) {
		  	fs.createReadStream(htmlFile).pipe(res);
  		} else {
  			res.statusCode = 404;
  			res.end('Sorry, page not found!');
  		}
  	});
}

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});