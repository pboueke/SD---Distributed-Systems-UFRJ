var fs = require('fs');
var Regex = require('regex');

var regex = new Regex(/(frase\n)*/);

fs.readFile('test.txt', 'utf8', function (err,data) {
  
  var array = data.match(/frase\n/g);
  var length = array ? array.length : 0;
  console.log(length);

  console.log('Resetting file...');
  fs.writeFile('test.txt', '', function (err) { console.log('Done'); });
});



